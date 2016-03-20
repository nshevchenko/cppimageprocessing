#include <iostream>
#include <vector>
using namespace std;

// PASS N2 BY REFERENCE (ADDRESS IN THE MEMORY
void increment(int n1, int &n2, int inc) {
	cout << "HI";
	n1 += inc;
	n2 += inc;

	// ALTERNATIVE WAY BY POINTER
	//increment(int n1, int *n2, int inc) {
	// *n2 += inc
	// increment the value in the memory address the pointer points to.

	// playing around with pointer changes and values it points to

	// cout << "n2 : " << n2 << endl;
	// cout << "*n2 " << *n2 << endl;
	// n2 += inc;
	// cout << "n2 : " << n2 << endl;
	// cout << "*n2 " << *n2 << endl;
	// *n2 += inc;
	// cout << "n2 : " << n2 << endl;
	// cout << "*n2 " << *n2 << endl;
}

int main() {

	int n1 = 2, n2 = 3, inc = 4;
	// n1 = 2;
	// n2 = 3;
	// inc = 4;

	cout << n1 << " " << n2 << " " << inc << endl;
	increment(n1, n2, inc);
	cout << n1 << " " << n2 << " " << inc << endl;

	// repeat
	cout << n1 << " " << n2 << " " << inc << endl;
	increment(n1, n2, inc);
	cout << n1 << " " << n2 << " " << inc << endl;
}
