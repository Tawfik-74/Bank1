#include <iostream>
#include<vector>
#include<string>
#include <fstream>
#include<iomanip>
using namespace std;
const string filename = "Banksystem.txt";

struct stclientinfo {
    string AccountNumber;
    string pincode;
    string ClientName;
    string PhoneNumber;
    float AccountBalance;
};
stclientinfo readClientData()
{
    stclientinfo client;
    cout << "Enter AccountNumber : ";
    getline(cin >> ws, client.AccountNumber);


    cout << "Enter pincode : ";
    getline(cin, client.pincode);

    cout << "Enter ClientName : ";
    getline(cin, client.ClientName);
    cout << endl;


    cout << "Enter PhoneNumber : ";
    getline(cin, client.PhoneNumber);


    cout << "Enter AccountBalance : ";
    cin >> client.AccountBalance;


    return client;
}
string convertlinetodata(stclientinfo client) {

    string adaptar = "";
    adaptar += client.AccountNumber + "//";
    adaptar += client.pincode + "//";
    adaptar += client.ClientName + "//";
    adaptar += client.PhoneNumber + "//";

    adaptar += to_string(client.AccountBalance) + "//";

    return adaptar;

}
void loaddatatofile(string filena, string clientdatarecord) {

    fstream bank1;
    bank1.open(filena, ios::out | ios::app);

    if (bank1.is_open())
    {
        bank1 << clientdatarecord << endl;
        bank1.close();
    }
}
void addclient() {
    stclientinfo client = readClientData();

    loaddatatofile(filename, convertlinetodata(client));
}
void addclients() {
    char addmore = 'Y';

    do
    {
        cout << "Enter clients info : \n\n";
        addclient();

        cout << "\nClient added succsesfuly , do you want to add more clients? ";
        cin >> addmore;

    } while (toupper(addmore) == 'Y');
}
void loaddataformfiletovector(string filename, vector<string>& data) {


    fstream bankfile;
    bankfile.open(filename, ios::in);

    if (bankfile.is_open())
    {
        string line;
        while (getline(bankfile, line)) {

            data.push_back(line);

        }
        bankfile.close();
    }

}

