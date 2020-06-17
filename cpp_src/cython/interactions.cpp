#include <iostream>
#include <vector>
#include <unordered_map>
// algorithm allows for using std::rand()
#include <algorithm>

// User defined libraries
#include "interactions.h"

// Define the Interactions Class
Interactions::Interactions(){
    // Do nothing
}

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

Population Interactions::interactAll(){
    // Get all the unique connections
    
}


// Define the Population Class
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


// Define the Connections Class
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

int main(){
    // values for connection list stub
    std::vector<int> newAgents = {0, 1};
    std::vector<std::vector<int>> newConnectionsList = {{0, 1}, {0, 2}};
    std::vector<int> numConnections = {2, 2};
    std::vector<int> maxConnections = {3, 3};

    // values for population stub
    std::vector<int> popNewAgents = {0, 1};
    std::vector<std::string> newStates = {"inf", "sus"};
    std::vector<std::vector<int>> newInfectedByList = {{1}, {}};
    std::vector<int> newDaysInfected = {1, 0};
    std::vector<int> newImmunities = {0, 1};

    Interactions interactions = Interactions();
    interactions.initConnections(newAgents, newConnectionsList, numConnections, maxConnections);
    interactions.initPopulation(popNewAgents, newStates, newInfectedByList, newDaysInfected, newImmunities);
    std::cout << "Interactions object successfully made!" << std::endl;
    return 0;
}