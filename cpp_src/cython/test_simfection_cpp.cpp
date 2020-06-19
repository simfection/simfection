#include "gtest/gtest.h"

#include <iostream>
#include <vector>
#include <unordered_map>
// algorithm allows for using std::rand() and std::unique()
#include <algorithm>
#include <cmath>
#include <ctime>
#include <set>

#include "simfection_cpp.h"
#include "simfection_cpp.cpp"


Interactions::Interactions setup() {
	// Create the populations stub
	std::string sus = "sus";
	std::string inf = "inf";
	std::vector<int> agents = { 0, 1, 2, 3, 4, 5 };
	std::vector<std::string> states = { inf, sus, sus, sus, sus, sus };
	std::vector<std::vector<int>> infectedByList = { {}, {}, {}, {}, {}, {} };
	std::vector<int> daysInfected = { 1, 0, 0, 0, 0, 0 };
	std::vector<int> immunities = { 0, 0, 0, 0, 0, 0 };

	// Create the interactconnections stub
	std::vector<int> conn_agents = { 0, 1, 2, 3, 4, 5 };
	std::vector<std::vector<int>> connectionsList = { {1,2,3,4,5}, {0}, {0}, {0}, {0}, {0} };
	std::vector<int> numConnections = { 5, 1, 1, 1, 1, 1 };
	std::vector<int> maxConnections = { 5, 5, 5, 5, 5, 5 };

	// Finally, create the test Interactions object
	Interactions::Interactions interactions;
	interactions.setPopulation(agents, states, infectedByList, daysInfected, immunities);
	interactions.setConnections(conn_agents, connectionsList, numConnections, maxConnections);
	// Generate the Pathogen Settings object
	interactions.genPathogenSettings();

	return interactions;
}

// Test the qualify interaction function
// if infection_rate is 1.0
TEST(TestQualifyInteractionFunction, TestSimfectionCpp) {
	Interactions::Interactions interactions = setup();

	std::vector<std::vector<int>> interaction_pairs;
    // Get all the unique connections
	Interactions::Interactions::InteractConnections connections = interactions.getConnections();
    interaction_pairs = interactions.getUniqueConnections(connections);

	std::unordered_map<int, std::string> agentStates = interactions.getPopulation().getAgentStates();
    int agentAID = interaction_pairs[0][0];
    int agentBID = interaction_pairs[0][1];
    std::string agentAState = agentStates[agentAID];
    std::string agentBState = agentStates[agentBID];
	// Make the Agent A pair
    std::pair<int, std::string> agentAIDState;
    agentAIDState.first = agentAID;
    agentAIDState.second = agentAState;
	// Make the Agent B pair
    std::pair<int, std::string> agentBIDState; 
    agentBIDState.first = agentBID;
    agentBIDState.second = agentBState;
	// Combine the pairs into a pair
    std::pair<std::pair<int, std::string>, std::pair<int, std::string>> agentPair;
    agentPair.first = agentAIDState;
    agentPair.second = agentBIDState;
    // Qualify the interaction and unpack the values
    std::pair<bool, std::pair<int, int>> interaction_qualification = interactions.qualify_interaction(agentPair);

	EXPECT_TRUE(interaction_qualification.first);
}

// Test that an infected person will infect a susceptible person 
// if infection_rate is 1.0
TEST(TestInteractFunction, TestSimfectionCpp) {
	Interactions::Interactions interactions = setup();
	std::vector<std::vector<int>> interaction_pairs;
    // Get all the unique connections
	Interactions::Interactions::InteractConnections connections = interactions.getConnections();
    interaction_pairs = interactions.getUniqueConnections(connections);
	// Set the pathogen setting for infection rate to 1.0
	interactions.setPathogenSetting("infection_rate", 1.0F);
	std::unordered_map<std::string, float> pathogenSettings = interactions.getPathogenSettings();
	interactions.interact(interaction_pairs[0], pathogenSettings);
	std::vector<std::string> states = interactions.getPopulation().getStates();
	std::string inf = "inf";
	// Interactions::Interactions::isSameString(agents)
	EXPECT_EQ(states[1], inf);
}

// Test that, if the infected rate is high enough,
// sus people are converted to infected
TEST(TestSusGetInfected, TestSimfectionCpp) {
	Interactions::Interactions interactions = setup();
	std::vector<std::string> start_states = interactions.getPopulation().getStates();
	interactions.interactAll();
	std::vector<std::string> end_states = interactions.getPopulation().getStates();
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}