from .connection_engine import ConnectionEngine
from .interaction_engine import InteractionEngine, pathogen
from .population_engine import PopulationEngine
from .update_engine import UpdateEngine
from .settings import SimfectionSettings
from .logger import SimfectionLogger
from .anchor import AnchorTracker

import pandas as pd
import numpy as np
import time
import logging


simfection_logger = SimfectionLogger(name=__name__)
logger = simfection_logger.get_logger()


class SimulationDay():
    def __init__(
            self,
            run_id,
            day_number: int = None,
            population: PopulationEngine = None,
            settings: SimfectionSettings = None) -> None:
        self.anchor_tracker = AnchorTracker()
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
            logger.debug(
                '- Population states: {}'
                .format(
                    self
                    ._df
                    .state
                    .value_counts(normalize=True)
                    .to_dict()
                )
            )
            self.population = population

        logger.debug('+ Saving starting population.')
        self.starting_population = self.population._df.copy()

    def run(self):
        self.anchor_tracker.create_anchor('run')
        verbose = self.settings.get_setting('verbose')
        self.connection_engine = ConnectionEngine(
            population=self.population._df,
            settings=self.settings
        )
        self.anchor_tracker.create_anchor('connection')
        cpp = self.settings.get_setting('cpp')
        self.connection_engine.create_connections(cpp)
        self.anchor_tracker.end_anchor('connection')
        connection_runtime = self.anchor_tracker.timing('connection')
        logger.debug('- Connections made in {:.2f} seconds.'.format(connection_runtime))

        self.interaction_engine = InteractionEngine(
            connections=self.connection_engine.connections,
            settings=self.settings,
            population=self.connection_engine.population
        )
        self.anchor_tracker.create_anchor('interact')
        self.interaction_engine.interact_all()
        self.anchor_tracker.end_anchor('interact')
        interact_runtime = self.anchor_tracker.timing('interact')
        logger.debug('- Interactions made in {:.2f} seconds.'.format(interact_runtime))

        self.update_engine = UpdateEngine(
            population=self.interaction_engine.population,
            settings=self.settings
        )
        self.anchor_tracker.create_anchor('update')
        self.update_engine.update_all()
        self.anchor_tracker.end_anchor('update')
        update_runtime = self.anchor_tracker.timing('update')
        logger.debug('- Updates made in {:.2f} seconds.'.format(update_runtime))

        self.population._df = self.update_engine.population

        self.anchor_tracker.end_anchor('run')
        run_runtime = self.anchor_tracker.timing('run')
        logger.debug('- Day ran successfully.')
        logger.debug('- Day simulated in {:.2f} seconds.'.format(connection_runtime))
        logger.debug('- Saving final population.')
        self.final_population = self.population._df
