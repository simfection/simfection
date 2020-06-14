import sys
sys.path.append('../')
sys.path.append('../simfection')

import unittest
import numpy as np
from invoke import run
from simfection.settings import SimfectionSettings
from simfection.population_engine import PopulationEngine

class TestPopulationEngine(unittest.TestCase):

    def setUp(self):
        self.settings = SimfectionSettings()
        # Use a larger population and non-default initial states
        initial_states = {'inf': 0.15, 'dead': 0.2}
        self.settings.set_setting('initial_states', initial_states)
        self.settings.set_setting('num_people', 1000)
        self.population = PopulationEngine(self.settings)
        self.population.synthesize_population()
        # Seed the numpy random number generator to keep results repeatable
        np.random.seed(0)
        super(TestPopulationEngine, self).setUp()

    def tearDown(self):
        # Remove any simfection.log files that are made
        cmd = "rm \'simfection.log\'"
        result = run(cmd, hide=True, warn=True)
        if result.ok:
            print("simfection.log succesfully deleted")
        else:
            print("Unable to delete simfection.log file, please delete manually.")
        super(TestPopulationEngine, self).tearDown()

    def test_initial_states_setting_self(self):
        initial_states = self.settings.get_setting('initial_states')
        population = self.population._df
        population_size = self.settings.get_setting('num_people')
        for state in initial_states:
            percent = initial_states[state]
            num_state = population.query(f'state == "{state}"').index
            percent_state = num_state.size / population_size
            self.assertAlmostEqual(percent, percent_state, places=1)

if __name__ == '__main__':
    unittest.main()