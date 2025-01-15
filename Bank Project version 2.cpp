#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

const string path = "File.txt";

void Bank();

void TransactionScreen();

enum enAction { Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Transaction = 6 , Exit = 7 };

enum enTrans {Deposit = 1, Withdraw = 2, TotalBalances = 3, MainMenu = 4};

enTrans ReadTrans()
{
	short num;
	cout << "Choose what do you want to do? [1 to 4] ?";
	cin >> num;
	return (enTrans)num;
}

string ReadString()
{
	string s1;
	cout << "Enter Account Number ?";
	getline(cin >> ws, s1);
	return s1;
}

struct stInfo
{
	string accountNum, pinCode;
	string name, phone;
	double accountBalance;
	bool MarkForDelete = false;
};

vector<string> spiltString(string s1, string delim)
{
	vector<string> vString;
	string sword;
	short pos = 0;

	while ((pos = s1.find(delim)) != string::npos)
	{
		sword = s1.substr(0, pos);
		if (sword != " ")
		{
			vString.push_back(sword);
		}
		s1.erase(0, pos + delim.length());
	}
	if (s1 != " ")
	{
		vString.push_back(s1);
	}
	return vString;
}

stInfo convertLineToRecort(string line, string seprator = "#//#")
{
	vector<string> vstring = spiltString(line, seprator);

	stInfo info;

	info.accountNum = vstring[0];
	info.pinCode = vstring[1];
	info.name = vstring[2];
	info.phone = vstring[3];
	info.accountBalance = stod(vstring[4]);

	return info;
}

string ConvertRecordToLine(stInfo client, string seprator = "#//#")
{
	string ClientRec = "";

	ClientRec += client.accountNum + seprator;
	ClientRec += client.pinCode + seprator;
	ClientRec += client.name + seprator;
	ClientRec += client.phone + seprator;
	ClientRec += to_string(client.accountBalance);

	return ClientRec;
}

bool FindClient(stInfo& client, vector<stInfo> vClient, string searNum)
{
	for (stInfo& c : vClient)
	{
		if (c.accountNum == searNum)
		{
			client = c;
			return true;
		}
	}
	return false;
}

vector<stInfo> LoadDataFromFileToVector(string path)
{
	vector<stInfo> vClient;
	stInfo client;
	fstream MyFile;

	MyFile.open(path, ios::in);
	if (MyFile.is_open())
	{
		string line;
		while (getline(MyFile, line))
		{
			client = convertLineToRecort(line);
			vClient.push_back(client);
		}
		MyFile.close();
	}
	return vClient;
}

void printStruct(stInfo info)
{
	cout << "Account Num : " << info.accountNum << endl;
	cout << "Pin Code    : " << info.pinCode << endl;
	cout << "Name        : " << info.name << endl;
	cout << "Phone       : " << info.phone << endl;
	cout << "Account Balance : " << info.accountBalance << endl;
}

void printStructForAll(stInfo info)
{
	cout << "| " << setw(15) << left << info.accountNum;
	cout << "| " << left << setw(10) << info.pinCode;
	cout << "| " << setw(40) << left << info.name;
	cout << "| " << setw(12) << left << info.phone;
	cout << "| " << left << setw(10) << info.accountBalance;
}

void PrintClients(vector<stInfo> vClient)
{
	cout << "\t\t\tClint list (" << vClient.size() << ") clinet(s).";
	cout << "\n-----------------------------------------------------------------------------------------------\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n-----------------------------------------------------------------------------------------------\n";
	for (stInfo& client : vClient)
	{
		printStructForAll(client);
		cout << endl;
	}
	cout << "\n-----------------------------------------------------------------------------------------------\n";

}

