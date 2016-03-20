#include <iostream>
#include <cmath>
using namespace std;

/* THE AIM IS TO WRITE CODE THAT TESTS HOW THE OVERLOADED OPERATORS */
/* WORK WITH STRINGS IN C++ */

class vector2d {
	public:
		int X, Y;

		vector2d() {
			cout << "init" << endl;
		}

		vector2d(double X, double Y) {
			this->X = X;
			this->Y = Y;
			cout << "init" << endl;
		}

		double length(){
			return sqrt((X*X)+(Y*Y));
		}

};

int main()
{
	vector2d *v = new vector2d(3, 4);
	cout << v->X << " " << v->length() << endl;
	cout << "V is cool";

	return 0;
}
