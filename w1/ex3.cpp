#include <iostream>
using namespace std;

// made by Nik Shevchenko on 10th February 2016

int main(){
	int a, b;
	cout << "Type a number a: ";
	cin >> a;
	cout << "Type a number b: ";
	cin >> b;
	cout << "The biggest number is ";
	if(a > b)
		cout << a << endl;
	else
		cout << b << endl;
}
