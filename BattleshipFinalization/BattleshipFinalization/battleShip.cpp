#include "battleship.h"
#include <iostream>
#include <ctime>
#include<string>
using namespace std;

//this is a friend function to Location class.
bool compare(const Location& loc1, const Location& loc2) {
    return (loc1 == loc2);
    /*nitoce that == operator is overloaded for the Location class*/

}

//overloding the << operator to teach the compiler how to print a ship info using cout
ostream& operator<<(ostream& os, const Ship& sh)
{
    string status;
    if (!sh.sunk)
        status = " up ";
    else
        status = " sunk ";
    sh.loc.print();

    os << "->" << status;
    return os;
}

//--------Location implementation-----------------------------------------------------------------------//

Location::Location() {
    coordinates = new int[2];
    coordinates[0] = -1;
    coordinates[1] = -1;
}
Location::Location(int x, int y) {
    coordinates = new int[2];
    coordinates[0] = x;
    coordinates[1] = y;
}
void Location::pick() {
    //srand(time(nullptr));
    coordinates[0] = rand() % FIELD_SIZE + 1;
    coordinates[1] = rand() % FIELD_SIZE + 1;

}
void Location::fire() {
    bool validX = false;
    bool validY = false;
    int x, y;

    while (validX == false) {
        cout << "x-coordinate [1 - 6] ->"; cin >> x;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "You can only enter numbers. Please try again." << endl;
        }
        else if ((x < 1) || (x > 6)) {
            cout << "Invalid number. Please try again." << endl;
        }
        else {
            validX = true;
        }
    }

    while (validY == false) {
        cout << "y-coordinate [1 - 6] ->"; cin >> y;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "You can only enter numbers. Please try again." << endl;
        }
        else if ((y < 1) || (y > 6)) {
            cout << "Invalid number. Please try again.";
        }
        else {
            validY = true;
        }
    }

    coordinates[0] = x;
    coordinates[1] = y;
}
void Location::print() const {
    cout << "[" << coordinates[0] << ", " << coordinates[1] << "]";
}

//rule of three
Location::Location(const Location& org) {
    coordinates = new int[2];
    coordinates[0] = org.coordinates[0];
    coordinates[1] = org.coordinates[1];
}
Location& Location::operator=(const Location& rhs) {
    if (this != &rhs) {
        coordinates[0] = rhs.coordinates[0];
        coordinates[1] = rhs.coordinates[1];
    }

    return *this;
}
Location::~Location() {
    delete[] coordinates;
}


//--------Ship implementation------------------------------------------------//

Ship::Ship() {
    sunk = false;
}

bool Ship::match(const Location& otherLocation) const {
    return compare(loc, otherLocation);
}

void Ship::sink() {
    sunk = true;
}

void Ship::setLocation(const Location& currentLoc) {

    loc = currentLoc;
}

void Ship::printShip() const {
    cout << this;
}
//--------Fleet implementation ------------------//

void Fleet::deployFleet() {
    for (int i = 0; i < FLEET_SIZE; i++) {
        Location shipLoc;
        shipLoc.pick();
        if (check(shipLoc) != -1) {
            i--;
        }
        else {
            ships[i].setLocation(shipLoc);
        }
    }
}

bool Fleet::operational() const {
    int numShipsUp = 0;
    for (int i = 0; i < FLEET_SIZE; i++) {
        if (!(ships[i].isSunk())) {
            numShipsUp++;
        }
    }

    if (numShipsUp > 0) {
        return true;
    }
    else {
        return false;
    }
}

int Fleet::isHitNSink(const Location& loc) {
    for (int i = 0; i < FLEET_SIZE; i++) {
        if (ships[i].match(loc)) {
            if (ships[i].isSunk()) {
                return 2;
            }
            else {
                ships[i].sink();
                return 1;
            }
        }
    }

    return 0;
}

void Fleet::printFleet() const {
    for (int i = 0; i < FLEET_SIZE; i++) {
        if (i == 5) {
            cout << ships[i];
        }
        else {
            cout << ships[i] << ", ";
        }
    }
}

Ship* Fleet::getShipList() {
    return ships;
}

int Fleet::getFleetSize() {
    return FLEET_SIZE;
}

int Fleet::check(const Location& loc) const {
    for (int i = 0; i < FLEET_SIZE; i++) {
        if (ships[i].match(loc)) {
            return i;
        }
    }

    return -1;
}