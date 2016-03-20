#include <iostream>
#include <cmath>
using namespace std;

/* THE AIM IS TO WRITE CODE THAT TESTS HOW THE OVERLOADED OPERATORS */
/* WORK WITH SUB AND SUPER CASSES  C++ */

// made by Nik Shevchenko on 10th February 2016

class Building {
	int rooms, floors, area;

	public:
		Building(int rooms, int floors, int area) {
			this->rooms = rooms;
			this->floors = floors;
			this->area = area;
		}
		int getRooms(){
			return this->rooms;
		}
		int getFloors(){
			return this->floors;
		}
		int getArea(){
			return this->area;
		}
};

class House : public Building {
	string name;
	int bedrooms, bathrooms;

	public:
		House(string name, int bedrooms, int bathrooms, int rooms, int floors, int area)
		: Building(rooms, floors, area) {
			this->name = name;
			this->bedrooms = bedrooms;
			this->bathrooms = bathrooms;
		}
		string getName(){
			return this->name;
		}

		int getBedrooms(){
			return this->bedrooms;
		}

		int getBathrooms(){
			return this->bathrooms;
		}
};

int main()
{
	House *h = new House("Brabazon House", 4, 2, 6, 3, 235);
	cout << h->getArea() << " " << h->getName() << endl;
	cout << "H is cool";

	return 0;
}
