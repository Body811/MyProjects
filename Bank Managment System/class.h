#ifndef classes_h
#define classes_h

#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Client;

class BankAccount
{
protected:
    int accountId;
    double balance = 0;


public:
    static int counter;
    BankAccount();
    BankAccount(double amount);
    void setBalance(double amount);
    void setAccountId(int id);
    double getBalance();
    int getaccountID();
    void withdraw(double amount);
    void deposite(double amount);
};
// int BankAccount::accountId = 0;
class SavingsBankAccount : public BankAccount
{
    double minimumBalance;

public:
    SavingsBankAccount(double amount, double minAmount);
    void withdraw(double amount);
    void deposite(double amount);
    double getMinimumBalance();
};

class Client
{
    string name;
    string address;
    string accountType;
    int phone;

public:
    BankAccount *accountPtr;
    SavingsBankAccount *SavingsAccountPtr;
    Client(string name, string address, int phone);
    string getName();
    string getAddress();
    string getAccountType();
    int getPhone();
    void setAccountType(string type);

};

class BankApplication
{
    vector<Client> listOfClients;

public:
    BankApplication();
    void addClient();
    void ListClients();
    void withdraw();
    void deposite();
    ~BankApplication();
};

#endif