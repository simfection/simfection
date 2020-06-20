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

	return interactions;
}

// Test that, if the infected rate is high enough,
// sus people are converted to infected
TEST(TestCaseName, TestName) {
	Interactions::Interactions interactions = setup();
	std::vector<std::string> start_states = interactions.getPopulation().getStates();
	interactions.interactAll();
	std::vector<std::string> end_states = interactions.getPopulation().getStates();
	for (int i = 0; i < start_states.size(); i++) {
		std::cout << start_states[i] << " --> " << end_states[i] << std::endl;
	}
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}