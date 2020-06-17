# Wrapping the connections list code 
# distutils: sources = connections.cpp
# distutils: language = c++

from libcpp.vector cimport vector
from libcpp.map cimport map
from libcpp.utility cimport pair
from libcpp cimport bool
from libcpp.string cimport string

from connections cimport Connections
from interactions cimport Interactions
# from interactions cimport Interactions.Population as Population
ctypedef Interactions.Population Population
# from interactions cimport Interactions.Connections as interactionsConnections
ctypedef Interactions.Connections interactionsConnections

# Create a Cython extension type which holds a C++ instance
# as an attribute and create a bunch of forwarding methods
# Python extension type.
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


cdef class PyInteractions:
    cdef Interactions c_interactions

    # Constructor
    def __cinit__(self):
        # We have an empty construct at the moment
        pass

    # Setters
    def set_population(self, 
                       vector[int] newAgents,
                       vector[string] newStates,
                       vector[vector[int]] newInfectedByList,
                       vector[int] newDaysInfected,
                       vector[int] newImmunities):
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
                              map[string, float] newPathogenSettings):
        self.c_interactions.setPathogenSettings(newPathogenSettings)
    
    # Getters
    def get_population(self):
        pass
    
    def get_connections(self):
        pass
    
    def get_pathogen_settings(self):
        pass
    
    def get_agent_id_and_state_pair(self, int agent_id):
        pass

    # Interaction Engine Functions
    def is_same_string(self, string str1, string str2):
        pass

    def get_unique_connections(self):
        if self.get_connections():
            # Connections is non-empty, call on available connections in object
            return self.c_interactions.getUniqueConnections(self.c_interactions.getConnections())
        else:
            # Connections was empty, so just return None
            return None

    def qualify_interaction(self, pair[pair[int, string], pair[int, string]] pair):
        pass

    def interact(self, vector[int] pair):
        pass

    def interact_all(self):
        pass

    # Function for stitching together a pandas DataFrame to return 
    # for the downstream modules
    def get_population_df(self):
        pass