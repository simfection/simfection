#include <iostream>
#include <vector>
#include <unordered_map>
// algorithm allows for using std::rand()
#include <algorithm>

// User defined libraries
#include "interactions.h"


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

std::vector<std::vector<int>> getUniqueConnections(Interactions::Connections thisConnections){
    std::vector<std::vector<int>> interaction_pairs;
    // Get connection lists that are > 0 in length/size

    // Generate a vector of all pairs of agent_a : agent_b's from the connections list

    // Get rid of all duplicate agent_a : agent_b pairs

    // return a 2D vector of the interaction pairs
    return interaction_pairs;
}

Interactions::Population Interactions::interactAll(){
    Interactions::Population population;
    // Get all the unique connections

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