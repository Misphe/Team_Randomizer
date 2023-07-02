#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_set>
using std::vector;
using std::string;
using std::unordered_set;

#define TEAM_1 0
#define TEAM_2 1
#define TEAM_SIZE 5
#define PLAYER_NUMBER_ERROR -1
#define LOAD_FROM_FILE 1
#define LOAD_FROM_KEYBOARD 2
#define CONFIRM "y"
#define REFUSE "n"

int userDataLoadingResponse() {
	std::string userResponse;
	std::cin >> userResponse;

	if (userResponse == CONFIRM) {
		return LOAD_FROM_FILE;
	}

	if (userResponse == REFUSE) {
		return LOAD_FROM_KEYBOARD;
	}

	return LOAD_FROM_KEYBOARD;
}

vector<string> loadPlayersDataFromFile(int teamSize) {
	std::ifstream file("nicknames.txt");
	vector<string> data(2 * teamSize);
	for (int i = 0; i < 2 * teamSize; i++) {
		std::getline(file, data[i]);
		if (data[i] == "") {
			std::cout << "too few players";
			exit(PLAYER_NUMBER_ERROR);
		}
	}
	return data;
}

vector<string> loadPlayersDataFromKeyboard(int teamSize) {
	vector<string> data(2 * teamSize);
	for (int i = 0; i < 2 * teamSize; i++) {
		std::getline(std::cin, data[i]);
		if (data[i] == "") {
			i--;
		}
	}
	return data;
}

int main() {

	srand(time(NULL));

	int teamSize;
	std::cout << "please, provide the size of a team: ";
	std::cin >> teamSize;

	//// validate the input
	if (std::cin.fail()) {
		std::cout << "provided size is not a number\n";
		return -1;
	}

	vector<string> people(2 * teamSize);

	std::cout << "load players from file? y/n\n";
	if (userDataLoadingResponse() == LOAD_FROM_FILE) {
		people = loadPlayersDataFromFile(teamSize);
	}
	else {
		std::cout << "input players' names: \n\n";
		people = loadPlayersDataFromKeyboard(teamSize);
	}

	vector<string> team1;
	vector<string> team2;
	unordered_set<int> chosenIndexes;

	// pick 5 random people
	while (chosenIndexes.size() < teamSize) {
		int index = rand() % (2 * teamSize);
		chosenIndexes.insert(index);
	}

	// put people to teams according to whether 
	// they were randomly picked in chosenIndexes
	// or not
	for (int i = 0; i < 2 * teamSize; i++) {
		auto finder = chosenIndexes.find(i);

		if (finder != chosenIndexes.end()) {
			team1.push_back(people[i]);
		}
		else {
			team2.push_back(people[i]);
		}
	}

	std::cout << "team1: \n";
	for (int i = 0; i < teamSize; i++) {
		std::cout << team1[i] << "\n";
	}

	std::cout << "\nteam2: \n";
	for (int i = 0; i < teamSize; i++) {
		std::cout << team2[i] << "\n";
	}
}