bool MarkForDeleteClient(vector<stInfo>& vClient, string searNum)
{
	for (stInfo& client : vClient)
	{
		if (client.accountNum == searNum)
		{
			client.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector<stInfo> saveClientToFileAfterDelete(vector<stInfo>& vClient)
{
	fstream MyFile;
	string line;
	MyFile.open(path, ios::out);
	if (MyFile.is_open())
	{
		for (stInfo& client : vClient)
		{
			if (!client.MarkForDelete)
			{
				line = ConvertRecordToLine(client);
				MyFile << line << endl;
			}
		}
		MyFile.close();
	}
	return vClient;
}

bool DeleteClient(vector<stInfo> vClient, string searNum)
{
	stInfo client;
	char ans = 'n';

	if (FindClient(client, vClient, searNum))
	{
		printStruct(client);

		cout << "Are you sure you want to delete this record y/n ?";
		cin >> ans;

		if (toupper(ans) == 'Y')
		{
			MarkForDeleteClient(vClient, searNum);
			saveClientToFileAfterDelete(vClient);

			vClient = LoadDataFromFileToVector(path);

			cout << "\nthe client Deleted Successfully.\n";
			return true;
		}
	}
	else
	{
		cout << "Client with account number (" << searNum << ") Not found !\n";
		return false;
	}

}

stInfo ReadNewClient()
{
	stInfo info;
	cout << "Enter Account Num ? ";
	getline(cin >> ws, info.accountNum);

	cout << "Enter Pin Code ? ";
	getline(cin, info.pinCode);

	cout << "Enter Your name ? ";
	getline(cin, info.name);

	cout << "Enter Phone ? ";
	getline(cin, info.phone);

	cout << "Enter Account Balance ? ";
	cin >> info.accountBalance;

	return info;
}

stInfo ReadClientToUpdate(string searNum)
{
	stInfo info;

	info.accountNum = searNum;

	cout << "Enter Pin Code ? ";
	getline(cin >> ws, info.pinCode);

	cout << "Enter Your name ? ";
	getline(cin, info.name);

	cout << "Enter Phone ? ";
	getline(cin, info.phone);

	cout << "Enter Account Balance ? ";
	cin >> info.accountBalance;

	return info;
}

vector<stInfo> saveClientToFileAfterUpdate(vector<stInfo>& vClient, string searNum)
{
	fstream MyFile;
	string line;
	MyFile.open(path, ios::out);


	if (MyFile.is_open())
	{
		for (stInfo& client : vClient)
		{
			if (client.accountNum == searNum)
			{
				line = ConvertRecordToLine(ReadClientToUpdate(searNum));
				MyFile << line << endl;
			}
			else
			{
				line = ConvertRecordToLine(client);
				MyFile << line << endl;
			}
		}
		MyFile.close();
	}
	return vClient;
}

bool UpdateClient(vector<stInfo>& vClient, string searNum)
{
	stInfo client;
	char ans = 'n';

	if (FindClient(client, vClient, searNum))
	{
		printStruct(client);

		cout << "Are you sure you want to Update this record y/n ?";
		cin >> ans;

		if (toupper(ans) == 'Y')
		{

			saveClientToFileAfterUpdate(vClient, searNum);


			cout << "\nthe client Updated Successfully.\n";
			return true;
		}
	}
	else
	{
		cout << "Client with account number (" << searNum << ") Not found !\n";
		return false;
	}

}

void ShowMenueScreen()
{
	cout << "====================================================\n";
	cout << "\t\t Main Menu Screen \n";
	cout << "====================================================\n";
	cout << "\t [1] Show Client List.\n";
	cout << "\t [2] Add New Client.\n";
	cout << "\t [3] Delete Client.\n";
	cout << "\t [4] Update Client.\n";
	cout << "\t [5] Find Client.\n";
	cout << "\t [6] Transaction.\n";
	cout << "\t [7] Exit.\n";
	cout << "====================================================\n";
}

void saveClietToFileAfterAdding(string rec, string clinetFile)
{
	fstream MyFile;
	MyFile.open(clinetFile, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << rec << endl;

		MyFile.close();
	}
}

enAction ActionChoice()
{
	short choice = 0;
	cout << "Choose what you want to do? [1 to 7]? ";
	cin >> choice;
	return (enAction)choice;
}

void goBack()
{
	cout << "Press any key to go the main menu... ";
	system("pause > 0");
	Bank();
}

void goBackToTransaction()
{
	cout << "Press any key to go the main menu... ";
	system("pause > 0");
	TransactionScreen();
}

void ShowList(vector<stInfo> vClinet)
{
	system("cls");
	PrintClients(vClinet);
	goBack();
}

void AddClient(vector<stInfo>& vClinet)
{
	system("cls");
	cout << "====================================================\n";
	cout << "\t\tAdd Client Screen \n";
	cout << "====================================================\n";
	saveClietToFileAfterAdding(ConvertRecordToLine(ReadNewClient()), path);
	vClinet = LoadDataFromFileToVector(path);
	goBack();
}

void FinalDelete(vector<stInfo>& vClinet)
{
	system("cls");
	cout << "====================================================\n";
	cout << "\t\tDelete Client Screen \n";
	cout << "====================================================\n";
	string searNum = ReadString();
	DeleteClient(vClinet, searNum);
	goBack();
}

void FinalUpdate(vector<stInfo>& vClinet)
{
	system("cls");
	cout << "====================================================\n";
	cout << "\t\tUpdate Screen \n";
	cout << "====================================================\n";
	string searNum = ReadString();
	UpdateClient(vClinet, searNum);
	goBack();
}

void FinalFind(vector<stInfo>& vClinet)
{
	system("cls");
	cout << "====================================================\n";
	cout << "\t\tFind Client Screen \n";
	cout << "====================================================\n";
	stInfo client;
	string searNum = ReadString();
	FindClient(client, vClinet, searNum);
	printStruct(client);
	goBack();
}

void ExitShow()
{
	system("cls");
	cout << "--------------------------------\n";
	cout << "\tProgram Ends :-)\n";
	cout << "--------------------------------\n";
}

vector<stInfo> saveClientToFileAfterDeposit(vector<stInfo>& vClient, string searNum, double dep)
{
	fstream MyFile;
	string line;
	MyFile.open(path, ios::out);


	if (MyFile.is_open())
	{
		for (stInfo& client : vClient)
		{
			if (client.accountNum == searNum)
			{
				client.accountBalance += dep; 
				line = ConvertRecordToLine(client);
				MyFile << line << endl;
			}
			else
			{
				line = ConvertRecordToLine(client);
				MyFile << line << endl;
			}
		}
		MyFile.close();
	}
	return vClient;
}

void deposit()
{
	vector<stInfo> vClients = LoadDataFromFileToVector(path);
	string SearNum;
	stInfo client;
	char ans = 'n';
	double dep = 0;

	do
	{
		SearNum = ReadString();

	} while (!FindClient(client, vClients, SearNum));

	printStruct(client);


	cout << "\nPlease enter a deposit amount ";
	cin >> dep;
	
	cout << "\nAre you sure you want to deposit " << dep <<  " to "<< client.accountNum << " y/n ?";
	cin >> ans;

	if (toupper(ans) == 'Y')
	{
		client.accountBalance += dep;
		saveClientToFileAfterDeposit(vClients, SearNum, dep);
		cout << "\ndone successfully, new balance is : " << client.accountBalance << endl;
	}
	
}

void DepositScreen()
{
	system("cls");
	cout << "-----------------------------\n";
	cout << "\tDeposit Screen\n";
	cout << "-----------------------------\n";
	deposit();
	goBackToTransaction();
}

vector<stInfo> saveClientToFileAfterWithdraw(vector<stInfo>& vClient, string searNum, double with)
{
	fstream MyFile;
	string line;
	MyFile.open(path, ios::out);


	if (MyFile.is_open())
	{
		for (stInfo& client : vClient)
		{
			if (client.accountNum == searNum)
			{
				client.accountBalance -= with;
				line = ConvertRecordToLine(client);
				MyFile << line << endl;
			}
			else
			{
				line = ConvertRecordToLine(client);
				MyFile << line << endl;
			}
		}
		MyFile.close();
	}
	return vClient;
}

void withdraw()
{
	vector<stInfo> vClients = LoadDataFromFileToVector(path);
	string SearNum;
	stInfo client;
	char ans = 'n';
	double with = 0;

	do
	{
		SearNum = ReadString();

	} while (!FindClient(client, vClients, SearNum));

	printStruct(client);


	cout << "\nPlease enter the withdraw amount ";
	cin >> with;
	
	cout << "\nAre you sure you want to Withdraw " << with <<  " to "<< client.accountNum << " y/n ?";
	cin >> ans;

	if (toupper(ans) == 'Y')
	{
		client.accountBalance -= with;
		saveClientToFileAfterWithdraw(vClients, SearNum, with);
		cout << "\ndone successfully, The balance after withdraw is : " << client.accountBalance << endl;
	}
	
}

void WithdrawScreen()
{
	system("cls");
	cout << "-----------------------------\n";
	cout << "\tWithdraw Screen\n";
	cout << "-----------------------------\n";
	withdraw();
	goBackToTransaction();
}

void printStructForBalance(stInfo info)
{
	cout << "| " << setw(15) << left << info.accountNum;
	cout << "| " << setw(40) << left << info.name;
	cout << "| " << left << setw(10) << info.accountBalance;
}

void PrintClientsForBaalance(vector<stInfo> vClient)
{
	double totalBalnces = 0;

	cout << "\t\t\tClint list (" << vClient.size() << ") clinet(s).";
	cout << "\n-----------------------------------------------------------------------------------------------\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n-----------------------------------------------------------------------------------------------\n";
	for (stInfo& client : vClient)
	{
		printStructForAll(client);
		totalBalnces += client.accountBalance;
		cout << endl;
	}
	cout << "\n-----------------------------------------------------------------------------------------------\n";

	cout << "\t\t\tTotal Balances = " << totalBalnces << endl;
}

void TotalBalancesScreen()
{
	system("cls");
	vector<stInfo> vClient = LoadDataFromFileToVector(path);
	PrintClientsForBaalance(vClient);
	goBackToTransaction();
}

void ProcessTheTrans(enTrans Transaction)
{
	switch (Transaction)
	{
	case Deposit:
		DepositScreen();
		break;
	case Withdraw:
		WithdrawScreen();
		break;
	case TotalBalances:
		TotalBalancesScreen();
		break;
	case MainMenu:
		system("cls");
		Bank();
		break;
	}
}

void TransactionScreen()
{
	system("cls");
	cout << "====================================================\n";
	cout << "\t\tTransaction Menu Screen \n";
	cout << "====================================================\n";
	cout << "\t [1] Deposit.\n";
	cout << "\t [2] Withdraw.\n";
	cout << "\t [3] Total Balances.\n";
	cout << "\t [4] Main Menu.\n";
	cout << "====================================================\n";
	ProcessTheTrans(ReadTrans());
}

void ProccesTheAction(enAction Choice, vector<stInfo>& vClinet)
{
	switch (Choice)
	{
	case Show:
		ShowList(vClinet);
		break;
	case Add:
		AddClient(vClinet);
		break;
	case Delete:
		FinalDelete(vClinet);
		break;
	case Update:
		FinalUpdate(vClinet);
		break;
	case Find:
		FinalFind(vClinet);
		break;
	case Transaction:
		TransactionScreen();
		break;
	case Exit:
		ExitShow();
		break;
	}
}

void Bank()
{
	system("cls");
	vector<stInfo> vClinet = LoadDataFromFileToVector(path);
	ShowMenueScreen();
	enAction choice = ActionChoice();
	ProccesTheAction(choice, vClinet);

}

int main()
{
	Bank();
	return 0;
}