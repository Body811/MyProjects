#include "class.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

// Bank account class methods
int BankAccount::counter = 0;
BankAccount::BankAccount()
{
    balance = 0.0;
    counter++;
    accountId = counter;
}

BankAccount::BankAccount(double amount)
{
    balance = amount;
    counter++;
    accountId = counter;
}

void BankAccount::setBalance(double amount)
{
    balance = amount;
}

double BankAccount::getBalance()
{
    return balance;
}

int BankAccount::getaccountID()
{
    return accountId;
}

void BankAccount::withdraw(double amount)
{
    balance -= amount;
}

void BankAccount::deposite(double amount)
{
    balance += amount;
}

// SavingsBankAccount class methods
SavingsBankAccount::SavingsBankAccount(double amount, double minAmount)
{
    if (amount > minAmount)
    {
        balance = amount;
        minimumBalance = minAmount;
    }
    else
        cout << "balance can't be lower than the minimum balance";
}

void SavingsBankAccount::withdraw(double amount)
{
    while (amount > balance || balance - amount < minimumBalance)
    {
        cout << "Sorry. This is more than what you can withdraw.\n";
        cout << "Please Enter The Amount to Withdraw =========> " << endl;
        cin >> amount;
    }
    balance -= amount;
    cout << "Withdraw Done" << endl;
    cout << "Balance: " << balance << endl;
}

void SavingsBankAccount::deposite(double amount)
{
    while (amount < 100)
    {
        cout << "Minimun deposite amount is 100EGP\n";
        cout << "Please Enter The Amount to Deposite =========> " << endl;
        cin >> amount;
    }
    balance += amount;
    cout << "Deposite Done" << endl;
    cout << "Balance: " << balance << endl;
}

double SavingsBankAccount::getMinimumBalance()
{
    return minimumBalance;
}

// Client class methods
Client::Client(string name, string address, int phone)
{
    this->name = name;
    this->address = address;
    this->phone = phone;
}

string Client::getName()
{
    return name;
}

string Client::getAddress()
{
    return address;
}

string Client::getAccountType()
{
    return accountType;
}

int Client::getPhone()
{
    return phone;
}

void Client::setAccountType(string type)
{
    accountType = type;
}

// BankApplication class methods
BankApplication::BankApplication()
{
    int num;
    do
    {

        cout << "Welcome to FCAI Banking Application\n";
        cout << "1. Create a New Account\n";
        cout << "2. List Clients and Accounts\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Deposit Money\n";
        cout << "5. Exit\n";
        cout << "Please Enter Choice =========> ";
        cin >> num;

        if (num == 1)
        {
            addClient();
        }
        else if (num == 2)
        {
            ListClients();
        }
        else if (num == 3)
        {
            withdraw();
        }
        else if (num == 4)
        {
            deposite();
        }
        else if (num == 5)
        {
            exit(1);
        }
        else
            cout << "Invalid Input !" << endl;

    } while (num != 5);
}

void BankApplication::addClient()
{
    string name, address;
    int num2, phone;

    cout << "Please Enter Client Name =========> ";
    cin >> name;

    cout << "Please Enter Client Address =======> ";
    cin >> address;

    cout << "Please Enter Client Phone =======> ";
    cin >> phone;

    Client client(name, address, phone);
    do
    {
        cout << "What Type of Account Do You Like? (1) Basic (2) Saving - Type 1 or 2 =========> ";
        cin >> num2;
        int balance;
        if (num2 == 1)
        {
            cout << "Please Enter the Starting Balance =========> ";
            cin >> balance;
            client.accountPtr = new BankAccount(balance);
            cout << "An account was created with ID FCAI-" << setw(3) << setfill('0') << client.accountPtr->getaccountID() << " and Starting Balance " << client.accountPtr->getBalance() << " L.E.\n";
            client.setAccountType("Basic");
            listOfClients.push_back(client);
        }
        else if (num2 == 2)
        {
            int minBalance;
            cout << "Please Enter the Minimum Balance =========> ";
            cin >> minBalance;
            cout << "Please Enter the Starting Balance =========> ";
            cin >> balance;
            while (balance < minBalance)
            {
                cout << "Balance can't be smaller that the Minimum Balance" << endl;
                cout << "Please Enter the Starting Balance =========> ";
                cin >> balance;
            }

            client.SavingsAccountPtr = new SavingsBankAccount(balance, minBalance);
            cout << "An account was created with ID FCAI-" << setw(3) << setfill('0') << client.accountPtr->getaccountID() << " with Minimum Balance of " << client.SavingsAccountPtr->getMinimumBalance() << " L.E. and Starting Balance " << client.SavingsAccountPtr->getBalance() << " L.E.\n";
            client.setAccountType("Saving");
            listOfClients.push_back(client);
        }
        else
        {
            cout << "Invalid Input!" << endl;
        }

    } while (num2 < 1 || num2 > 2);
}

