import sys
sys.path.append('../')
sys.path.append('../simfection')

from simfection.connection_engine import ConnectionEngine
from simfection.population_engine import PopulationEngine
from simfection.settings import SimfectionSettings
import pandas as pd
from invoke import run

class ConnectionEngineProfiler:
    def __init__(self, pop_size=1000, cpp=False):
        self.pop_size = pop_size
        # Use default settings
        self.settings = SimfectionSettings(None)
        # Choose whether to use cpp optimization
        self.settings.set_setting('cpp', cpp)

    def tearDown(self):
        # Remove any simfection.log files that are made
        cmd = "rm \'simfection.log\'"
        result = run(cmd, hide=True, warn=True)
        if result.ok:
            print("simfection.log succesfully deleted")
        else:
            pass


    def _single_pop_experiment(self):
        # Set the population heres
        self.settings.set_setting('num_people', self.pop_size)
        popengine = PopulationEngine(self.settings)
        popengine.make_dummy()
        population = popengine._df
        connectengine = ConnectionEngine(population, self.settings)
        connectengine.create_connections(self.settings.get_setting('cpp'))

    def run_single_pop_test(self, pop_size=1000):
        self._single_pop_experiment(pop_size)
