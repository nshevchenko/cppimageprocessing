#include <iostream>
#include <vector>
using namespace std;


int main() {

	int myInt = 1000;
 	int *myIntPointer; // what pointer value is
	cout << myInt << " " << myIntPointer << endl;
  myIntPointer = &myInt; //  whhere pointer points to
 	// declare a pointer to an integer
 	// and make it point to myInt
 	cout << myInt << " " << myIntPointer;

	myIntPointer = NULL; // what pointer value is
	
	cout << myInt << " " << myIntPointer << endl;


}
