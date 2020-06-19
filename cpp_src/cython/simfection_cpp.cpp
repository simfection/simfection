#include <iostream>
#include <vector>
#include <unordered_map>
// algorithm allows for using std::rand() and std::unique()
#include <algorithm>
#include <cmath>
#include <ctime>
#include <set>

// User defined libraries
#include "simfection_cpp.h"

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

    std::vector<std::vector<int>>& Interactions::Population::getInfectedByList(){
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

    // Generator Functions
    void Interactions::Population::genPopulation(int size, float infection_rate){
        std::string inf = "inf";
        std::string sus = "sus";
        std::vector<int> agents;
        std::vector<std::string> states;
        std::vector<std::vector<int>> infectedByList;
        std::vector<int> daysInfected;
        std::vector<int> immunities;
        // Generate the agents list
        for(int i = 0; i < size; i++){
            agents.push_back(i);
            float rand_num = static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
            if(rand_num < infection_rate){
                states.push_back(inf);
                daysInfected.push_back(1);
            }
            else{
                states.push_back(sus);
                daysInfected.push_back(0);
            }
            std::vector<int> empty_list = {};
            infectedByList.push_back(empty_list);
            immunities.push_back(0);
        }
        // Assign all the values to this object
        this->agents = agents;
        this->states = states;
        this->infectedByList = infectedByList;
        this->daysInfected = daysInfected;
        this->immunities = immunities;
    }


    //-------------------------------------------------------//
    // Define the Connections Class
    //-------------------------------------------------------//
    Interactions::InteractConnections::InteractConnections(){
        // Do nothing
    }

    Interactions::InteractConnections::InteractConnections(std::vector<int> newAgents, 
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
    std::vector<int> Interactions::InteractConnections::getAgents(){
        return this->agents;
    }

    std::vector<std::vector<int>> Interactions::InteractConnections::getConnectionsList(){
        return this->connectionsList;
    }

    std::vector<int> Interactions::InteractConnections::getNumConnections(){
        return this->numConnections;
    }

    std::vector<int> Interactions::InteractConnections::getMaxConnections(){
        return this->maxConnections;
    }

    // Setters
    void Interactions::InteractConnections::setAgents(std::vector<int> newAgents){
        this->agents = newAgents;
    }

    void Interactions::InteractConnections::setConnectionsList(std::vector<std::vector<int>> newConnectionsList){
        this->connectionsList = newConnectionsList;
    }

    void Interactions::InteractConnections::setNumConnections(std::vector<int> newNumConnections){
        this->numConnections = newNumConnections;
    }

    void Interactions::InteractConnections::setMaxConnections(std::vector<int> newMaxConnections){
        this->maxConnections = newMaxConnections;
    }

    // Generator Functions
    void Interactions::InteractConnections::genInteractConnections(int size){
        std::vector<int> agents;
        std::vector<std::vector<int>> connectionsList;
        std::vector<int> numConnections;
        std::vector<int> maxConnections;
        for(int i = 0; i < size; i++){
            agents.push_back(i);
            // Generate the connections lists for each agent
            int rand_num = std::rand() % 10 + 1;
            std::vector<int> connections;
            for(int j = 1; j <= rand_num; j++){
                int rand_num2 = std::rand() % size;
                connections.push_back(rand_num2);
            }
            connectionsList.push_back(connections);
            numConnections.push_back(rand_num);
            maxConnections.push_back(rand_num);
        }
        // Set the data in this object
        this->agents = agents;
        this->connectionsList = connectionsList;
        this->numConnections = numConnections;
        this->maxConnections = maxConnections;
    }


    //-------------------------------------------------------//
    // Define the Interactions Class
    //-------------------------------------------------------//
    Interactions::Interactions(){
        // Seed the random number generator
        std::srand((unsigned int)time(NULL));
    }
    Interactions::Interactions(int size){
        std::cout << "Size of input size: " << sizeof(size) << std::endl;
        // Seed the random number generator
        std::srand((unsigned int)time(NULL));
        // Generate some pathogen settings
        this->genPathogenSettings();
        float infection_rate = this->pathogenSettings["infection_rate"];
        // Generate a random population and connections
        this->population.genPopulation(size, infection_rate);
        this->connections.genInteractConnections(size);
    }

    // Setters
    void Interactions::setConnections(Interactions::InteractConnections connections){
        this->connections = connections;
    }

    void Interactions::setConnections(std::vector<int> newAgents, 
                                std::vector<std::vector<int>> newConnectionsList, 
                                std::vector<int> newNumConnections,
                                std::vector<int> newMaxConnections){
        this->connections = InteractConnections(newAgents, 
                                        newConnectionsList, 
                                        newNumConnections, 
                                        newMaxConnections);
    }

    void Interactions::setPopulation(Interactions::Population population){
        this->population = population;
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

    void Interactions::setPathogenSettings(std::unordered_map<std::string, float> &newPathogenSettings){
        this->pathogenSettings = newPathogenSettings;
    }

    void Interactions::setPathogenSetting(std::string setting, float value){
        this->pathogenSettings[setting] = value;
    }

    // Getters
    Interactions::InteractConnections Interactions::getConnections(){
        return this->connections;
    }

    Interactions::Population Interactions::getPopulation(){
        return this->population;
    }

    std::unordered_map<std::string, float> Interactions::getPathogenSettings(){
        return this->pathogenSettings;
    }

    // Generator Functions
    void Interactions::genPathogenSettings(){
        // unordered_map key, value is: setting_name, setting_value
        // For pathogen_settings from Python, we should expect default values of 
        float infection_rate = 0.5F;
        float recovery_rate = 0.1F;
        float death_rate = 0.00F;
        float spontaneous_rate = 0.00F;
        float testing_accuracy = 0.0F;
        float immunity_period = 100.0F;
        float contagious_period = 99.0F;
        float incubation_period = 0.0F;
        // We will have to make sure to type cast any potential ints to floats in the .pyx / .pyd file. 
        std::unordered_map<std::string, float> pathogenSettings;
        pathogenSettings["infection_rate"] = infection_rate;
        pathogenSettings["recovery_rate"] = recovery_rate;
        pathogenSettings["death_rate"] = death_rate;
        pathogenSettings["spontaneous_rate"] = spontaneous_rate;
        pathogenSettings["testing_accuracy"] = testing_accuracy;
        pathogenSettings["immunity_period"] = immunity_period;
        pathogenSettings["contagious_period"] = contagious_period;
        pathogenSettings["incubation_period"] = incubation_period;
        // Set the data in this object
        this->pathogenSettings = pathogenSettings;

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

    std::vector<std::vector<int>> Interactions::getUniqueConnections(Interactions::InteractConnections &thisConnections){
        // Get connection lists that are > 0 in length/size
        std::vector<std::vector<int>> connectionsList = thisConnections.getConnectionsList();
        std::vector<int> agents = thisConnections.getAgents();
        std::set<std::vector<int>> interaction_pairs;
        if (connectionsList.size() != agents.size()) {
            std::cout << "agents and conenctionsList are not the same size!" << std::endl;
        }

        // Hold the connections that are > 0 in another 2D vector
        for(int i = 0; i < agents.size(); i++){
            if(connectionsList[i].size() > 0){
                // Generate a vector of all pairs of agent_a : agent_b's from the agentsWithNonZeroConnectionsList
                int agentWithNonZeroConnections = agents[i];
                for(int connection : connectionsList[agentWithNonZeroConnections]){
                    // Should have the form of {agentWithNonZeroConnections, connection}
                    std::vector<int> pair = {agentWithNonZeroConnections, connection};
                    std::sort(pair.begin(), pair.end());
                    interaction_pairs.insert(pair);
                }
            }
        }

        // Unpack the set into a 2D vector
        std::vector<std::vector<int>> vect_interaction_pairs;
        for (std::vector<int> v : interaction_pairs) {
            vect_interaction_pairs.push_back(v);
        }
        // return a 2D vector of the interaction pairs
        return vect_interaction_pairs;
    }

    std::pair<bool, std::pair<int, int>> Interactions::qualify_interaction(std::pair<std::pair<int, std::string>, std::pair<int, std::string>> &pair){
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

    void Interactions::interact(std::vector<int> &pair, std::unordered_map<std::string, float> &pathogenSettings){
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
            this->population.getInfectedByList()[susceptible_agent_id].push_back(infected_agent_id);
        }

    }

    void Interactions::interactAll(){
        // The affected object in this function via subcalls is this->population 
        // which is eventually what we'll want to return in order to fulfill the
        // same functionality as the python code
        std::vector<std::vector<int>> interaction_pairs;
        // Get all the unique connections
        interaction_pairs = this->getUniqueConnections(this->connections);
        // For each connection, interact them
        std::unordered_map<std::string, float> pathogenSettings = this->getPathogenSettings();
        for(std::vector<int> pair : interaction_pairs){
            this->interact(pair, pathogenSettings);
        }
    }

} // end namespace Interactions

namespace Connections {
    Connections::Connections(){
        // Do nothing
    }

    Connections::Connections(int newSize){
        setSize(newSize);
    }

    int Connections::getSize(){
        return size;
    }

    void Connections::setSize(int newSize){
        size = newSize;
    }

    bool Connections::existsInVector(int num, std::vector<int> &v){
        for(int i : v){
            if(num == i){
                return true;
            }
        }
        return false;
    }

    std::vector<int> Connections::genConnectionsMaxVector(int minConnections, int maxConnections, int size){
        std::vector<int> connectionsMax;
        for(int i = 0; i < size; i++){
            int connectionRange = maxConnections - minConnections;
            int randomConnectionSize = std::rand() % connectionRange + minConnections;
            connectionsMax.push_back(randomConnectionSize);
        }
        return connectionsMax;
    }

    std::vector<int> Connections::getAvailable(int personID, std::vector<int> &connectionsMax, std::vector<std::vector<int> > &connections){
        // Finds all the connections avialable for a given perosn, excluding themselves. 
        std::vector<int> available;

        for (int i = 0; i < connections.size(); i++){
            if (i != personID && !existsInVector(personID, connections[i]) && connections[i].size() < connectionsMax[i]){
                available.push_back(i);
            }
        }
        return available;
    }

    std::vector<std::vector<int> > Connections::genRandomNetwork(std::vector<int> &connectionsMax, bool verbose, bool testing){
        // Instantiate a 2d vector container for the connections list
        std::vector<std::vector<int> > connections;
        for(int i = 0; i < size; i++){
            std::vector<int> v;
            connections.push_back(v);
        }
        // If testing, Generate a random connectionsMax vector
        if(testing){
            int connectMin = 8;
            int connectMax = 10;
            std::vector<int> connectionsMax = genConnectionsMaxVector(connectMin, connectMax, size);
        }
        // Loop through the connections, and for each, allocate a random connection that is available to connect
        float percent_complete = 0;
        if (verbose){
            std::cout << "Starting to generate random network." << std::endl;
            std::cout << "Percent Complete: " << percent_complete << std::endl;
        }
        for (int i = 0; i < size; i++){
            if (verbose && i % 1000 == 0 ){
                percent_complete = (float)i / (float)size * 100;
                std::cout << "Percent Complete: " << percent_complete << std::endl;
            }
            
            while(connections[i].size() < connectionsMax[i]){
                // Get the available people we can connect with
                std::vector<int> available = getAvailable(i, connectionsMax, connections);
                if(available.size() == 0){
                    // No one available to connect with
                    break;
                }
                // Pick someone from among those we can connect with
                int randomConnection = std::rand() % available.size();

                // Make sure they aren't already in the person's conenction list
                for (int j = 0; j < connections[i].size(); j++){
                    if(randomConnection == connections[i][j]){
                        // This person is already in the connections list, so continue
                        continue;
                    }
                }

                connections[i].push_back(available[randomConnection]);
                connections[available[randomConnection]].push_back(i);
            }
        }

        return connections;
    }
} // end namespace Connections

// int main(){
//     std::cout << "Compiled successfully!" << std::endl;
//     // Make a new connections object to test it compiles successfully
//     // int newSize = 100;
//     // Connections::Connections connections = Connections::Connections(100);
//     // std::vector<int> connectionsMax = connections.genConnectionsMaxVector(9, 10, newSize);
//     // connections.genRandomNetwork(connectionsMax);

//     // Make an interactions object to test it compiles successfully
//     Interactions::Interactions interactions(1000);
//     std::cout << "Starting connectionsList: " << std::endl;
//     std::vector<std::vector<int>> connectionsList = interactions.getConnections().getConnectionsList();
//     Interactions::print2DVect(connectionsList);
//     std::vector<std::string> start_states = interactions.getPopulation().getStates();

//     interactions.interactAll();
//     std::cout << "Interacted connectionsList: " << std::endl;
//     connectionsList = interactions.getConnections().getConnectionsList();
//     Interactions::print2DVect(connectionsList);
//     std::cout << "Ending states: " << std::endl;
//     std::vector<std::string> end_states = interactions.getPopulation().getStates();
//     for(int i = 0; i < start_states.size(); i++){
//         if(!Interactions::isSameString(start_states[i], end_states[i])){
//             std::cout << start_states[i] << " --> " << end_states[i] << std::endl;
//         }
//     }
//     std::cout << "Successfully ran!" << std::endl;

    
//     return 0;
// }