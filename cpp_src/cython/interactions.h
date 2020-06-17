#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Interactions {
    // private:
    class Population {
        // private: 
        public:
        std::vector<int> agents;
        std::vector<std::string> states;
        std::vector<std::vector<int>> infectedByList;
        std::vector<int> daysInfected;
        std::vector<int> immunities;
        Population();
        Population(std::vector<int> newAgents,
                   std::vector<std::string> newStates,
                   std::vector<std::vector<int>> newInfectedByList,
                   std::vector<int> newDaysInfected,
                   std::vector<int> newImmunities);
    };

    class Connections {
        // private:
        public:
        std::vector<int> agents;
        std::vector<std::vector<int>> connectionsList;
        std::vector<int> numConnections;
        std::vector<int> maxConnections;
        Connections();
        Connections(std::vector<int> newAgents, 
                    std::vector<std::vector<int>> newConnectionsList, 
                    std::vector<int> newNumConnections,
                    std::vector<int> newMaxConnections);
    };

    public:
    Population population;
    Connections connections;
    Interactions();
    void initPopulation(std::vector<int> newAgents,
                        std::vector<std::string> newStates,
                        std::vector<std::vector<int>> newInfectedByList,
                        std::vector<int> newDaysInfected,
                        std::vector<int> newImmunities);
    void initConnections(std::vector<int> newAgents, 
                         std::vector<std::vector<int>> newConnectionsList, 
                         std::vector<int> newNumConnections,
                         std::vector<int> newMaxConnections);
    Population interactAll();

};



