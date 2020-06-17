#include <iostream>
#include <vector>
#include <unordered_map>
// algorithm allows for using std::rand() and std::unique()
#include <algorithm>
#include <ctime>

// User defined libraries
#include "interactions.h"

namespace Interactions {
    //-------------------------------------------------------//
    // Utility functions
    //-------------------------------------------------------//
    void print2DVect(std::vector<std::vector<int>> &vect){
        for(int i = 0; i < vect.size(); i++){
            for(int j = 0; j < vect[i].size(); j++){
                std::cout << vect[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void sort2DVectorRows(std::vector<std::vector<int>> &vect){
        for(int i = 0; i < vect.size(); i++){
            std::sort(vect[i].begin(), vect[i].end());
            std::sort(vect.begin(), vect.end());
        }
    }

    void get2DVectUniqueRows(std::vector<std::vector<int>> &vect){
        std::vector<std::vector<int>>::iterator it = std::unique(vect.begin(), vect.end()); 
    
        // Resizing the vector which removes undefined items.
        vect.resize(std::distance(vect.begin(), it)); 
    }

    bool isSameString(std::string &str1, std::string &str2){
        bool compare;
        if(str1.compare(str2) != 0){
            compare = false;
        }
        else{
            compare = true;
        }
        return compare;
    }

    //-------------------------------------------------------//
    // Define the Population Class
    //-------------------------------------------------------//
    Interactions::Population::Population(){
        // Do nothing
    }

    Interactions::Population::Population(std::vector<int> newAgents,
                                        std::vector<std::string> newStates,
                                        std::vector<std::vector<int>> newInfectedByList,
                                        std::vector<int> newDaysInfected,
                                        std::vector<int> newImmunities){
        this->agents = newAgents;
        this->states = newStates;
        this->infectedByList = newInfectedByList;
        this->daysInfected = newDaysInfected;
        this->immunities = newImmunities;
        // Now that we have all the information, initialize the agentStates hash table
        this->initAgentStates();
    }

    // Getters
    std::vector<int> Interactions::Population::getAgents(){
        return this->agents;
    }

    std::vector<std::string> Interactions::Population::getStates(){
        return this->states;
    }

    std::vector<std::vector<int>> Interactions::Population::getInfectedByList(){
        return this->infectedByList;
    }

    std::vector<int> Interactions::Population::getDaysInfected(){
        return this->daysInfected;
    }

    std::vector<int> Interactions::Population::getImmunities(){
        return this->immunities;
    }

    std::unordered_map<int, std::string> Interactions::Population::getAgentStates(){
        return this->agentStates;
    }

    // Setters
    void Interactions::Population::setAgents(std::vector<int> newAgents){
        this->agents = newAgents;
    }

    void Interactions::Population::setStates(std::vector<std::string> newStates){
        this->states = newStates;
    }

    void Interactions::Population::setInfectedByList(std::vector<std::vector<int>> newInfectedByList){
        this->infectedByList = newInfectedByList;
    }

    void Interactions::Population::setDaysInfected(std::vector<int> newDaysInfected){
        this->daysInfected = newDaysInfected;
    }

    void Interactions::Population::setImmunities(std::vector<int> newImmunities){
        this->immunities = newImmunities;
    }

    void Interactions::Population::initAgentStates(){
        // Loop through the entire agents list and initialize the agentStates unordered_map
        // to allow for faster querying later
        // Remember that agentStates has type:
        // std::unordered_map<int, std::string> agentStates;
        for(int i = 0; i < this->agents.size(); i++){
            agentStates[this->agents[i]] = this->states[i];
        }
    }


    //-------------------------------------------------------//
    // Define the Connections Class
    //-------------------------------------------------------//
    Interactions::Connections::Connections(){
        // Do nothing
    }

    Interactions::Connections::Connections(std::vector<int> newAgents, 
                            std::vector<std::vector<int>> newConnectionsList, 
                            std::vector<int> newNumConnections,
                            std::vector<int> newMaxConnections){
        this->agents = newAgents;
        this->connectionsList = newConnectionsList;
        this->numConnections = newNumConnections;
        this->maxConnections = newMaxConnections;
        // Do nothing
    }

    // Getters
    std::vector<int> Interactions::Connections::getAgents(){
        return this->agents;
    }

    std::vector<std::vector<int>> Interactions::Connections::getConnectionsList(){
        return this->connectionsList;
    }

    std::vector<int> Interactions::Connections::getNumConnections(){
        return this->numConnections;
    }

    std::vector<int> Interactions::Connections::getMaxConnections(){
        return this->maxConnections;
    }

    // Setters
    void Interactions::Connections::setAgents(std::vector<int> newAgents){
        this->agents = newAgents;
    }

    void Interactions::Connections::setConnectionsList(std::vector<std::vector<int>> newConnectionsList){
        this->connectionsList = newConnectionsList;
    }

    void Interactions::Connections::setNumConnections(std::vector<int> newNumConnections){
        this->numConnections = newNumConnections;
    }

    void Interactions::Connections::setMaxConnections(std::vector<int> newMaxConnections){
        this->maxConnections = newMaxConnections;
    }


    //-------------------------------------------------------//
    // Define the Interactions Class
    //-------------------------------------------------------//
    Interactions::Interactions(){
        // Seed the random number generator
        std::srand((unsigned int)time(NULL));
    }

    // Setters
    void Interactions::setConnections(std::vector<int> newAgents, 
                                std::vector<std::vector<int>> newConnectionsList, 
                                std::vector<int> newNumConnections,
                                std::vector<int> newMaxConnections){
        this->connections = Connections(newAgents, 
                                        newConnectionsList, 
                                        newNumConnections, 
                                        newMaxConnections);
        // Seed the random number generator
        std::srand((unsigned int)time(NULL));
    }

    void Interactions::setPopulation(std::vector<int> newAgents,
                                    std::vector<std::string> newStates,
                                    std::vector<std::vector<int>> newInfectedByList,
                                    std::vector<int> newDaysInfected,
                                    std::vector<int> newImmunities){
        this->population = Population(newAgents, 
                                    newStates,
                                    newInfectedByList,
                                    newDaysInfected,
                                    newImmunities);
    }

    void Interactions::setPathogenSettings(std::unordered_map<std::string, float> newPathogenSettings){
        this->pathogenSettings = newPathogenSettings;
    }

    // Getters
    Interactions::Connections Interactions::getConnections(){
        return this->connections;
    }

    Interactions::Population Interactions::getPopulation(){
        return this->population;
    }

    std::unordered_map<std::string, float> Interactions::getPathogenSettings(){
        return this->pathogenSettings;
    }

    // Interaction Engine functions
    bool Interactions::isSameString(std::string &str1, std::string &str2){
        bool compare;
        if(str1.compare(str2) != 0){
            compare = false;
        }
        else{
            compare = true;
        }
        return compare;
    }

    std::vector<std::vector<int>> Interactions::getUniqueConnections(Interactions::Connections thisConnections){
        std::vector<std::vector<int>> interaction_pairs;
        // Get connection lists that are > 0 in length/size
        std::vector<std::vector<int>> connectionsList = thisConnections.getConnectionsList();
        std::vector<int> agents = thisConnections.getAgents();
        if(connectionsList.size() != agents.size()){
            throw "agents and connectionsList vectors are not same size!";
        }
        // Hold the connections that are > 0 in another 2D vector
        for(int i = 0; i < agents.size(); i++){
            if(connectionsList[i].size() > 0){
                // Generate a vector of all pairs of agent_a : agent_b's from the agentsWithNonZeroConnectionsList
                int agentWithNonZeroConnections = agents[i];
                for(int connection : connectionsList[agentWithNonZeroConnections]){
                    // Should have the form of {agentWithNonZeroConnections, connection}
                    std::vector<int> pair = {agentWithNonZeroConnections, connection};
                    interaction_pairs.push_back(pair);
                }
            }
        }

        // Get rid of all duplicate agent_a : agent_b pairs
        sort2DVectorRows(interaction_pairs);
        get2DVectUniqueRows(interaction_pairs);

        // return a 2D vector of the interaction pairs
        return interaction_pairs;
    }

    std::pair<bool, std::pair<int, int>> Interactions::qualify_interaction(std::pair<std::pair<int, std::string>, std::pair<int, std::string>> pair){
        // Interact the pair 
        // interaction_qualification pair denotes
        // <bool shouldAgentsInteract, <agentAID, agentBID>>
        std::pair<bool, std::pair<int, int>> interaction_qualification;
        // Fill return variables with default return values
        interaction_qualification.first = false;
        std::pair<int, int> infected_susceptible_ids;
        infected_susceptible_ids.first = -1;
        infected_susceptible_ids.second = -1;
        interaction_qualification.second = infected_susceptible_ids;
        // Unpack the input values for readability
        int agentAID = pair.first.first;
        std::string agentAState = pair.first.second;
        int agentBID = pair.second.first;
        std::string agentBState = pair.second.second;

        if(agentAState != agentBState){
            if((isSameString(agentAState, this->inf) || isSameString(agentBState, this->inf)) && (isSameString(agentAState, this->sus) || isSameString(agentBState, this->sus))){
                // Determine who is infected and who is susceptible
                int infected_agent;
                int susceptible_agent;
                if(isSameString(agentAState, this->inf)){
                    infected_agent = agentAID;
                    susceptible_agent = agentBID;
                }
                else{
                    infected_agent = agentBID;
                    susceptible_agent = agentAID;
                }

                // Determine if the infected agent is contagious
                // Cast days_infected to int after extracting it
                float float_contagious_period = this->pathogenSettings["contagious_period"];
                int contagious_period = static_cast <int> (float_contagious_period);
                int days_infected = this->population.getDaysInfected()[infected_agent];

                // Determine if susceptible is immune
                // Get the agent's immunity days remaining
                int immunity_days_remaining = this->population.getImmunities()[infected_agent];
                // If the infected person is still contagious and the susceptible person doesn't have immunity
                // Then infect the susceptible person
                if(days_infected < contagious_period && immunity_days_remaining == 0){
                    // Set that the two should interact
                    interaction_qualification.first = true;
                    // Set the infected agent's ID
                    infected_susceptible_ids.first = infected_agent;
                    infected_susceptible_ids.second = susceptible_agent;
                    // Set the <infected, susceptible> ID pair in the qualification pair
                    interaction_qualification.second = infected_susceptible_ids;
                }
            }
        }

        return interaction_qualification;
    }

    void Interactions::interact(std::vector<int> pair){
        // Get the agent #s and their states as a couple of pairs
        std::unordered_map<int, std::string> agentStates = this->population.getAgentStates();
        int agentAID = pair[0];
        int agentBID = pair[1];
        std::string agentAState = agentStates[agentAID];
        std::string agentBState = agentStates[agentBID];
        std::pair<int, std::string> agentAIDState;
        agentAIDState.first = agentAID;
        agentAIDState.second = agentAState;
        std::pair<int, std::string> agentBIDState; 
        agentBIDState.first = agentBID;
        agentBIDState.second = agentBState;
        std::pair<std::pair<int, std::string>, std::pair<int, std::string>> agentPair;
        agentPair.first = agentAIDState;
        agentPair.second = agentBIDState;
        // Qualify the interaction and unpack the values
        std::pair<bool, std::pair<int, int>> interaction_qualification = this->qualify_interaction(agentPair);
        bool qualified_interaction = interaction_qualification.first;
        int infected_agent_id = interaction_qualification.second.first;
        int susceptible_agent_id = interaction_qualification.second.second;
        // Draw a random number from 0.0 to 1.0
        float rand_num = static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
        // Get the infection_rate
        // Load the pathogen settings
        std::unordered_map<std::string, float> pathogenSettings = this->getPathogenSettings();
        float infection_rate = pathogenSettings["infection_rate"];
        // Using that random number and the bool from interaction_qualification, 
        // if interaction_qualification is True and the random number < infection_rate
        // then update the susceptible person's state to 'inf' in the population object and 
        // append to the infected_list of the population object with the infecter's agent #
        if(qualified_interaction && rand_num < infection_rate){
            // Update the susceptible agent's (interaction_qualification.second.second) 
            // state to "inf" in the population agentStates and append the infecting agent's 
            // ID (interaction_qualification.second.first) to the susceptible agent's infectedByList.
            std::vector<std::string> newStates = this->population.getStates();
            // Update the susceptible agent's state
            newStates[susceptible_agent_id] = "inf";
            this->population.setStates(newStates);
            // Append the infecting agent's ID to the suscetible agent's infectedByList
            std::vector<std::vector<int>> newInfectedByList = this->population.getInfectedByList();
            newInfectedByList[susceptible_agent_id].push_back(infected_agent_id);
            this->population.setInfectedByList(newInfectedByList);
        }

    }

    void Interactions::interactAll(){
        // The affected object in this function via subcalls is this->population 
        // which is eventually what we'll want to return in order to fulfill the
        // same functionality as the python code
        std::vector<std::vector<int>> interaction_pairs;
        // Get all the unique connections
        try {
            interaction_pairs = this->getUniqueConnections(this->connections);
        } catch (const char* msg) {
            std::cerr << (*msg) << std::endl;
        }
        // For each connection, interact them
        for(std::vector<int> pair : interaction_pairs){
            this->interact(pair);
        }
    }

} // end namespace Interactions

//-------------------------------------------------------//
// Main function for debugging and testing
//-------------------------------------------------------//
int main(){
    // Strings to use for agent states
    std::string inf = "inf";
    std::string sus = "sus";
    std::string dead = "dead";
    // values for connection list stub
    std::vector<int> newAgents = {0, 1, 2, 3, 4, 5};
    std::vector<std::vector<int>> newConnectionsList = {{1, 2}, {0, 3}, {0, 3}, {1, 4, 2}, {3, 5}, {4}};
    std::vector<int> numConnections = {2, 2, 2, 2, 2, 2};
    std::vector<int> maxConnections = {3, 3, 3, 3, 3, 3};

    // values for population stub
    std::vector<int> popNewAgents = {0, 1, 2, 3, 4, 5};
    std::vector<std::string> newStates = {inf, inf, sus, sus, sus, sus};
    std::vector<std::vector<int>> newInfectedByList = {{}, {}, {}, {}, {}, {}};
    std::vector<int> newDaysInfected = {1, 1, 0 ,0, 0, 0};
    std::vector<int> newImmunities = {0, 0, 2, 0, 0, 0};

    // values for pathogenSettings stub
    std::unordered_map<std::string, float> newPathogenSettings;
    newPathogenSettings["infection_rate"] = 0.7;
    newPathogenSettings["recovery_rate"] = 0.1;
    newPathogenSettings["death_rate"] = 0.00;
    newPathogenSettings["spontaneous_rate"] = 0.00;
    newPathogenSettings["testing_accuracy"] = -1.0;
    newPathogenSettings["immunity_period"] = 100.0;
    newPathogenSettings["contagious_period"] = 99.0;
    newPathogenSettings["incubation_period"] = 0.0;

    Interactions::Interactions interactions = Interactions::Interactions();
    interactions.setConnections(newAgents, newConnectionsList, numConnections, maxConnections);
    interactions.setPopulation(popNewAgents, newStates, newInfectedByList, newDaysInfected, newImmunities);
    interactions.setPathogenSettings(newPathogenSettings);
    interactions.interactAll();
    Interactions::Interactions::Population population = interactions.getPopulation();
    
    std::cout << "infectedByList: " << std::endl;
    std::vector<std::vector<int>> infectedByList = population.getInfectedByList();
    for(std::vector<int> v : infectedByList){
        for(int i : v){
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}