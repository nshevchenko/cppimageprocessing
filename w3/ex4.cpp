#include <iostream>
#include <cmath>
using namespace std;

/* THE AIM IS TO WRITE CODE */

// made by Nik Shevchenko on 10th February 2016

class Calc {

	public:
		// add
		float add (float a, float b){
			return a + b;
		}

		// sub
		float sub (float a, float b){
			return a - b;
		}

		// mul
		float mul (float a, float b){
			return a * b;
		}

		// div
		float div (float a, float b){
			return a / b;
		}

		float operation_Selection(float a, float b, float (Calc::*pt2Func)(float, float)){
			return (*this.*pt2Func)(a,b);
		}

};


int main()
{
	// define pointer to the function, float Calc::pt2Member
	float (Calc::*pt2Member)(float, float) = NULL;
	string inputStr;
	int a, b;


	// print intro
	cout << "Commands : add(1), sub(2), mul(3), div(4) ... '!' for exit" << endl;

	// cmd loop
	while ( inputStr.compare("!") ) {
		cout << "Enter command : ";
		getline(cin, inputStr);
		int input = stoi(inputStr);
		switch(input){
			case 1:
				// get a
				cout << "Insert a: ";
				getline(cin, inputStr);
				a = stoi(inputStr);

				// get B
				cout << " + " << endl << "Insert b: ";
				getline(cin, inputStr);
				b = stoi(inputStr);

				// assign pointer
				pt2Member = &Calc::add;
				break;
			case 2:
				// get a
				cout << "Insert a: ";
				getline(cin, inputStr);
				a = stoi(inputStr);

				// get B
				cout << " - " << endl << "Insert b: ";
				getline(cin, inputStr);
				b = stoi(inputStr);

				// assign pointer
				pt2Member = &Calc::sub;
				break;
			case 3:
					// get a
					cout << "Insert a: ";
					getline(cin, inputStr);
					a = stoi(inputStr);

					// get B
					cout << " * " << endl << "Insert b: ";
					getline(cin, inputStr);
					b = stoi(inputStr);

					// assign pointer
					pt2Member = &Calc::mul;
					break;
				case 4:
					// get a
					cout << "Insert a: ";
					getline(cin, inputStr);
					a = stoi(inputStr);

					// get B
					cout << " / " << endl << "Insert b: ";
					getline(cin, inputStr);
					b = stoi(inputStr);

					// assign pointer
					pt2Member = &Calc::div;
					break;
		}
		Calc calc;
		cout << "Result: " << calc.operation_Selection(a, b, pt2Member) << endl;
	}
	cout << "Good Bye my friend! ";
	return 0;
}


// OUTPUT

/*
Commands : add(1), sub(2), mul(3), div(4) ... '!' for exit
Enter command : 1
Insert a: 3
 +
Insert b: 4
Result: 7
Enter command : 2
Insert a: 5
 -
Insert b: 2
Result: 3
Enter command : 3
Insert a: 5
 *
Insert b: 4
Result: 20
Enter command : 4
Insert a: 6
 /
Insert b: 2
Result: 3
Enter command : 4
Insert a: 4
 /
Insert b: 3
Result: 1.33333
Enter command :
*/
