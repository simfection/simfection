"""Creates a network of hand-shake connections as part of model run.

The ConnectionEngine takes a PopulationEngine object and an average number of connections
and randomly creates a hand-shake network of interactions within the population.

  Typical usage example:

    from settings import SimfectionSettings
    from population_engine import PopulationEngine
    from connection_engine import ConnectionEngine

    # Settings
    settings = SimfectionSettings()

    # Synthesize population
    population = PopulationEngine(settings)
    population.synthesize_population()

    # Create connections
    connection_engine = ConnectionEngine(
      population=population._df,
      settings=settings
    )
    connection_engine.create_connections()
"""
import time
import sys
import pandas as pd
import numpy as np
from invoke import run
# User defined imports
import network
from .settings import SimfectionSettings
from .logger import SimfectionLogger

simfection_logger = SimfectionLogger(name=__name__)
logger = simfection_logger.get_logger()

sys.setrecursionlimit(10**6)


class ConnectionEngine():
    """Creates a connections list for each agent in a population following
    the hand-shake protocol.

    Longer class information....
    Longer class information....

    Attributes:
        population: A pandas DataFrame representing a population attribute from
            a PopulationEngine instance.
        mean_connections: An integer average number of connections for each
            agent.
        experiment: A boolean indicating whether or not this instance is being
            used for a timing experiment.
        verbose: A boolean indicating whether or not print debugging
            information to the console.
        std: An integer standard deviation for the distribution from which
            each agent draws to determine the maximum number of connections
            they will have.
        size: An interger number of samples to take from the normal distribution
            from which each agent draws to determine the maximum number of
            connections.
        connections: Initialized as a Nonetype. This will be set in the
            create_connections method.
    """

    def __init__(self, population: pd.DataFrame = None,
                 settings: SimfectionSettings = None) -> None:
        logger.debug('+ Initializing connection engine.')
        self.population = population
        self.mean_connections = settings.get_setting('mean_connections')
        self.experiment = settings.get_setting('experiment')
        self.verbose = settings.get_setting('verbose')
        self.std = settings.get_setting('std')
        self.size = settings.get_setting('size')
        self.connections = None
        self.cpp = settings.get_setting('cpp')

    def _max_connections(self,
                         std: int = None,
                         size: int = None):
        distribution = np.round(
            np.random.normal(
                loc=self.mean_connections,  # Mean
                scale=std,  # Standard Deviation
                size=size  # sample size
            )
        )

        choice = int(np.random.choice(distribution))
        while choice < 0:
            choice = int(np.random.choice(distribution))

        return choice

    def _build_connection_list(self, connections):
        # Use the wrapped C++ PyConnections object to generate a random network instead
        if self.experiment:
            _start = time.time()
        # Run functions here
        # Instantiate a PyConnections object
        size = connections['agent'].size
        net = network.PyConnections(size)
        # Get the connection limits as a list to pass into function later
        connections_max_list = connections['max_connections'].values.tolist()
        # Generate the random network 2D list to convert to DataFrame form later
        start_gen_random_network = time.time()
        random_network = net.gen_random_network(connections_max_list)
        end_gen_random_network = time.time()
        runtime_gen_random_network = end_gen_random_network - start_gen_random_network
        logger.debug(f'- Random network generated in {runtime_gen_random_network} seconds.')
        # Update the connections DataFrame using the 2D list
        new_connections = pd.DataFrame({'connections': random_network})
        connections.update(new_connections)
        # Update the num_connections part of the connections DataFrame
        # TODO(aogle): update the implementation so it doesn't require magic numbers
        for i in range(0, connections['connections'].size):
            connections.iloc[i, 2] = len(connections.iloc[i, 1])
        if self.experiment:
            runtime_available = time.time() - _start
            runtime_choose = runtime_available
            return connections, runtime_available, runtime_choose
        return connections

    def create_connections(self):
        """Creates connection list for each agent.

        A connections DataFrame is created and returned using the agents in the
        PopulationEngine instance self attribute. This method and return object
        spec are required inputs for the next step,which is the interaction
        engine.

        Returns:
            A pandas DataFrame representing the interaction network for a
            simulation day. Each row is a record that is indexed to an agent in
            the  PopulationEngine instance. A description of the columns
            folowed by an example record are given below.

            DataFrame Columns:
                'agent': unqiue agent ID indexed to the PopulationEngine
                'connections': list of agent IDs with whom the agent had
                    an interaction
                'num_connections': length of list in connections columns
                'max_connections': maximum number of connections the agent can
                    have as randomly drawn

            Example:
                agent connections  num_connections  max_connections
                0         [1]                1                1
                1      [0, 3]                2                1
                2         [5]                1                1
                3      [1, 4]                2                1
                4      [3, 8]                2                1
        """
        std = self.std
        size = self.size
        if self.experiment:
            logger.debug('- Entering experiment mode.')

        logger.debug('- Creating connections.')
        not_dead = self.population.query('state != "dead"').index
        connections = pd.DataFrame(
            {
                'agent': list(range(len(not_dead))),
                'connections': [[] for i in not_dead],
                'num_connections': [0 for i in not_dead],
                'max_connections': [
                    self._max_connections(std=std, size=size)
                    for i in not_dead
                ]
            }
        )

        _update = len(not_dead)*0.1
        if self.experiment:
            runtime = {
                'available': [],
                'choose': []
            }

        if self.experiment:
            connections, runtime_available, runtime_choose = self._build_connection_list(
                connections,
            )
            runtime['available'].append(runtime_available)
            runtime['choose'].append(runtime_choose)
        else:
            self._build_connection_list(connections)
        self.connections = connections
        logger.debug('- All connections made successfully with C++ optimization.')
        if self.experiment:
            return connections, runtime
        return None


if __name__ == '__main__':
    print("Hi, I'm the ConnectionEngine++. I'm not meant to be run directly.")
    print('To use me, please import ConnectionEngineCpp in your script.')
