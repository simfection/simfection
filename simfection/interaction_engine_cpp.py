import pandas as pd
import numpy as np
from invoke import run
# User defined imports
from .interaction_engine import InteractionEngine
from .settings import SimfectionSettings
from .logger import SimfectionLogger

simfection_logger = SimfectionLogger(name=__name__)
logger = simfection_logger.get_logger()

# the network library depends on the
# network.comparchitecture.so file being in the same directory
try:
    # If the network.so file does not exist, this will fail
    import network
except ModuleNotFoundError:
    # Compile the Network library from /cpp_src/
    cmd = "python3 setup.py build_ext --inplace"
    result = run(cmd, hide=True, warn=True)
    if result.ok:
        logger.info("Network C++ library succesfully compiled.")
        try:
            import network
        except ModuleNotFoundError:
            logger.info("Even after Network library was compiled, unable to import.")
            pass
    else:
        logger.info("Unable to compile Network C++ library.")


class InteractionEngineCpp(InteractionEngine):
    def __init__(self,
                 connections: pd.DataFrame = None,
                 population: pd.DataFrame = None,
                 settings: SimfectionSettings = None) -> None:
        logger.debug('+ Initializing interaction engine.')
        self.connections = connections
        self.population = population
        self.verbose = settings.get_setting('verbose')
        self.pathogen = {
            key: settings.get_setting(key) for key in settings.get_setting('pathogen_keys')
        }
        self.cpp = settings.get_setting('cpp')

    def _init_interactions(self):
        # Initialize the network.PyInteractions object
        # For a look at the API, checkout the network.pyx file in /cpp_src/cython
        self.interactions = network.PyInteractions()

        # Get all the population information required for running PyInteractions
        pop_agent = self.population['agent'].tolist()
        pop_state = self.population['state'].tolist()
        # Convert every string in pop_state to unicode bytes for ingestion in interactions
        pop_state = [state.encode() for state in pop_state]
        pop_infected_by = self.population['infected_by'].tolist()
        # Do a quick list comprehension to convert any NoneType to empty lists
        pop_infected_by = [[] if this_list == None else this_list for this_list in pop_infected_by]
        pop_days_infected = self.population['days_infected'].tolist()
        pop_immunity = self.population['immunity'].tolist()

        # Set the Population in the PyInteractions object
        self.interactions.set_population(pop_agent,
                                    pop_state,
                                    pop_infected_by,
                                    pop_days_infected,
                                    pop_immunity)

        # Get all the connections information required for running PyInteractions
        conn_agent = self.connections['agent'].tolist()
        conn_connections = self.connections['connections'].tolist()
        conn_num_connections = self.connections['num_connections'].tolist()
        conn_max_connections = self.connections['max_connections'].tolist()

        # Set the Connections in the PyInteractions object
        self.interactions.set_connections(conn_agent,
                                     conn_connections,
                                     conn_num_connections,
                                     conn_max_connections)

        # Set the Pathogen settings, first convert each value in pathogen
        # to unicode bytes for ingestion to interactions
        pathogen = {key.encode(): value for key, value in self.pathogen.items()}
        self.interactions.set_pathogen_settings(pathogen)

    def interact_all(self):
        verbose = self.verbose
        logger.debug('- Running InteractionEngine with C++ optimizations.')

        self._init_interactions()

        # Run the Interaction Engine functionality
        self.interactions.interact_all()
        results = self.interactions.get_population_df()
        self.population = results
        if verbose:
            logger.debug(
                '- Population states: {}'
                .format(
                    self
                    .population
                    .state
                    .value_counts(normalize=True)
                    .to_dict()
                )
            )

if __name__ == '__main__':
    print("Hi, I'm the InteractionEngine++. I'm not meant to be run directly.")
    print('To use me, please import InteractionEngineCpp in your script.')
