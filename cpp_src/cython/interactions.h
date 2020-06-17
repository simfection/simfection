#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Interactions {
    public:
    class Population {
        private: 
        std::vector<int> agents;
        std::vector<std::string> states;
        std::vector<std::vector<int>> infectedByList;
        std::vector<int> daysInfected;
        std::vector<int> immunities;

        public:
        Population();
        Population(std::vector<int> newAgents,
                   std::vector<std::string> newStates,
                   std::vector<std::vector<int>> newInfectedByList,
                   std::vector<int> newDaysInfected,
                   std::vector<int> newImmunities);
        // Getters
        std::vector<int> getAgents();
        std::vector<std::string> getStates();
        std::vector<std::vector<int>> getInfectedByList();
        std::vector<int> getDaysInfected();
        std::vector<int> getImmunities();
        // Setters
        void setAgents(std::vector<int> newAgents);
        void setStates(std::vector<std::string> newStates);
        void setInfectedByList(std::vector<std::vector<int>> newInfectedByList);
        void setDaysInfected(std::vector<int> newDaysInfected);
        void setImmunities(std::vector<int> newImmunities);
    };

    class Connections {
        private:
        std::vector<int> agents;
        std::vector<std::vector<int>> connectionsList;
        std::vector<int> numConnections;
        std::vector<int> maxConnections;

        public:
        Connections();
        Connections(std::vector<int> newAgents, 
                    std::vector<std::vector<int>> newConnectionsList, 
                    std::vector<int> newNumConnections,
                    std::vector<int> newMaxConnections);
        // Getters
        std::vector<int> getAgents();
        std::vector<std::vector<int>> getConnectionsList();
        std::vector<int> getNumConnections();
        std::vector<int> getMaxConnections();
        // Setters
        void setAgents(std::vector<int> newAgents);
        void setConnectionsList(std::vector<std::vector<int>> newConnectionsList);
        void setNumConnections(std::vector<int> newNumConnections);
        void setMaxConnections(std::vector<int> newMaxConnections);
    };
    // Constructor
    Interactions();
    // Setter for population
    void initPopulation(std::vector<int> newAgents,
                        std::vector<std::string> newStates,
                        std::vector<std::vector<int>> newInfectedByList,
                        std::vector<int> newDaysInfected,
                        std::vector<int> newImmunities);
    // Setter for connections
    void initConnections(std::vector<int> newAgents, 
                         std::vector<std::vector<int>> newConnectionsList, 
                         std::vector<int> newNumConnections,
                         std::vector<int> newMaxConnections);
    // Getters
    Population getPopulation();
    Connections getConnections();
    std::vector<std::vector<int>> getUniqueConnections(Connections thisConnections);
    Population interactAll();

    private:
    Population population;
    Connections connections;

};



