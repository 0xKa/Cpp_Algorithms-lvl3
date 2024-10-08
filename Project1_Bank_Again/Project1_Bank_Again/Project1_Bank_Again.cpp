#include <iostream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream> 
using namespace std;

const string ClientsFileName = "Clients.txt";
const string DefaultSeparator = "/<>/<>/<>/";

struct stClientData
{
	string id;
	string pinCode;
	string name;
	string phone;
	double balance;
	bool MarkForDelete = false;
};

enum enMainMenuOption {
	eShowClientList = 1, eAddNewClient = 2, eDeleteClient = 3, UpdateClient = 4, eFindClient = 5, eExit = 6
};


//////////////////// Generic Functions ////////////////////

string ReadString(string Massage)
{
	string s = "";
	cout << Massage << endl;
	getline(cin >> ws, s);
	return s;
}

bool ValidateNumberBetween(int Number, int MoreThan, int LessThan)
{
	if (Number >= MoreThan && Number <= LessThan)
		return true;
	else
	{
		cout << "\nPlease Enter A Number From " << LessThan << " To " << MoreThan << endl;
		return false;
	}
}

vector <string> SplitString(string s, string separator)
{
	//separator is the same as delimeter

	vector <string> vStringWords;

	string word;
	short position = 0;

	while ((position = s.find(separator)) != s.npos)
	{
		word = s.substr(0, position);
		if (word != "")
			vStringWords.push_back(word);

		s.erase(0, position + separator.length());
	}

	if (s != "")
		vStringWords.push_back(s);

	return vStringWords;
}

string ConvertDataToLine(stClientData client, string separator = DefaultSeparator)
{
	string line = "";

	line += client.id + separator;
	line += client.pinCode + separator;
	line += client.name + separator;
	line += client.phone + separator;
	line += to_string(client.balance);
	return line;
}

stClientData ConvertLineToData(string line, string separator = DefaultSeparator)
{
	vector <string> lineSplitted = SplitString(line, separator);
	stClientData data;

	data.id = lineSplitted[0];
	data.pinCode = lineSplitted[1];
	data.name = lineSplitted[2];
	data.phone = lineSplitted[3];
	data.balance = stod(lineSplitted[4]);

	return data;
}

bool Confirm_Y_N(string massage) // generic function to confirm Yes/No Questions
{
	char ConfirmUpdate = 'n';
	cout << endl << massage << endl;
	cin >> ConfirmUpdate;

	return(tolower(ConfirmUpdate) == 'y' ? true : false);
}

vector <stClientData> LoadClientsFromFileToVector(string FileName)
{
	fstream clients;
	vector <stClientData> vClients;

	clients.open(ClientsFileName, ios::in);

	if (clients.is_open())
	{
		string line;
		while (getline(clients, line))
		{
			vClients.push_back(ConvertLineToData(line));
		}

		clients.close();
	}
	return vClients;
}

void LoadClientsFromVectorToFile(string FileName, vector <stClientData> vClients)
{
	fstream Client;

	Client.open(FileName, ios::out); //overwrite

	if (Client.is_open())
	{
		for (stClientData c : vClients)
		{
			// now we send the vector data to the file while skipping the MarkForDelete data
			if (c.MarkForDelete == false)
				Client << ConvertDataToLine(c) << endl;
		}
		Client.close();
	}

}

bool FindClientBy_ID(string id, stClientData& Client, vector <stClientData> vClients)
{
	for (stClientData c : vClients)
	{
		if (c.id == id)
		{
			Client = c; //Client is ByRef
			return true;
		}
	}
	return false;
}


////////////////////  1.Print Client List/Card Functions  ////////////////////
void PrintClientRecord(stClientData client)
{
	cout << "| " << left << setw(14) << client.id;
	cout << "| " << left << setw(9) << client.pinCode;
	cout << "| " << left << setw(39) << client.name;
	cout << "| " << left << setw(11) << client.phone;
	cout << "| " << left << setw(11) << client.balance;
	cout << "| ";
}

void PrintClientsDataList()
{
	vector <stClientData> vClientsData = LoadClientsFromFileToVector(ClientsFileName);

	if ((vClientsData.size() == 0))
		cout << "\nNo Clients Available in The System!\n\n";
	else
	{

		cout << "\t\t\t\t\tClient List: (" << vClientsData.size() << ") Client(s).\n";
		cout << "|===============|==========|========================================|============|============|\n";

		cout << "| " << left << setw(14) << "ID";
		cout << "| " << left << setw(9) << "PIN Code";
		cout << "| " << left << setw(39) << "Client Name";
		cout << "| " << left << setw(11) << "Phone";
		cout << "| " << left << setw(11) << "Balance";
		cout << "| \n";

		cout << "|===============|==========|========================================|============|============|\n";

		for (stClientData data : vClientsData)
		{
			PrintClientRecord(data);
			cout << endl;
		}
		cout << "|===============|==========|========================================|============|============|\n";
	}
}

