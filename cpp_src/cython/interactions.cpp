#include <iostream>
#include <vector>
#include <unordered_map>
// algorithm allows for using std::rand() and std::unique()
#include <algorithm>

// User defined libraries
#include "interactions.h"

//-------------------------------------------------------//
// Utility functions
//-------------------------------------------------------//

void print2DVect(std::vector<std::vector<int>> vect){
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
    this-> states = newStates;
    this->infectedByList = newInfectedByList;
    this->daysInfected = newDaysInfected;
    this->immunities = newImmunities;

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
    // Do nothing
}

// Setters
void Interactions::initConnections(std::vector<int> newAgents, 
                              std::vector<std::vector<int>> newConnectionsList, 
                              std::vector<int> newNumConnections,
                              std::vector<int> newMaxConnections){
    this->connections = Connections(newAgents, 
                                    newConnectionsList, 
                                    newNumConnections, 
                                    newMaxConnections);
}

void Interactions::initPopulation(std::vector<int> newAgents,
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

// Getters
Interactions::Connections Interactions::getConnections(){
    return this->connections;
}

Interactions::Population Interactions::getPopulation(){
    return this->population;
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

Interactions::Population Interactions::interactAll(){
    Interactions::Population population;
    // Get all the unique connections
    try {
        this->getUniqueConnections(this->connections);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
    // For each connection, interact them

    // return an object or set some class variables that have getters defined which can be pulled from 
    // in the Python code later to reconstruct a population DataFrame. 
    return population;
}


//-------------------------------------------------------//
// Main function for debugging and testing
//-------------------------------------------------------//
int main(){
    // values for connection list stub
    std::vector<int> newAgents = {0, 1, 2, 3};
    std::vector<std::vector<int>> newConnectionsList = {{0, 1}, {0, 2}, {0, 3}, {1, 4}};
    std::vector<int> numConnections = {2, 2, 2, 2};
    std::vector<int> maxConnections = {3, 3, 3, 3};

    // values for population stub
    std::vector<int> popNewAgents = {0, 1, 2, 3};
    std::vector<std::string> newStates = {"inf", "sus", "sus", "sus"};
    std::vector<std::vector<int>> newInfectedByList = {{1}, {}, {}, {}};
    std::vector<int> newDaysInfected = {1, 0, 0 ,0};
    std::vector<int> newImmunities = {0, 2, 0, 0};

    Interactions interactions = Interactions();
    interactions.initConnections(newAgents, newConnectionsList, numConnections, maxConnections);
    interactions.initPopulation(popNewAgents, newStates, newInfectedByList, newDaysInfected, newImmunities);
    std::cout << "Interactions object successfully made!" << std::endl;
    std::vector<std::vector<int>> interaction_pairs = interactions.getUniqueConnections(interactions.getConnections());
    print2DVect(interaction_pairs);

    // // Practice vector
    // std::vector<std::vector<int>> thisVect = {{20, 1},
    //                                           {2, 1},
    //                                           {9, 3},
    //                                           {2, 1},
    //                                           {20, 1},
    //                                           {9, 3}};

    // std::unordered_map<int, std::vector<int>> agent_interactions_dict; 
    
    // // Sort the vector
    // std::cout << "Unsorted vector: " << std::endl;
    // print2DVect(thisVect);
    // sort2DVectorRows(thisVect);
    // std::cout << "Sorted vector: " << std::endl;
    // print2DVect(thisVect);
    
    return 0;
}