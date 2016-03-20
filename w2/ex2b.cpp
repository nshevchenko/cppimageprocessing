int main() {
 int myInt = 1000;
 int *myIntPointer = &myInt;
 // declare another integer whose value is the same as the integer
 // at memory address <myIntPointer>
 int mySecondInt = *myIntPointer;
 cout << myInt <<’ ‘;
3
 // dereference the pointer and add 5 to the integer it points to
 *myIntPointer += 5;
 cout << myInt << ‘ ’;
 cout << mySecondInt;
} 
