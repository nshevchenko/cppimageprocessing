#include <iostream>
using namespace std;

class base {
public:
 virtual void vfunc() {
 cout << "This is base’s vfunc().\n";
 }
};

class derived1 : public base {
public:
 void vfunc() {
 cout << "This is derived1’s vfunc().\n";
 }
};

int main()
{
 	base *p, b;

	derived1 d1;
 	p = &b;
 	p->vfunc();
 	p = &d1;
 	p->vfunc();
 	return 0;
}
