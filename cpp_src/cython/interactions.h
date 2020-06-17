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
        std::unordered_map<int, std::string> agentStates;

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
        std::unordered_map<int, std::string> getAgentStates();
        // Setters
        void setAgents(std::vector<int> newAgents);
        void setStates(std::vector<std::string> newStates);
        void setInfectedByList(std::vector<std::vector<int>> newInfectedByList);
        void setDaysInfected(std::vector<int> newDaysInfected);
        void setImmunities(std::vector<int> newImmunities);
        void initAgentStates();

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
    // Setters
    void setPopulation(std::vector<int> newAgents,
                        std::vector<std::string> newStates,
                        std::vector<std::vector<int>> newInfectedByList,
                        std::vector<int> newDaysInfected,
                        std::vector<int> newImmunities);
    void setConnections(std::vector<int> newAgents, 
                         std::vector<std::vector<int>> newConnectionsList, 
                         std::vector<int> newNumConnections,
                         std::vector<int> newMaxConnections);
    void setPathogenSettings(std::unordered_map<std::string, float> newPathogenSettings);
    // Getters
    Population getPopulation();
    Connections getConnections();
    std::unordered_map<std::string, float> getPathogenSettings();
    std::pair<int, std::string> getAgentIDAndStatePair(int agent_id);

    // Interaction Engine functions
    bool isSameString(std::string &str1, std::string &str2);
    std::vector<std::vector<int>> getUniqueConnections(Connections thisConnections);
    std::pair<bool, std::pair<int, int>> qualify_interaction(std::pair<std::pair<int, std::string>, std::pair<int, std::string>> pair);
    void interact(std::vector<int> pair);
    void interactAll();

    private:
    Population population;
    Connections connections;
    // Default std::string states, probably better to implement with enums
    std::string inf = "inf";
    std::string sus = "sus";
    std::string dead = "dead";
    // unordered_map key, value is: setting_name, setting_value
    // For pathogen_settings from Python, we should expect default values of 
    // infection_rate = 0.4
    // recovery_rate = 0.1
    // death_rate = 0.00
    // spontaneous_rate = 0.00
    // testing_accuracy = None (What is None converted to in C++ via Cython?)
    //     see: https://stackoverflow.com/questions/54117082/cython-cannot-declare-none-type
    // immunity_period = 100
    // contagious_period = 99
    // incubation_period = 0
    // We will have to make sure to type cast any potential ints to floats in the .pyx / .pyd file. 
    std::unordered_map<std::string, float> pathogenSettings;

};



