from libcpp.vector cimport vector
from libcpp.map cimport map
from libcpp.utility cimport pair
from libcpp cimport bool
from libcpp.string import string

# Declare the Population nested/inner class
cdef extern from "interactions.h" namespace "Interactions::Population":
    cdef cppclass Population:
    # private:
        vector[int] agents
        vector[string] states
        vector[vector[int]] infectedByList
        vector[int] daysInfected
        vector[int] immunities
        map[int, string] agentStates
        # public:
        Population() except +
        Population(vector[int],
                   vector[string],
                   vector[vector[int]],
                   vector[int],
                   vector[int]) except +
        # Getters
        vector[int] getAgents()
        vector[string] getStates()
        vector[vector[int]] getInfectedByList()
        vector[int] getDaysInfected()
        vector[int] getImmunities()
        map[int, string] getAgentStates()
        # Setters
        void setAgents(vector[int])
        void setStates(vector[string])
        void setInfectedByList(vector[vector[int]])
        void setDaysInfected(vector[int])
        void setImmunities(vector[int] newImmunities)
        void initAgentStates()


# Declare the Connections nested/inner class
cdef extern from "interactions.h" namespace "Interactions::Connections":
    # Connections subclass
    cdef cppclass Connections:
        # private:
        vector[int] agents
        vector[vector[int]] connectionsList
        vector[int] numConnections
        vector[int] maxConnections
        # public: 
        Connections() except +
        Connections(vector[int], 
                    vector[vector[int]], 
                    vector[int],
                    vector[int]) except +
        # Getters
        vector[int] getAgents()
        vector[vector[int]] getConnectionsList()
        vector[int] getNumConnections()
        vector[int] getMaxConnections()
        # Setters
        void setAgents(vector[int])
        void setConnectionsList(vector[vector[int]])
        void setNumConnections(vector[int])
        void setMaxConnections(vector[int])


# Declare the Interactions class
cdef extern from "interactions.h" namespace "Interactions":
    cdef cppclass Interactions:
        # public: 
        # Constructor
        Interactions() except +
        # Setters
        void setPopulation(vector[int],
                           vector[string],
                           vector[vector[int]],
                           vector[int],
                           vector[int])
        void setConnections(vector[int], 
                            vector[vector[int]], 
                            vector[int],
                            vector[int])
        void setPathogenSettings(map[string, float])
        # Getters
        Population getPopulation()
        Connections getConnections()
        map[string, float] getPathogenSettings()
        pair[int, string] getAgentIDAndStatePair(int)
        # Interaction Engine Functions
        bool isSameString(string str1, string str2)
        vector[vector[int]] getUniqueConnections(Connections thisConnections)
        pair[bool, pair[int, int]] qualify_interaction(pair[pair[int, string], pair[int, string]])
        void interact(vector[int])
        void interactAll()
        # private:
        Population population
        Connections connections
        string inf
        string sus
        string dead
        map[string, float] pathogenSettings

