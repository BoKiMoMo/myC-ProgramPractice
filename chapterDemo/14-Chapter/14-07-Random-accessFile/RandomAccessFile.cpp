#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include"ClientData.h"

using namespace std;

int enterChoice();
void createTextFile(fstream&);
void updateRecord(fstream&);
void newRecord(fstream&);
void deleteRecord(fstream&);
void outputLine(ostream&,const ClientData&);
int getAccount(const char* const);

enum Choice { PRINT = 1, UPDATE, NEW, DELETE, END };

int main()
{
	fstream inOutCredit("credit.dat", ios::in | ios::out | ios::binary);

	if (!inOutCredit)
	{
		cerr << "File could not be opened" << endl;
		exit(EXIT_FAILURE);
	}//end if

	int choice;

    while ( (choice = enterChoice() ) != END)
	{
		switch (choice)
		{
		case PRINT:
			createTextFile(inOutCredit);
			break;

		case UPDATE:
			updateRecord(inOutCredit);
			break;

		case NEW:
			newRecord(inOutCredit);
			break;

		case DELETE:
			deleteRecord(inOutCredit);
			break;

		default:
			cerr << "Incorrect choice" << endl;
			break;
		}//end switch

		inOutCredit.clear();
	}//end while
}//end main

int enterChoice()
{
	cout << "\nEnter your choice" << endl
		<< "1 - store a formatted text file of accounts" << endl
		<< "    called \"print.txt\" for printing" << endl
		<< "2 - update an account" << endl
		<< "3 - add a new account" << endl
		<< "4 - delete an account" << endl
		<< "5 - end program\n? ";

	int menuChoice;
	cin >> menuChoice;
	return menuChoice;
}

void createTextFile(fstream& readFromFile)
{
    ofstream outPrintFile("print.txt", ios::out);

    if (!outPrintFile)
    {
        cerr << "File could not be created." << endl;
        exit(EXIT_FAILURE);
    } // end if

    outPrintFile << left << setw(10) << "Account" << setw(16)
        << "Last Name" << setw(11) << "First Name" << right
        << setw(10) << "Balance" << endl;

    readFromFile.seekg(0);

    ClientData client;
    readFromFile.read(reinterpret_cast<char*>(&client),
        sizeof(ClientData));

    while (!readFromFile.eof())
    {
        if (client.getAccountNumber() != 0)
           outputLine(outPrintFile, client);

        readFromFile.read(reinterpret_cast<char*>(&client),
            sizeof(ClientData));
    } // end while
} // end function createTextFile

void updateRecord(fstream& updateFile)
{
    int accountNumber = getAccount("Enter account to update");

    updateFile.seekg((accountNumber - 1) * sizeof(ClientData));

    ClientData client;
    updateFile.read(reinterpret_cast<char*>(&client),
        sizeof(ClientData));

    if (client.getAccountNumber() != 0)
    {
        outputLine(cout, client); 

        cout << "\nEnter charge (+) or payment (-): ";
        double transaction;
        cin >> transaction;

        double oldBalance = client.getBalance();
        client.setBalance(oldBalance + transaction);
        outputLine(cout, client);

        updateFile.seekp((accountNumber - 1) * sizeof(ClientData));

        updateFile.write(reinterpret_cast<const char*>(&client),
            sizeof(ClientData));
    } // end if
    else 
        cerr << "Account #" << accountNumber
        << " has no information." << endl;
} // end function updateRecord

void newRecord(fstream& insertInFile)
{
    int accountNumber = getAccount("Enter new account number");

    insertInFile.seekg((accountNumber - 1) * sizeof(ClientData));

    ClientData client;
    insertInFile.read(reinterpret_cast<char*>(&client),
        sizeof(ClientData));

    if (client.getAccountNumber() == 0)
    {
        string lastName;
        string firstName;
        double balance;

        cout << "Enter lastname, firstname, balance\n? ";
        cin >> lastName;
        cin >> firstName;
        cin >> balance;

        client.setLastName(lastName);
        client.setFirstName(firstName);
        client.setBalance(balance);
        client.setAccountNumber(accountNumber);

        insertInFile.seekp((accountNumber - 1) * sizeof(ClientData));
             
        insertInFile.write(reinterpret_cast<const char*>(&client),
            sizeof(ClientData));
    } // end if
    else 
        cerr << "Account #" << accountNumber
        << " already contains information." << endl;
} // end function newRecord

void deleteRecord(fstream& deleteFromFile)
{
    int accountNumber = getAccount("Enter account to delete");

    deleteFromFile.seekg((accountNumber - 1) * sizeof(ClientData));

    ClientData client;
    deleteFromFile.read(reinterpret_cast<char*>(&client),
        sizeof(ClientData));

    if (client.getAccountNumber() != 0)
    {
        ClientData blankClient; 

        deleteFromFile.seekp((accountNumber - 1) *
            sizeof(ClientData));

        deleteFromFile.write(
            reinterpret_cast<const char*>(&blankClient),
            sizeof(ClientData));

        cout << "Account #" << accountNumber << " deleted.\n";
    } // end if
    else 
        cerr << "Account #" << accountNumber << " is empty.\n";
} // end deleteRecord

void outputLine(ostream& output, const ClientData& record)
{
    output << left << setw(10) << record.getAccountNumber()
        << setw(16) << record.getLastName()
        << setw(11) << record.getFirstName()
        << setw(10) << setprecision(2) << right << fixed
        << showpoint << record.getBalance() << endl;
} // end function outputLine

int getAccount(const char* const prompt)
{
    int accountNumber;

    do
    {
        cout << prompt << " (1 - 100): ";
        cin >> accountNumber;
    } while (accountNumber < 1 || accountNumber > 100);

    return accountNumber;
}