#include <iostream>
#include<string>
using namespace std;
/* EXERCISE 4: C++ STRINGS */
// made by Nik Shevchenko on 10th February 2016

int main()
{
	string s;
	while (cin >> s)
		cout << s.length() << " -" + s.substr(1, s.length()) << '\n';
	return 0;
}
