from libcpp.vector cimport vector
from libcpp cimport bool
from libcpp.unordered_map cimport unordered_map
from libcpp.utility cimport pair
from libcpp.string cimport string

# Declare the class with cdef
cdef extern from "simfection_cpp.h" namespace "Connections":
    cdef cppclass Connections:
        # private:
        int size 
        # public: 
        Connections() except +
        Connections(int) except +
        int getSize()
        void setSize(int)
        bool existsInVector(int, vector[int])
        vector[int] genConnectionsMaxVector(int, int, int)
        vector[int] getAvailable(int, vector[int], vector[vector[int]])
        vector[vector[int]] genRandomNetwork(vector[int], bool, bool)


# Declare the Population nested/inner class
cdef extern from "simfection_cpp.h" namespace "Interactions::Interactions::Population":
    cdef cppclass Population:
    # private:
        vector[int] agents
        vector[string] states
        vector[vector[int]] infectedByList
        vector[int] daysInfected
        vector[int] immunities
        unordered_map[int, string] agentStates
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
        unordered_map[int, string] getAgentStates()
        # Setters
        void setAgents(vector[int])
        void setStates(vector[string])
        void setInfectedByList(vector[vector[int]])
        void setDaysInfected(vector[int])
        void setImmunities(vector[int] newImmunities)
        void initAgentStates()


# Declare the Connections nested/inner class
cdef extern from "simfection_cpp.h" namespace "Interactions::Interactions::InteractConnections":
    # Connections subclass
    cdef cppclass InteractConnections:
        # private:
        vector[int] agents
        vector[vector[int]] connectionsList
        vector[int] numConnections
        vector[int] maxConnections
        # public: 
        InteractConnections() except +
        InteractConnections(vector[int], 
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
cdef extern from "simfection_cpp.h" namespace "Interactions":
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
        void setPathogenSettings(unordered_map[string, float])
        # Getters
        Population getPopulation()
        InteractConnections getConnections()
        unordered_map[string, float] getPathogenSettings()
        pair[int, string] getAgentIDAndStatePair(int)
        # Interaction Engine Functions
        bool isSameString(string str1, string str2)
        vector[vector[int]] getUniqueConnections(InteractConnections thisConnections)
        pair[bool, pair[int, int]] qualify_interaction(pair[pair[int, string], pair[int, string]])
        void interact(vector[int])
        void interactAll()
        # private:
        Population population
        InteractConnections connections
        string inf
        string sus
        string dead
        unordered_map[string, float] pathogenSettings

