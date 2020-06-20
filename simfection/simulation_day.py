import pandas as pd
import numpy as np
import time
import logging
# User defined imports
from .connection_engine import ConnectionEngine
from .connection_engine_cpp import ConnectionEngineCpp
from .interaction_engine import InteractionEngine
from .interaction_engine_cpp import InteractionEngineCpp
from .population_engine import PopulationEngine
from .update_engine import UpdateEngine
from .settings import SimfectionSettings
from .logger import SimfectionLogger


simfection_logger = SimfectionLogger(name=__name__)
logger = simfection_logger.get_logger()


class SimulationDay():
    def __init__(
            self,
            run_id,
            day_number: int = None,
            population: PopulationEngine = None,
            settings: SimfectionSettings = None) -> None:
        self.cpp = settings.get_setting('cpp')
        assert population is not None or settings is not None, (
            'Both population and settings are NoneType. At least one must be passed.'
        )
        logger.info('+ Simulating day {}.'.format(day_number))
        self.day_number = day_number
        self.settings = settings
        self.run_id = run_id
        if population is None:
            logger.info('+ Dummy population generated.')
            self.population = PopulationEngine(settings)
            self.population.make_dummy()

        else:
            logger.debug('+ Population loaded.')
            self.population = population

        logger.debug('+ Saving starting population.')
        self.starting_population = self.population._df.copy()

    def run(self):
        verbose = self.settings.get_setting('verbose')
        if not self.cpp:
            self.connection_engine = ConnectionEngine(
                population=self.population._df,
                settings=self.settings
            )
            self.connection_engine.create_connections()

            self.interaction_engine = InteractionEngineCpp(
                connections=self.connection_engine.connections,
                settings=self.settings,
                population=self.connection_engine.population
            )

            self.interaction_engine = InteractionEngine(
                connections=self.connection_engine.connections,
                settings=self.settings,
                population=self.connection_engine.population
            )
            
            self.interaction_engine.interact_all()

            self.update_engine = UpdateEngine(
                population=self.interaction_engine.population,
                settings=self.settings
            )
            self.update_engine.update_all()

            self.population._df = self.update_engine.population
        else:
            self.connection_engine = ConnectionEngineCpp(
                population=self.population._df,
                settings=self.settings
            )
            self.connection_engine.create_connections()

            self.interaction_engine = InteractionEngineCpp(
                connections=self.connection_engine.connections,
                settings=self.settings,
                population=self.connection_engine.population
            )

            self.update_engine = UpdateEngine(
                population=self.interaction_engine.population,
                settings=self.settings
            )
            self.update_engine.update_all()

            self.population._df = self.update_engine.population

        logger.debug('- Day ran successfully.')
        logger.debug('- Saving final population.')
        self.final_population = self.population._df