void PrintClientCard(stClientData Client)
{
	cout << "\n==========| The following are the client details |==========\n";
	cout << "\nID      : " << Client.id;
	cout << "\nPIN Code: " << Client.pinCode;
	cout << "\nName    : " << Client.name;
	cout << "\nPhone   : " << Client.phone;
	cout << "\nBalance : " << Client.balance << "$\n";
	cout << "\n============================================================\n";
}


////////////////////      2.Adding Clients Functions     ////////////////////
void PrintAddNewClientScreen(bool onlyScreen = false); //func declaration only

bool isIdAvailable(string id, string FileName)
{
	fstream clients;

	clients.open(ClientsFileName, ios::in);

	if (clients.is_open())
	{
		string line;
		stClientData Client;

		while (getline(clients, line))
		{
			Client = ConvertLineToData(line);
			if (Client.id == id)
			{
				clients.close();
				return false; //false means the id is NOT available
			}
		}
		clients.close();
	}
	return true; //true means the id is Available
}

stClientData ReadClientData()
{
	stClientData client;


	// Usage of >>std::ws will extract all the whitespace character
	cout << "Enter Client ID: ";
	getline(cin >> ws, client.id);

	while (isIdAvailable(client.id, ClientsFileName) == false)//check if client id is available
	{
		cout << "\nClient With ID Number [" << client.id << "] Already Exists, Enter Another ID:\n";
		getline(cin >> ws, client.id);
	}

	cout << "Enter PIN Code: ";
	getline(cin, client.pinCode);

	cout << "Enter Name: ";
	getline(cin, client.name);

	cout << "Enter Phone Number: ";
	getline(cin, client.phone);

	cout << "Enter Account Balance: ";
	cin >> client.balance;

	return client;
}

void AddClientRecordLineToFile(string FileName, string RecordLine)
{
	fstream client;

	client.open(FileName, ios::out | ios::app);

	if (client.is_open())
	{
		client << RecordLine << endl;
		client.close();
	}

}

void AddNewClient()
{
	stClientData client = ReadClientData(); //getting the info of the new client 

	string line = ConvertDataToLine(client); //getting the record line of the new client

	AddClientRecordLineToFile(ClientsFileName, line); //passing the line to function to add it to file 
}

void AddClients()
{
	char addMore = 'n';

	do
	{
		if (addMore == 'y')
		{
			system("cls");
			PrintAddNewClientScreen(true);
		}
		cout << "\nAdding New Client...\n\n";

		AddNewClient();

		cout << "\nDo You Want To Add Another Client? \n";
		cin >> addMore;
	} while (tolower(addMore) == 'y');

}

void PrintAddNewClientScreen(bool PrintOnlyScreen)
{
	bool onlyScreen = PrintOnlyScreen;
	cout << "================================\n";
	cout << "         Add New Client         \n";
	cout << "================================\n";

	if (onlyScreen == false)
		AddClients();
}

////////////////////      3.Delete Clients Functions     ////////////////////
void MarkClientForDelete(string id, vector <stClientData>& vClient)
{
	for (stClientData& c : vClient)//ByRef
	{
		if (c.id == id)
			c.MarkForDelete = true;
	}
}

void DeleteClientBy_ID(string id, vector <stClientData>& vClients)
{
	stClientData Client;

	if (FindClientBy_ID(id, Client, vClients))
	{
		PrintClientCard(Client);

		if (Confirm_Y_N("Are You Sure You Want To Delete This Client?"))
		{
			MarkClientForDelete(id, vClients);

			LoadClientsFromVectorToFile(ClientsFileName, vClients);

			vClients = LoadClientsFromFileToVector(ClientsFileName); //refresh the vector because it is ByRef

			cout << "\nClient Deleted Successfully.\n";
		}
		else
			cout << "\nDeleteing the Client is Canceled\n";

	}
	else
		cout << "\nClient Number [" << id << "] Not Found!\n";

}

void PrintDeleteClientScreen()
{
	cout << "=================================\n";
	cout << "          Delete Client          \n";
	cout << "=================================\n";

	vector <stClientData> vClients = LoadClientsFromFileToVector(ClientsFileName);

	DeleteClientBy_ID(ReadString("Enter ID Number:"), vClients);
}

