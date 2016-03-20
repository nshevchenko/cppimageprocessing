#include <iostream>
#include<string>
using namespace std;
/* EXERCISE 4a: C++ STRINGS */
/* THE AIM IS TO WRITE CODE THAT TESTS HOW THE OVERLOADED OPERATORS */
/* WORK WITH STRINGS IN C++ */

// made by Nik Shevchenko on 10th February 2016

int main()
{
	string s1, as1, s2, s3;
	s1 = "shev";
	as1 = "asdf";
	s2 = "shevc";
	s3 = "shevch";

	/* check content */
	if( s1.compare(as1) )
		cout << s1 << " value is equal to " << as1 << endl;
	else
		cout << s1 << " value is not equal to " << as1 << endl;

	if( s1.compare(as1) )
		cout << s1 << " value is equal to " << s1 << endl;
	else
		cout << s1 << " value is not equal to " << s1 << endl;

	/* check lenth */
	if( s2 > s1 )
		cout << s2 << " bigger than " << s1 << endl;

	if( s1 == s1 )
			cout << s1 << " is equal to " << s1 << endl;
	else
		cout << s1 << " is not equal to " << s1 << endl;

	if( s1 == as1 )
		cout << s1 << " is equal to " << as1 << endl;
	else
		cout << s1 << " is not equal to " << as1 << endl;

	if( s1 == s2 )
		cout << s1 << " == " << s2 << endl;
	else
		cout << s1 << " != " << s2 << endl;

	if( s1 != s3 )
		cout << s1 << " != " << s3 << endl;

	cout << "concatenated s1 +s2 + " << s1 + s2 << endl;
	cout << "Conclusion: operators work with s.length() value to define the result";

	return 0;
}
