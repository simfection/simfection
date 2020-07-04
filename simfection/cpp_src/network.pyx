# Wrapping the connections list code 
# distutils: sources = ./simfection/cpp_src/simfection_cpp.cpp
# distutils: language = c++
import pandas as pd

from libcpp.vector cimport vector
from libcpp cimport bool
from libcpp.unordered_map cimport unordered_map
from libcpp.utility cimport pair
from libcpp.string cimport string

from simfection_cpp cimport Connections, Interactions, Population, InteractConnections

# Create a Cython extension type which holds a C++ instance
# as an attribute and create a bunch of forwarding methods
# Python extension type.

# Define API for C++ Connections object
cdef class PyConnections:
    cdef Connections c_connections  # Hold a C++ instance which we're wrapping

    def __cinit__(self, int size):
        self.c_connections = Connections(size)

    def get_size(self):
        return self.c_connections.getSize()

    def set_size(self, int size):
        self.c_connections.setSize(size)

    def gen_connections_max_vector(self, int minConnections, int maxConnections, int size):
        return self.c_connections.genConnectionsMaxVector(minConnections, maxConnections, size)

    def get_available(self, int personID, vector[int] connectionsMax, vector[vector[int]] connections):
        return self.c_connections.getAvailable(personID, connectionsMax, connections)

    def gen_random_network(self, vector[int] connectionsMax, bool verbose=False, bool testing=False):
        return self.c_connections.genRandomNetwork(connectionsMax, verbose, testing)


# Define the API For the C++ Interactions object
cdef class PyInteractions:
    cdef Interactions c_interactions

    # Constructor
    def __cinit__(self):
        # We have an empty construct at the moment
        self.c_interactions = Interactions()

    # Setters
    def set_population(self, 
                       vector[int] newAgents,
                       vector[string] newStates,
                       vector[vector[int]] newInfectedByList,
                       vector[int] newDaysInfected,
                       vector[int] newImmunities):
        # newInfectedByList can sometimes contain NoneType objects
        self.c_interactions.setPopulation(newAgents, 
                                     newStates,
                                     newInfectedByList,
                                     newDaysInfected,
                                     newImmunities)

    def set_connections(self, 
                        vector[int] newAgents, 
                        vector[vector[int]] newConnectionsList, 
                        vector[int] newNumConnections,
                        vector[int] newMaxConnections):
        self.c_interactions.setConnections(newAgents,
                                      newConnectionsList,
                                      newNumConnections,
                                      newMaxConnections)

    def set_pathogen_settings(self,
                              pathogenSettings):
        # Go through all the values in the pathogen settings dict and make sure any
        # that are None are set to -1. 
        for key, value in pathogenSettings.items():
            if value is None: 
                pathogenSettings[key] = -1.0

        cdef unordered_map[string, float] newPathogenSettings = pathogenSettings
        self.c_interactions.setPathogenSettings(newPathogenSettings)

    def interact_all(self):
        self.c_interactions.interactAll()

    # Function for stitching together a pandas DataFrame to return 
    # for the downstream modules
    def get_population_df(self):
        agents = self.c_interactions.getPopulation().getAgents()
        cdef vector[string] states = self.c_interactions.getPopulation().getStates()
        # Decode the states list from unicode bytes to ASCII str
        str_states = [state.decode('UTF-8') for state in states]
        infectedByList = self.c_interactions.getPopulation().getInfectedByList()
        daysInfected = self.c_interactions.getPopulation().getDaysInfected()
        immunities = self.c_interactions.getPopulation().getImmunities()
        # Package it into a dataframe
        data = {'agent': agents,
                'state': str_states,
                'infected_by': infectedByList,
                'days_infected': daysInfected,
                'immunity': immunities}
        result = pd.DataFrame(data)
        return result