#include <iostream>
#include <cmath>
using namespace std;

/* THE AIM IS TO WRITE CODE THAT TESTS HOW THE OVERLOADED OPERATORS */
/* WORK WITH SUB AND SUPER CASSES  C++ */

// made by Nik Shevchenko on 10th February 2016

// Building super class

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
    virtual void build(){
      cout << "I am building a Building";
    }
};

// House sub class

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

    virtual void build(){
      cout << "I am building a House";
    }
};


// FarmHouse sub class

class FarmHouse : public House {
  double farmLandArea;

  public:
		FarmHouse(string name, int bedrooms, int bathrooms, int rooms, int floors, int area, double farmLandArea)
		: House(name, bedrooms, bathrooms, rooms, floors, area) {
			this->farmLandArea = farmLandArea;
		}

    int getFarmLandArea(){
			return this->farmLandArea;
		}

    void build(){
      cout << "I am building a Farm House";
    }
};

// Igloo sub class


class Igloo : public Building {
	string name;
	int iceBlocks;

	public:
		Igloo(string name, int rooms, int floors, int area, int iceBlocks)
		: Building(rooms, floors, area) {
			this->name = name;
			this->iceBlocks = iceBlocks;
		}
		string getName(){
			return this->name;
		}

		int getIceBlocks(){
      return iceBlocks;
    }

    void build(){
      cout << "I am building a Igloo";
    }
};


int main()
{
	House *h = new House("Brabazon House", 4, 2, 6, 3, 235);
	cout << h->getName() << ": " << endl;
	h->build();
	cout << endl;

	//int bedrooms, int bathrooms, int rooms, int floors, int area, double farmLandArea)
	FarmHouse *f = new FarmHouse("Brabazon Farm House", 4, 2, 6, 3, 235, 5000);
	cout << f->getName() << ": " << endl;
	f->build();
	cout << endl;

	Igloo *i = new Igloo("Brabazon Igloo", 4, 2, 6, 2);
	cout << i->getName() << ": " << endl;
	i->build();
	cout << endl;

	return 0;
}
