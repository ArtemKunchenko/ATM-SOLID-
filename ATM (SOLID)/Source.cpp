#include <iostream>
#include <string>
#include <vector>
using namespace std;

class ATMTransaction;
class Customer;

class Bank
{
public:
	Bank(int code, const string& address) : _code(code), _address(address) {}
	virtual void manages() {};
	virtual void maintains() {};
protected:
	int _code;
	string _address;
};

class ATM
{
public:
	ATM(const string& location, Bank* managedby) : _location(location), _managedby(managedby) {}

	bool identifies(Customer* customer)
	{
		for (const auto& cust : _customers)
		{
			if (cust == customer) return true;
		}
		return false;
	}
private:
	string _location;
	Bank* _managedby;
	vector<Customer*> _customers;
};

class Customer
{
public:
	Customer(const string& name, const string& address, const string& dob, const string& card_number, int pin)
		: _name(name), _address(address), _dob(dob), _card_number(card_number), _pin(pin) {}

	bool verifyPassword(int pin)
	{
		if (_pin == pin) return true;
		else return false;
	}
private:
	string _name;
	string _address;
	string _dob;
	string _card_number;
	int _pin;
};

class ATMTransaction
{
public:
	ATMTransaction(int transaction_id, const string& date, const string& type, double amount, double post_balance)
		: _transaction_id(transaction_id), _date(date), _type(type), _amount(amount), _post_balance(post_balance) {}

private:
	int _transaction_id;
	string _date;
	string _type;
	double _amount;
	double _post_balance;
};

class Account 
{
public:
	virtual void deposit(double amount) = 0;
	virtual void withdraw(double amount) = 0;
	void createTransaction(ATMTransaction* transaction) {_transactions.push_back(transaction);}
protected:
	int _number;
	double _balance;
	Bank* _bank;
	vector<ATMTransaction*> _transactions; 
};

class CurrentAccount : public Account 
{
public:
	CurrentAccount(int number, double balance, Bank* bank) : _number(number), _balance(balance), _bank(bank) {}

	void deposit(double amount) override {_balance += amount;}

	void withdraw(double amount) override 
	{
		if (_balance >= amount) _balance -= amount;
		else cout << "Transaction is declined\n";
	}
	double getBalance() { return _balance; }
private:
	int _number;
	double _balance;
	Bank* _bank;
};

class SavingsAccount : public Account 
{
public:
	SavingsAccount(int number, double balance, Bank* bank) : _number(number), _balance(balance), _bank(bank) {}

	void deposit(double amount) override {_balance += amount;}

	void withdraw(double amount) override 
	{
		if (_balance >= amount) _balance -= amount;
		else cout << "Transaction is declined\n";
	}

private:
	int _number;
	double _balance;
	Bank* _bank;
};
void performTransaction(Customer& customer, CurrentAccount& currentAccount) {
	int enteredPin ;
	double withdrawalAmount, initialBalance = currentAccount.getBalance();
	cout << "Input PIN: ";
	cin >> enteredPin;
	if (customer.verifyPassword(enteredPin)) 
	{
		cout << "Enter is successful" << endl;
		cout << "Balance: " << currentAccount.getBalance() << "$\n";
		cout << "Inpum the amount for withdrawal: ";
		cin >> withdrawalAmount;
		currentAccount.withdraw(withdrawalAmount);
		ATMTransaction transaction(1, "02.10.2023", "Withdrawal", withdrawalAmount, currentAccount.getBalance());
		currentAccount.createTransaction(&transaction);
		if(initialBalance> currentAccount.getBalance())
			cout << "Transaction is successful. Balance: " << currentAccount.getBalance() << "$\n";
		else cout << "Balance: " << currentAccount.getBalance() << "$\n";
	}
	else cout << "Password isn't correct" << endl;
}
int main() 
{
	Bank bank(1, "Peremogy str. 1");
	ATM atm("ATM 1", &bank);
	Customer customer("Ivan Ivanov", "Geroiv str. 2", "01.01.1990", "1234-5678-9012-3456", 1234);
	CurrentAccount currentAccount(1, 5000, &bank);
	performTransaction(customer, currentAccount);

	system("pause");
	return 0;
}