void BankApplication::ListClients()
{

    for (auto c : listOfClients)
    {
        cout << "------------------- " << c.getName() << " -------------------" << endl;
        cout << "Address: " << c.getAddress() << " Phone: " << c.getPhone() << endl;
        if (c.getAccountType() == "Basic")
        {
            cout << "Account ID: " << setw(3) << setfill('0') << c.accountPtr->getaccountID() << endl;
            cout << "(Basic)" << endl;
            cout << "Balance: " << c.accountPtr->getBalance() << endl;
        }
        else
        {
            cout << "Account ID: " << setw(3) << setfill('0') << c.accountPtr->getaccountID() << endl;
            cout << "(Saving)" << endl;
            cout << "Balance: " << c.SavingsAccountPtr->getBalance() << endl;
            cout << "Minimum Balance: " << c.SavingsAccountPtr->getMinimumBalance() << endl;
        }
        cout << "------------------------------------------------------------------------------------------" << endl;
    }
}

void BankApplication::withdraw()
{
    int id;
    cout << "Please Enter Account ID (e.g., FCAI-015) =========> FCAI- ";
    cin >> id;
    for (auto c : listOfClients)
    {
        int amount;
        if (c.getAccountType() == "Basic")
        {
            if (c.accountPtr->getaccountID() == id)
            {
                cout << "Account ID: FCAI-" << setw(3) << setfill('0') << c.accountPtr->getaccountID() << endl;
                cout << "Acocunt Type: Basic" << endl;
                cout << "Balance" << c.accountPtr->getBalance() << endl;
                cout << "Please Enter The Amount to Withdraw =========> " << endl;
                cin >> amount;
                while (amount > c.accountPtr->getBalance())
                {
                    cout << "Sorry. This is more than what you can withdraw.\n";
                    cout << "Please Enter The Amount to Withdraw =========> " << endl;
                    cin >> amount;
                }
                c.accountPtr->withdraw(amount);
                cout << "Withdraw Done" << endl;
                cout << "Balance: " << c.accountPtr->getBalance() << endl;
            }
        }
        else
        {
            if (c.SavingsAccountPtr->getaccountID() == id)
            {
                cout << "Account ID: FCAI-" << setw(3) << setfill('0') << c.SavingsAccountPtr->getaccountID() << endl;
                cout << "Acocunt Type: Saving" << endl;
                cout << "Balance: " << c.SavingsAccountPtr->getBalance() << endl;
                cout << "Minimum Balance: " << c.SavingsAccountPtr->getMinimumBalance() << endl;
                cout << "Please Enter The Amount to Withdraw =========> " << endl;
                cin >> amount;
                c.SavingsAccountPtr->withdraw(amount);
            }
        }
    }
}

void BankApplication::deposite()
{
    int id;
    cout << "Please Enter Account ID (e.g., FCAI-015) =========> FCAI- ";
    cin >> id;
    for (auto c : listOfClients)
    {
        int amount;
        if (c.getAccountType() == "Basic")
        {
            if (c.accountPtr->getaccountID() == id)
            {
                cout << "Account ID: FCAI-" << setw(3) << setfill('0') << c.accountPtr->getaccountID() << endl;
                cout << "Acocunt Type: Basic" << endl;
                cout << "Balance" << c.accountPtr->getBalance() << endl;
                cout << "Please Enter The Amount to Deposite =========> " << endl;
                cin >> amount;
                c.accountPtr->deposite(amount);
                cout << "Deposite Done" << endl;
                cout << "Balance: " << c.accountPtr->getBalance() << endl;
            }
        }
        else
        {
            if (c.SavingsAccountPtr->getaccountID() == id)
            {
                cout << "Account ID: FCAI-" << setw(3) << setfill('0') << c.SavingsAccountPtr->getaccountID() << endl;
                cout << "Acocunt Type: Saving" << endl;
                cout << "Balance: " << c.SavingsAccountPtr->getBalance() << endl;
                cout << "Minimum Balance: " << c.SavingsAccountPtr->getMinimumBalance() << endl;
                cout << "Please Enter The Amount to Deposite =========> " << endl;
                cin >> amount;
                c.SavingsAccountPtr->deposite(amount);
            }
        }
    }
}

BankApplication::~BankApplication()
{
    for (auto c : listOfClients)
    {
        delete c.accountPtr;
        delete c.SavingsAccountPtr;
    }
}