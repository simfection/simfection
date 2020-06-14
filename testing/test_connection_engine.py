import sys
sys.path.append('../')
sys.path.append('../simfection')

import unittest
import numpy as np
from invoke import run
from simfection.settings import SimfectionSettings
from simfection.population_engine import PopulationEngine
from simfection.connection_engine import ConnectionEngine

class TestConnectionEngine(unittest.TestCase):

    def setUp(self):
        self.settings = SimfectionSettings()
        self.population = PopulationEngine(self.settings)
        self.population.synthesize_population()
        # Seed the numpy random number generator so results are repeatable
        np.random.seed(0)
        self.connection_engine = ConnectionEngine(
        population=self.population._df,
            settings=self.settings
        )
        self.connection_engine.create_connections()
        self.connections = self.connection_engine.connections
        super(TestConnectionEngine, self).setUp()

    def tearDown(self):
        # Remove any simfection.log files that are made
        cmd = "rm \'simfection.log\'"
        result = run(cmd, hide=True, warn=True)
        if result.ok:
            print("simfection.log succesfully deleted")
        else:
            print("Unable to delete simfection.log file, please delete manually.")
        super(TestConnectionEngine, self).tearDown()
        

    def test_correct_number_of_connections(self):
        # The number of connections in the connection list should always be 
        # less than or equal to the max connection number. 
        for i in range(0, self.connections['connections'].size):
            connection_list = self.connections['connections'][i]
            max_connections = self.connections['max_connections'][i]
            self.assertLessEqual(len(connection_list), max_connections)

    def test_no_repeat_connections(self):
        # A connection list shouldn't have repeat connections
        for connection_list in self.connections['connections']:
            for element in connection_list:
                self.assertLess(connection_list.count(element), 2)

if __name__ == '__main__':
    unittest.main()