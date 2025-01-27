#include <iostream> 
#include <fstream> 
#include <iomanip>  
#include <string>   
#include <cstdlib> 

using namespace std;

void outputLine(int, const string&, double);

int main()
{
	ifstream inClinetFile("clients.txt", ios::in);

	if (!inClinetFile)
	{
		cerr << "File could not be opened" << endl;
		exit(EXIT_FAILURE);
	}//end if

	int account;
	string name;
	double balance;

	cout << left << setw(10) << "Account" << setw(13)
		<< "Name" << "Balance" << endl << fixed << showpoint;

	while (inClinetFile>>account>>name>>balance)
		outputLine(account, name, balance);
	    //end while

}//end main

void outputLine(int account, const string& name, double balance)
{
	cout << left << setw(10) << account << setw(13)
		<< name << setw(7) << setprecision(2) << right << balance << endl;
}
