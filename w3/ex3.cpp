#include <iostream>
#include <vector>
using namespace std;



int main()
{

  string lenghtStr;
  cout << "Please, enter how many Ns you want to enter: ";
  getline(cin, lenghtStr);
  int length = stoi(lenghtStr);
  // init the array
  vector<string> strs(length);

  for(int i = 0; i < length; i++){
    string line;
    cout << "Plese enter the number " << i << ": ";
    getline(cin, line);
    // cout << "line : " << &line;
    strs[i] = line;
  }

  cout << "Thanks, you enterd the following numbers: ";
  for(int i = 0; i < length - 1; i++){
    cout << strs[i] << ", ";
  }
  cout << strs[length -1] << endl;
 	return 0;
}