////////////////////      4.Update Clients Functions     ////////////////////
stClientData ChangeClientRecord(string id)
{
	stClientData Clients;

	Clients.id = id;

	cout << "\nEnter PIN Code: ";
	getline(cin >> ws, Clients.pinCode);

	cout << "Enter Name: ";
	getline(cin, Clients.name);

	cout << "Enter Phone Number: ";
	getline(cin, Clients.phone);

	cout << "Enter Account Balance: ";
	cin >> Clients.balance;

	return Clients;
}

void UpdateClientBy_ID(string id, vector <stClientData>& vClients)
{
	stClientData Client;

	if (FindClientBy_ID(id, Client, vClients))
	{
		PrintClientCard(Client);

		if (Confirm_Y_N("Are You Sure You Want To Update This Client?"))
		{
			for (stClientData& c : vClients)
			{
				if (c.id == id)
				{
					c = ChangeClientRecord(id);
					break; //quit the for loop cuase no need to continue after we updated the client
				}
			}

			LoadClientsFromVectorToFile(ClientsFileName, vClients);
			cout << "\nClient Updated Successfully.\n";
		}
		else
			cout << "\nUpdating the Client is Canceled\n";

	}
	else
		cout << "\nClient Number [" << id << "] Not Found!\n";

}

void PrintUpdeteClientScreen()
{
	cout << "=================================\n";
	cout << "          Update Client          \n";
	cout << "=================================\n";

	vector <stClientData> vClients = LoadClientsFromFileToVector(ClientsFileName);
	UpdateClientBy_ID(ReadString("Enter ID Number:"), vClients);
}

////////////////////        5.Find Client Functions      ////////////////////
void FindClientAndPrintIt(string id, vector <stClientData>& vClients)
{
	stClientData Client;
	if (FindClientBy_ID(id, Client, vClients))
	{
		PrintClientCard(Client);
	}
	else
		cout << "\nClient Number [" << id << "] Not Found!\n";
}

void PrintFindClientScreen()
{
	cout << "=================================\n";
	cout << "           Find Client           \n";
	cout << "=================================\n";

	vector <stClientData> vClients = LoadClientsFromFileToVector(ClientsFileName);
	FindClientAndPrintIt(ReadString("Enter ID Number:"), vClients);
}

////////////////////            6.Exit Screen           ////////////////////
void PrintEndScreen()
{
	cout << "==================================\n";
	cout << "           Program Ends           \n";
	cout << "==================================\n";
}

//////////////////// Main Menu ////////////////////
void ShowMainMenu(); //func declaration

void GoBackToMainMenu()
{
	cout << "Press any key to go back to Main Menu...";
	system("pause>0"); //will pause the program until the user press any key
	ShowMainMenu();
}

enMainMenuOption ReadUserOption()
{
	int UserOption;
	cout << "Choose What You Want To Do? (1 - 6)?\n";

	do
	{
		cin >> UserOption; //read the user option ByRef
	} while (ValidateNumberBetween(UserOption, 1, 6) == false);

	return enMainMenuOption(UserOption);
}

void PerformMainMenuOption(enMainMenuOption UserOption)
{
	system("cls");
	switch (UserOption)
	{
	case eShowClientList:
		PrintClientsDataList();
		break;
	case eAddNewClient:
		PrintAddNewClientScreen();
		break;
	case eDeleteClient:
		PrintDeleteClientScreen();
		break;
	case UpdateClient:
		PrintUpdeteClientScreen();
		break;
	case eFindClient:
		PrintFindClientScreen();
		break;
	case eExit:
		PrintEndScreen();
		return; //exit the func 
	}

	GoBackToMainMenu(); //this will happen after any break
}

void ShowMainMenu()
{
	system("cls");
	cout << "|======================================|\n";
	cout << "|              Main Menu               |\n";
	cout << "|======================================|\n";

	cout << "|                                      |\n";
	cout << "|---[1] Show CLient List.              |\n";
	cout << "|---[2] Add New Client.                |\n";
	cout << "|---[3] Delete Client.                 |\n";
	cout << "|---[4] Update Client.                 |\n";
	cout << "|---[5] Find Client.                   |\n";
	cout << "|---[6] Exit.                          |\n";
	cout << "|                                      |\n";

	cout << "|======================================|\n";

	PerformMainMenuOption(ReadUserOption());
}

int main()
{
	ShowMainMenu();
	cout << endl << endl;
	return 0;
}