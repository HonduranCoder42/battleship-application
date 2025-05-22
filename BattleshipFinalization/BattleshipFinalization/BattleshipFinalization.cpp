#include "battleship.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main() {
	srand(time(nullptr));
	Fleet fleet;
	int numShipsRemaining = 6;
	bool isValid = false;
	string choice;

	fleet.deployFleet();

	cout << "Hello! Welcome to BattleShip!" << endl;

	while (isValid == false) {
		cout << "Would you like to print out the ship statuses before you begin? Enter '1' for yes or '2' for no" << endl;
		cin >> choice;
		if (choice == "1") {
			fleet.printFleet();
			isValid = true;
		}
		else if (choice == "2") {
			isValid = true;
		}
		else {
			cout << "Invalid entry. Try again" << endl;
		}
	}

	while (fleet.operational()) {
		Location userShot;

		cout << "There are " << numShipsRemaining << " ships remaining." << endl;
		cout << "Please enter coordinates to fire at: " << endl;
		userShot.fire();

		if (fleet.isHitNSink(userShot) == 1) {
			cout << "That's a hit! FeelsGoodMan." << endl;
			numShipsRemaining--;
		}
		else if (fleet.isHitNSink(userShot) == 0) {
			cout << "Unforunately, that's a miss. FeelsBadMan." << endl;
		}
		else if (fleet.isHitNSink(userShot) == 2) {
			cout << "There's already a sunk ship here. FeelsBadMan." << endl;
		}
	}

	cout << "Congratuations! You won! FeelsGreatMan!" << endl;

	return 0;
}