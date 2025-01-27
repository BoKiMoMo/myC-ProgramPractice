#include <iostream>
#include <fstream> 
#include <cstdlib> 
#include "ClientData.h"
using namespace std;

int main()
{
    int accountNumber;
    string lastName;
    string firstName;
    double balance;

    fstream outCredit("credit.dat", ios::in | ios::out | ios::binary);

    if (!outCredit)
    {
        cerr << "File could not be opened." << endl;
        exit(EXIT_FAILURE);
    } // end if

    cout << "Enter account number (1 to 100, 0 to end input)\n? ";

    ClientData client;
    cin >> accountNumber;

    while (accountNumber > 0 && accountNumber <= 100)
    {
        cout << "Enter lastname, firstname, balance\n? ";
        cin >> lastName;
        cin >> firstName;
        cin >> balance;

        client.setAccountNumber(accountNumber);
        client.setLastName(lastName);
        client.setFirstName(firstName);
        client.setBalance(balance);

        outCredit.seekp((client.getAccountNumber() - 1) *
            sizeof(ClientData));

        outCredit.write(reinterpret_cast<const char*>(&client),
            sizeof(ClientData));

        cout << "Enter account number\n? ";
        cin >> accountNumber;
    } // end while
} // end main