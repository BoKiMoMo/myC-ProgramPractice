#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib> 

using namespace std;

enum RequestType {	ZERO_BALANCE = 1,CREDIT_BALANCE,DEBIT_BALANCE,END};
int getRequset();
bool shouldDisplay(int, double);
void outputLine(int, const string&, double);

int main()
{
	ifstream inClientFile("clients.txt", ios::in);

	if (!inClientFile)
	{
		cerr << "File could not be opened" << endl;
		exit(EXIT_FAILURE);
	}//end if 

	int account;
	string name;
	double balance;

	int request = getRequset();

	while (request != END)
	{
		switch (request)
		{
		case ZERO_BALANCE:
			cout << "\nAccounts with zero balance : \n";
			break;

		case CREDIT_BALANCE:
			cout << "\nAccounts with credit balance : \n";
			break;

		case DEBIT_BALANCE:
			cout << "\nAccounts with debit balance : \n";
			break;
		}//end switch

		inClientFile >> account >> name >> balance;

		while (!inClientFile.eof())
		{
			if (shouldDisplay(request, balance))
				outputLine(account, name, balance);

			inClientFile >> account >> name >> balance;
		}//end inner while

		inClientFile.clear();
		inClientFile.seekg(0);
		request = getRequset();
	}//end outer while

	cout << "End of run." << endl;
}

int getRequset()
{
	int request;

	cout << "\nEnter request" << endl
		<< " 1 - List accounts with zero balances" << endl
		<< " 2 - List accounts with credit balances" << endl
		<< " 3 - List accounts with debit balances" << endl
		<< " 4 - End of run" << fixed << showpoint;

	do
	{
		cout << "\n? ";
		cin >> request;
	} while (request<ZERO_BALANCE && request > END);

	return request;
}

bool shouldDisplay(int type , double balance)
{
	if (type == ZERO_BALANCE && balance == 0)
		return true;

	if (type == CREDIT_BALANCE && balance < 0)
		return true;

	if (type == DEBIT_BALANCE && balance > 0)
		return true;

	return false;
}

void outputLine(int account, const string& name, double balance)
{
	cout << left << setw(10) << account << setw(13) << name
		<< setw(7) << setprecision(2) << right << balance << endl;
}
