import sys
sys.path.append('..')
sys.path.append('../simfection')

from simfection.settings import SimfectionSettings
from simfection.population_engine import PopulationEngine
from simfection.connection_engine import ConnectionEngine
from simfection.interaction_engine import InteractionEngine

settings = SimfectionSettings(None)
settings.set_setting('cpp', False)

population_engine = PopulationEngine(settings)
population_engine.make_dummy()

connection_engine = ConnectionEngine(population_engine._df, settings)
connection_engine.create_connections(settings.get_setting('cpp'))

interaction_engine = InteractionEngine(connection_engine.connections, population_engine._df, settings)
interaction_engine.interact_all()

print(interaction_engine.population)