vector <string> SplitString(string Str, string delim)
{
    vector <string> vString;
    string sWord = "";
    short Pos = 0;

    while ((Pos = Str.find(delim)) != std::string::npos)
    {
        sWord = Str.substr(0, Pos);

        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        Str = Str.erase(0, Pos + delim.length());
    }

    if (Str != "")
    {
        vString.push_back(Str);
    }

    return vString;
}
stclientinfo convertlinetorecord(string line, string se = "//") {

    stclientinfo client;
    vector<string>vclientdata;
    vclientdata = SplitString(line, se);
    client.AccountNumber = vclientdata[0];
    client.pincode = vclientdata[1];
    client.ClientName = vclientdata[2];
    client.PhoneNumber = vclientdata[3];
    client.AccountBalance = stod(vclientdata[4]);
    return client;

}
vector<stclientinfo>loaddatafromfile(string filename) {
    vector<stclientinfo>vclients;
    fstream bank1;
    bank1.open(filename, ios::in);

    if (bank1.is_open())
    {
        string line;
        stclientinfo client;
        while (getline(bank1, line)) {
            client = convertlinetorecord(line);

            vclients.push_back(client);
        }
        bank1.close();
    }
    return vclients;
}
void printclientrecord(stclientinfo clientdata) {

    cout << "| " << setw(15) << left << clientdata.AccountNumber;
    cout << "| " << setw(10) << left << clientdata.pincode;
    cout << "| " << setw(40) << left << clientdata.ClientName;
    cout << "| " << setw(12) << left << clientdata.PhoneNumber;
    cout << "| " << setw(12) << left << clientdata.AccountBalance;

}
void printallclientsdata(vector<stclientinfo>& vclients) {

    cout << "\n\t\t\t\t\tClient List(" << vclients.size() << ")Client(s)";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (stclientinfo& info : vclients)
    {
        printclientrecord(info);
        cout << endl
            ;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
bool findclientsbby(string AccountNumber, stclientinfo& client) {

    vector<stclientinfo>vclients = loaddatafromfile(filename);

    for (stclientinfo& c : vclients)
    {
        if (c.AccountNumber == AccountNumber)
        {
            client = c;
            return true;
        }
    }
    return false;
}
void PrintClientCard(stclientinfo Client) {

    cout << "The Following are the client details : \n";
    cout << "Account Number :" << Client.AccountNumber << endl;
    cout << "PinCode : " << Client.pincode << endl;
    cout << "Name : " << Client.ClientName << endl;
    cout << "Phone : " << Client.PhoneNumber << endl;
    cout << "Account Balance : " << Client.AccountBalance << endl;
}
string readaccountnumber() {
    string accoiunnumber;
    cout << "pleases enter account number : ";
    cin >> accoiunnumber;
    return accoiunnumber;
}

/*Delete Account Founcations*/

void SaveAllClientsToFile(vector<stclientinfo>& vclients) {
    fstream bankFile;
    bankFile.open(filename, ios::out);

    if (bankFile.is_open()) {
        for (stclientinfo& client : vclients) {
            bankFile << convertlinetodata(client) << endl;
        }
        bankFile.close();
    }
}

bool DeleteClientByAccountNumber(string AccountNumber) {
    vector<stclientinfo> vclients = loaddatafromfile(filename);
    bool found = false;

    vector<stclientinfo> UpdatedClients;
    for (stclientinfo& client : vclients) {
        if (client.AccountNumber != AccountNumber) {
            UpdatedClients.push_back(client);
        }
        else {
            found = true;
        }
    }

    if (found) {
        SaveAllClientsToFile(UpdatedClients);
    }
    return found;
}

void DeleteClient() {
    string AccountNumber = readaccountnumber();
    stclientinfo client;

    if (findclientsbby(AccountNumber, client)) {
        PrintClientCard(client);

        char confirm;
        cout << "Are you sure you want to delete this account? (Y/N): ";
        cin >> confirm;

        if (toupper(confirm) == 'Y') {
            if (DeleteClientByAccountNumber(AccountNumber)) {
                cout << "Client deleted successfully!\n";
            }
        }
        else {
            cout << "Operation canceled.\n";
        }
    }
    else {
        cout << "Client not found!\n";
    }
}

/*updat clients data */
void UpdateClientByAccountNumber(string AccountNumber) {
    vector<stclientinfo> vclients = loaddatafromfile(filename);
    bool found = false;

    for (stclientinfo& client : vclients) {
        if (client.AccountNumber == AccountNumber) {
            found = true;
            cout << "Client found! Enter new data:\n";
            client = readClientData();
            client.AccountNumber = AccountNumber;
            break;
        }
    }

    if (found) {
        SaveAllClientsToFile(vclients);
        cout << "Client data updated successfully!\n";
    }
    else {
        cout << "Client not found!\n";
    }
}

void EditClient() {
    string AccountNumber = readaccountnumber();
    stclientinfo client;

    if (findclientsbby(AccountNumber, client)) {
        PrintClientCard(client);

        char confirm;
        cout << "Are you sure you want to edit this client? (Y/N): ";
        cin >> confirm;

        if (toupper(confirm) == 'Y') {
            UpdateClientByAccountNumber(AccountNumber);
        }
        else {
            cout << "Operation canceled.\n";
        }
    }
    else {
        cout << "Client not found!\n";
    }
}
/*Client Menu Data*/
void showMenu() {
    cout << "\n====================================\n";
    cout << "         BANK SYSTEM MENU          \n";
    cout << "====================================\n";
    cout << "1. Add New Client\n";
    cout << "2. Show All Clients\n";
    cout << "3. Search for a Client\n";
    cout << "4. Edit Client Information\n";
    cout << "5. Delete Client\n";
    cout << "6. Exit\n";
    cout << "====================================\n";
    cout << "Enter your choice: ";
}


int main() {
    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            addclients();
            break;
        case 2:
        {
            vector<stclientinfo> clients = loaddatafromfile(filename);
            if (clients.empty()) {
                cout << "\n📢 No clients found in the system.\n";
            }
            else {
                printallclientsdata(clients);
            }
        }
        break;

        case 3:
        {
            stclientinfo client;
            if (findclientsbby(readaccountnumber(), client)) {
                PrintClientCard(client);
            }
            else {
                cout << "Client not found!\n";
            }
        }
        break;
        case 4:
            EditClient();
            break;
        case 5:
            DeleteClient();
            break;
        case 6:
            cout << "Exiting... Thank you for using our system!\n";
            break;
        default:
            cout << "Invalid choice! Please enter a number between 1 and 6.\n";
        }
    } while (choice != 6);

    return 0;
}
 