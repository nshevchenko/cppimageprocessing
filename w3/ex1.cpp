#include <iostream>
#include <vector>
using namespace std;

// made by Nik Shevchenko on 10th February 2016
class Account {
	string name;
	int balance;

	public:
		Account (string name, int balance) {
			this->name = name;
			this->balance = balance;
		}

		void deposit(int amount);

		string getName(){
			return this->name;
		}

		int getBalance(){
			return this->balance;
		}

		void withdraw(int amount){
			balance -= amount;
		}
};

void Account::deposit(int amount){
	balance += amount;
};

class Bank {
	vector<Account*> accounts;

	public:
		void addAccount(Account *acc){
			accounts.push_back(acc);
		}

		void printAllAccounts() {
			for (int i = 0; i < accounts.size(); ++i)
				cout << "account n^" << i << " name & balance: " << accounts[i]->getName() << " " << accounts[i]->getBalance() << endl;
			}

		/*
		 	deposit from user name with  amount
		*/
		void depositFromUserName(string username, int amount){
			for(int i = 0; i < accounts.size(); ++i){
				if (accounts[i]->getName().compare(username)){
						accounts[i]->deposit(amount);
				}
			}
		}

		/*
		 	Widraw from user name with  amount
		*/
		void withdrawFromUserName(string username, int amount){
			for(int i = 0; i < accounts.size(); ++i){
				if (accounts[i]->getName().compare(username)){
						accounts[i]->withdraw(amount);
				}
			}
		}


};

int main() {
	Account *acc = new Account("Nik Shevchenko", 1000);
	acc->withdraw(500);
	Account *acc2 = new Account("Yasmin Lau", 5000);
	acc->deposit(500);

	// add users to bank
	Bank *bank = new Bank();
	bank->addAccount(acc);
	bank->addAccount(acc2);
	bank->printAllAccounts();
	cout << endl;

	// widraw to bank to user name with amount
	bank->withdrawFromUserName(acc2->getName(), 200);
	bank->printAllAccounts();
	cout << endl;

	// deposit to bank to user name with amount
	bank->depositFromUserName(acc->getName(), 300);
	bank->printAllAccounts();

	delete acc;
}
