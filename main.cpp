#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <chrono>
using namespace std;
// -----------Constants-----------
#define AdUsername "ZiadSameh"
#define AdPassword "Zezo@sameh2003"
#define LinesEachUser 10
#define LinesEachTrip 12
#define LinesEachWallet 4
#define LinesEachReserv 12
// -----------Variables-----------
string AdUser, AdPass;
string ClUser, ClPass;
int NumberOfLines = 0;
int FileLines = 0;
int firstnameLine = 0;
int NumberOfTrips = 0;
string trip1Cost, trip1Tickets;
string oldDestination; // to be used to search for the old trip
// -----------booleans-----------
bool isAdmin = false;
bool isClient = false;
bool isAdUserC = false;
bool isAdPassC = false;
bool isLogin = false;
bool isRegister = false;
bool isClUserC = false;
bool isClPassC = false;
bool AdLogConf = false;
bool ClLogConf = false;
bool canAdd = true;
// -----------structure-----------
struct user
{
    string username;
    string firstname;
    string lastname;
    string phonenumber;
    string email;
    string address;
    string password1;
    string password2; // for confirmation
    string wallet;
} userReg;
struct trip
{
    string id;
    string startDate;
    string endDate;
    string destination;
    string transportation;
    string hotelName;
    string hotelAddress;
    string boarding;
    string maxReservations;
    string numReservations;
    string tripCost;
} tripInfo;
struct reservation
{
    string reservNum;
    string clientUsername;
    string destination;
    string cost;
    string numPeople;
    string paymentMeth;
    string confPayment;
    bool isReservationDone;
} reservationInfo{};
// ----------functions----------
void roleInput();
void adminLogin();
void checkAdmin();
void clientLogin();
void clientRegister();
void clientMenu();
void SaveClientInfo();
bool R_Username_Unique();
bool R_Phone_CFormat(string number);
bool R_Email_CFormat(string email);
bool R_Pass_Conf();
bool L_ValUser();
bool L_ValPass();
int PrevUserID();
string GetFirstName(int firstnameline);
int NumberOfUsers();
int NumberofTrips();
void adminMenu();
void addTrip();
void saveTrips();
void updateTrip();
void deleteTrip();
void showReservs();
void showUsers();
void confRequests();
void adLogout();
void clientMenu2();
void reserveTrip();
void saveReservInfo();
void refreshWallet();
void changeReserv();
void HistReserv();
void openReserv();
void cancelReserv();
void putWallet();
void saveWalletInfo();
void editAccInfo();
void clLogout();
// Miscellaneous functions
void checkTrip(); // function used in changeReserv function to check if the trip we want to reserve is found or not
// -------------------------
void roleInput()
{
    char AdorCl[100] = {};
    cout << "Are you an admin or a client?\n"
         << "* An admin ( Press One )\n"
         << "* A Client ( Press Two )\n"
         << "Your Answer: ";
    cin >> AdorCl;
    while (AdorCl[1] != '\0') // check if there is any other character after the number
    {
        cout << "You entered an incorrect choice. Please enter a correct choice: ";
        cin >> AdorCl;
    }
    while (AdorCl[0] != '1' && AdorCl[0] != '2')
    {
        cout << "You entered an incorrect choice. Please enter a correct choice: ";
        cin >> AdorCl;
    }
    switch (AdorCl[0])
    {
    case '1':
        isAdmin = true;
        isClient = false;
        adminLogin();
        break;
    case '2':
        isClient = true;
        isAdmin = false;
        clientMenu();
        break;
    }
}
// ----------Admin----------
void adminLogin()
{
    bool symbsIC = false;
    if (isAdmin)
    {
        isClient = false;
        cout << "--> Enter Username: ";
        cin.ignore();
        getline(cin, AdUser);
        // check that the username doesn't contain any other symbol rather than small, capital letters and numbers
        while (true)
        {
            for (int i = 0; i < AdUser.size(); i++)
            {
                if (!(AdUser[i] >= 65 && AdUser[i] <= 122) && !(AdUser[i] >= 48 && AdUser[i] <= 57))
                {
                    symbsIC = true;
                    break;
                }
            }
            if (symbsIC)
            {
                cout << "********** It's not allowed to type any symbols except small, capital letters and numbers **********\n";
                cout << "Please type your username again:\n--> Enter Username: ";
                getline(cin, AdUser);
                symbsIC = false;
            }
            else
            {
                break;
            }
        }
        cout << "--> Enter Password: ";
        getline(cin, AdPass);
    }
    checkAdmin();
}
void checkAdmin()
{
    char temp;
    if (isAdmin)
    {
        char chLogin[100] = {};
        if (AdUser == AdUsername)
        {
            isAdUserC = true;
        }
        else
        {
            isAdUserC = false;
        }
        if (AdPass == AdPassword)
        {
            isAdPassC = true;
        }
        else
        {
            isAdPassC = false;
        }
        if (isAdUserC && isAdPassC)
        {
            adminMenu();
            AdLogConf = true;
        }
        else
        {
            AdLogConf = false;
            cout << "Either the username or the password or both are incorrect :( " << endl;
            cout << "Do you want to try again? Y|N: ";
            cin >> chLogin;
            while (chLogin[1] != '\0')
            {
                cout << "You entered an incorrect choice. Please enter a correct choice: ";
                cin >> chLogin;
            }
            while (chLogin[0] != 'y' && chLogin[0] != 'Y' && chLogin[0] != 'n' && chLogin[0] != 'N')
            {
                cout << "You entered an incorrect choice. Please enter a correct choice: ";
                cin >> chLogin;
            }
            switch (chLogin[0])
            {
            case 'Y':
            case 'y':
                adminLogin();
                break;
            case 'n':
            case 'N':
                system("clear");
                roleInput();
                break;
            }
        }
    }
}
void adminMenu()
{
    char answer[100] = {};
    system("clear");
    //cout << "Welcome back Admin :)" << endl;
    cout << "User: Admin";
    cout << "                                                           **Admin Menu**" << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << "* Add a Trip               (Press One)" << endl;
    cout << "* Update a Trip Info       (Press Two)" << endl;
    cout << "* Delete a Trip            (Press Three)" << endl;
    cout << "* Show All Reservations    (Press Four)" << endl;
    cout << "* Show Users               (Press Five)" << endl;
    cout << "* Confirmation Requests    (Press Six)" << endl;
    cout << "* Logout                   (Press Seven)" << endl;
    cout << "--> Your Answer: ";
    cin >> answer;
    // to check that the user entered only from 1 --> 6
    while (answer[1] != '\0')
    {
        system("clear");
        cout << "User: Admin";
        cout << "                                                           **Admin Menu**" << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
        cout << "You entered an incorrect choice!" << endl;
        cout << "* Add a Trip               (Press One)" << endl;
        cout << "* Update a Trip Info       (Press Two)" << endl;
        cout << "* Delete a Trip            (Press Three)" << endl;
        cout << "* Show All Reservations    (Press Four)" << endl;
        cout << "* Show Users               (Press Five)" << endl;
        cout << "* Confirmation Requests    (Press Six)" << endl;
        cout << "* Logout                   (Press Seven)" << endl;
        cout << "--> Your Answer: ";
        cin >> answer;
    }
    while (!(answer[0] >= 49 && answer[0] <= 55))
    {
        system("clear");
        cout << "User: Admin";
        cout << "                                                           **Admin Menu**" << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
        cout << "You entered an incorrect choice!" << endl;
        cout << "* Add a Trip               (Press One)" << endl;
        cout << "* Update a Trip Info       (Press Two)" << endl;
        cout << "* Delete a Trip            (Press Three)" << endl;
        cout << "* Show All Reservations    (Press Four)" << endl;
        cout << "* Show Users               (Press Five)" << endl;
        cout << "* Confirmation Requests    (Press Six)" << endl;
        cout << "* Logout                   (Press Seven)" << endl;
        cout << "--> Your Answer: ";
        cin >> answer;
    }
    switch (answer[0])
    {
    case '1':
        addTrip();
        break;
    case '2':
        updateTrip();
        break;
    case '3':
        deleteTrip();
        break;
    case '4':
        showReservs();
        break;
    case '5':
        showUsers();
        break;
    case '6':
        confRequests();
        break;
    case '7':
        adLogout();
        break;
    }
}
void addTrip()
{
    system("clear");
    cout << "User: Admin                    Action: Adding Trip..." << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << "--> Enter Trip ID: ";
    cin >> tripInfo.id;
    cout
        << "--> Enter Start Date: ";
    cin.ignore();
    getline(cin, tripInfo.startDate);
    cout << "--> Enter End Date: ";
    getline(cin, tripInfo.endDate);
    cout << "--> Enter Destination: ";
    getline(cin, tripInfo.destination);
    cout << "--> Enter Means of Transportation: ";
    getline(cin, tripInfo.transportation);
    cout << "--> Enter Hotel Name: ";
    getline(cin, tripInfo.hotelName);
    cout << "--> Enter Hotel Address: ";
    getline(cin, tripInfo.hotelAddress);
    cout << "--> Enter Type of Boarding: ";
    getline(cin, tripInfo.boarding);
    cout << "--> Enter Maximum Number of Reservation: ";
    cin >> tripInfo.maxReservations;
    cout << "--> Enter Number of Reservation Made: ";
    cin >> tripInfo.numReservations;
    cout << "--> Enter Trip Cost: ";
    cin >> tripInfo.tripCost;
    saveTrips();
}
void saveTrips()
{
    char inChar[100] = {};
    char temp = inChar[0];
    ofstream outputData;
    outputData.open("data/tripsInfo.txt", ios::app);
    outputData << tripInfo.id << endl;
    outputData << tripInfo.startDate << endl;
    outputData << tripInfo.endDate << endl;
    outputData << tripInfo.destination << endl;
    outputData << tripInfo.transportation << endl;
    outputData << tripInfo.hotelName << endl;
    outputData << tripInfo.hotelAddress << endl;
    outputData << tripInfo.boarding << endl;
    outputData << tripInfo.maxReservations << endl;
    outputData << tripInfo.numReservations << endl;
    outputData << tripInfo.tripCost << endl;
    outputData << "----------------------------------------" << endl;
    //close
    outputData.close();
    cout << "Do you want to add another trip? Y|N: ";
    cin >> inChar;
    while (inChar[1] != temp)
    {
        cout << "You entered an incorrect choice!" << endl;
        cin >> inChar;
    }
    while (inChar[0] != 'y' && inChar[0] != 'Y' && inChar[0] != 'N' && inChar[0] != 'n')
    {
        cout << "You entered an incorrect choice!" << endl;
        cin >> inChar;
    }
    switch (inChar[0])
    {
    case 'y':
    case 'Y':
        addTrip();
        break;
    case 'n':
    case 'N':
        adminMenu();
        break;
    }
    NumberofTrips();
    adminMenu();
}
void updateTrip()
{
    char inChar2[50] = {};
    char temp2 = inChar2[0];
    system("clear");
    bool isContinue = false;
    cout << "User: Admin                    Action: Editing trip info..." << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << "--> Enter Trip ID: ";
    // ----------searching trip id in files----------
    string requestedID;
    cin >> requestedID;
    do
    {
        isContinue = false;
        for (int i = 0; i < requestedID.size(); i++)
        {
            if (requestedID[i] >= 48 && requestedID[i] <= 57)
            {
                continue;
            }
            else
            {
                isContinue = true;
                cout << "You entered an incorrect ID!" << endl;
                cout << "--> Enter Trip ID: ";
                cin >> requestedID;
                break;
            }
        }
    } while (isContinue);
    bool isFound = false;
    ifstream inputData;
    inputData.open("data/tripsInfo.txt");
    string line;
    while (getline(inputData, line))
    {
        if (line == requestedID)
        {
            isFound = true;
            break;
        }
        else
        {
            for (int i = 0; i < 11; i++)
            {
                getline(inputData, line);
            }
        }
    }
    if (isFound)
    {
        cout << "Your trip information: " << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
        cout << "* To Edit (Press Zero)   - Start Date: ";
        getline(inputData, line);
        cout << line << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
        cout << "* To Edit (Press One)    - End Date: ";
        getline(inputData, line);
        cout << line << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
        cout << "* To Edit (Press Two)    - Destination: ";
        getline(inputData, line);
        cout << line << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
        cout << "* To Edit (Press Three)  - Mean Of Transportation: ";
        getline(inputData, line);
        cout << line << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
        cout << "* To Edit (Press Four)  - Hotel Name: ";
        getline(inputData, line);
        cout << line << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
        cout << "* To Edit (Press Five)   - Hotel Address: ";
        getline(inputData, line);
        cout << line << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
        cout << "* To Edit (Press Six)    - Type of Boarding: ";
        getline(inputData, line);
        cout << line << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
        cout << "* To Edit (Press Seven)  - Max Number of Reservations: ";
        getline(inputData, line);
        cout << line << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
        cout << "* To Edit (Press Eight)  - Number of Resevations made: ";
        getline(inputData, line);
        cout << line << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
        cout << "* To Edit (Press Nine)   - Trip Cost: ";
        getline(inputData, line);
        cout << line << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
        cout << "--> The Answer: ";
    }
    else
    {
        while (true)
        {
            cout << "This trip is not found!" << endl;
            cout << "- Press One: Try Again" << endl;
            cout << "- Press Two: Go To Main Menu" << endl;
            cout << "--> The Answer: ";
            cin >> inChar2;
            while (inChar2[1] != temp2)
            {
                cout << "You entered an incorrect choice!" << endl;
                cout << "--> The Answer: ";
                cin >> inChar2;
            }
            while (!(inChar2[0] >= 49 && inChar2[0] <= 50))
            {
                cout << "You entered an incorrect choice!" << endl;
                cout << "--> The Answer: ";
                cin >> inChar2;
            }
            if (inChar2[0] == '1')
            {
                updateTrip();
                break;
            }
            else if (inChar2[0] == '2')
            {
                adminMenu();
                break;
            }
        }
    }
    inputData.close();
    // recieving the choice
    char inChar[50] = {};
    cin >> inChar;
    while (inChar[1] != '\0')
    {
        cout << "You entered an incorrect choice! " << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
    }
    while (!(inChar[0] >= 48 && inChar[0] <= 57))
    {
        cout << "You entered an incorrect choice! " << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
    }
    // Editing Data in Files
    inputData.open("data/tripsInfo.txt");
    ofstream outputData;
    outputData.open("data/temp.txt");
    string z;
    bool flag = false; // to detect if all the characters in string tripInfo.id are numbers
    switch (inChar[0])
    {
    case '0':
    {
        cout << "--> (Edit) Start Date: ";
        cin.ignore();
        getline(cin, tripInfo.startDate);
        string line; // contains the string in each line
        while (getline(inputData, line))
        {
            if (line == requestedID)
            {
                outputData << line << endl;
                getline(inputData, line);
                outputData << tripInfo.startDate << endl;
                continue;
            }
            outputData << line << endl;
        }
        inputData.close();
        outputData.close();
        remove("data/tripsInfo.txt");
        rename("data/temp.txt", "data/tripsInfo.txt");
        adminMenu();
        break;
    }
    case '1':
    {
        cout << "--> (Edit) End Date: ";
        cin.ignore();
        getline(cin, tripInfo.endDate);
        string line; // contains the string in each line
        while (getline(inputData, line))
        {
            if (line == requestedID)
            {
                outputData << line << endl;
                for (int i = 0; i < 1; i++)
                {
                    getline(inputData, line);
                    outputData << line << endl;
                }
                getline(inputData, line);
                outputData << tripInfo.endDate << endl;
                continue;
            }
            outputData << line << endl;
        }
        inputData.close();
        outputData.close();
        remove("data/tripsInfo.txt");
        rename("data/temp.txt", "data/tripsInfo.txt");
        adminMenu();
        break;
    }
    case '2':
    {
        cout << "--> (Edit) Destination: ";
        cin.ignore();
        getline(cin, tripInfo.destination);
        string line; // contains the string in each line
        while (getline(inputData, line))
        {
            if (line == requestedID)
            {
                outputData << line << endl;
                for (int i = 0; i < 2; i++)
                {
                    getline(inputData, line);
                    outputData << line << endl;
                }
                getline(inputData, line);
                outputData << tripInfo.destination << endl;
                continue;
            }
            outputData << line << endl;
        }
        inputData.close();
        outputData.close();
        remove("data/tripsInfo.txt");
        rename("data/temp.txt", "data/tripsInfo.txt");
        adminMenu();
        break;
    }
    case '3':
    {
        cout << "--> (Edit) Means of Transportation: ";
        cin.ignore();
        getline(cin, tripInfo.transportation);
        string line; // contains the string in each line
        while (getline(inputData, line))
        {
            if (line == requestedID)
            {
                outputData << line << endl;
                for (int i = 0; i < 3; i++)
                {
                    getline(inputData, line);
                    outputData << line << endl;
                }
                getline(inputData, line);
                outputData << tripInfo.transportation << endl;
                continue;
            }
            outputData << line << endl;
        }
        inputData.close();
        outputData.close();
        remove("data/tripsInfo.txt");
        rename("data/temp.txt", "data/tripsInfo.txt");
        adminMenu();
        break;
    }
    case '4':
    {
        cout << "--> (Edit) Hotel Name: ";
        cin.ignore();
        getline(cin, tripInfo.hotelName);
        string line; // contains the string in each line
        while (getline(inputData, line))
        {
            if (line == requestedID)
            {
                outputData << line << endl;
                for (int i = 0; i < 4; i++)
                {
                    getline(inputData, line);
                    outputData << line << endl;
                }
                getline(inputData, line);
                outputData << tripInfo.hotelName << endl;
                continue;
            }
            outputData << line << endl;
        }
        inputData.close();
        outputData.close();
        remove("data/tripsInfo.txt");
        rename("data/temp.txt", "data/tripsInfo.txt");
        adminMenu();
        break;
    }
    case '5':
    {
        cout << "--> (Edit) Hotel Address: ";
        cin.ignore();
        getline(cin, tripInfo.hotelAddress);
        string line; // contains the string in each line
        while (getline(inputData, line))
        {
            if (line == requestedID)
            {
                outputData << line << endl;
                for (int i = 0; i < 5; i++)
                {
                    getline(inputData, line);
                    outputData << line << endl;
                }
                getline(inputData, line);
                outputData << tripInfo.hotelAddress << endl;
                continue;
            }
            outputData << line << endl;
        }
        inputData.close();
        outputData.close();
        remove("data/tripsInfo.txt");
        rename("data/temp.txt", "data/tripsInfo.txt");
        adminMenu();
        break;
    }
    case '6':
    {
        cout << "--> (Edit) Type of Boarding: ";
        cin.ignore();
        getline(cin, tripInfo.boarding);
        string line; // contains the string in each line
        while (getline(inputData, line))
        {
            if (line == requestedID)
            {
                outputData << line << endl;
                for (int i = 0; i < 6; i++)
                {
                    getline(inputData, line);
                    outputData << line << endl;
                }
                getline(inputData, line);
                outputData << tripInfo.boarding << endl;
                continue;
            }
            outputData << line << endl;
        }
        inputData.close();
        outputData.close();
        remove("data/tripsInfo.txt");
        rename("data/temp.txt", "data/tripsInfo.txt");
        adminMenu();
        break;
    }
    case '7':
    {
        cout << "--> (Edit) Max Number of Reservations: ";
        cin.ignore();
        getline(cin, tripInfo.maxReservations);
        string line; // contains the string in each line
        while (getline(inputData, line))
        {
            if (line == requestedID)
            {
                outputData << line << endl;
                for (int i = 0; i < 7; i++)
                {
                    getline(inputData, line);
                    outputData << line << endl;
                }
                getline(inputData, line);
                outputData << tripInfo.maxReservations << endl;
                continue;
            }
            outputData << line << endl;
        }
        inputData.close();
        outputData.close();
        remove("data/tripsInfo.txt");
        rename("data/temp.txt", "data/tripsInfo.txt");
        adminMenu();
        break;
    }
    case '8':
    {
        cout << "--> (Edit) Number of Reservations Made: ";
        cin.ignore();
        getline(cin, tripInfo.numReservations);
        string line; // contains the string in each line
        while (getline(inputData, line))
        {
            if (line == requestedID)
            {
                outputData << line << endl;
                for (int i = 0; i < 8; i++)
                {
                    getline(inputData, line);
                    outputData << line << endl;
                }
                getline(inputData, line);
                outputData << tripInfo.numReservations << endl;
                continue;
            }
            outputData << line << endl;
        }
        inputData.close();
        outputData.close();
        remove("data/tripsInfo.txt");
        rename("data/temp.txt", "data/tripsInfo.txt");
        adminMenu();
        break;
    }
    case '9':
    {
        cout << "--> (Edit) Trip Cost: ";
        cin.ignore();
        getline(cin, tripInfo.tripCost);
        string line; // contains the string in each line
        while (getline(inputData, line))
        {
            if (line == requestedID)
            {
                outputData << line << endl;
                for (int i = 0; i < 9; i++)
                {
                    getline(inputData, line);
                    outputData << line << endl;
                }
                getline(inputData, line);
                outputData << tripInfo.tripCost << endl;
                continue;
            }
            outputData << line << endl;
        }
        inputData.close();
        outputData.close();
        remove("data/tripsInfo.txt");
        rename("data/temp.txt", "data/tripsInfo.txt");
        adminMenu();
        break;
    }
    }
}
void deleteTrip()
{
    // variables
    string line;
    int idLine;
    char inChar[50] = {};
    char temp = inChar[0];
    // booleans
    bool flag = false;
    bool isFound = false;
    system("clear");
    cout << "User: Admin                    Action: Deleting trip..." << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
    // Accepting ID from the user
    cout << "--> Enter Trip ID: ";
    cin >> tripInfo.id;
    // Checking if the ID contain any chars except numbers
    do
    {
        flag = false;
        for (int i = 0; i < tripInfo.id.size(); i++)
        {
            if (tripInfo.id[i] >= 48 && tripInfo.id[i] <= 57)
            {
                continue;
            }
            else
            {
                flag = true;
                cout << "You entered an incorrect ID!" << endl;
                cout << "--> Enter Trip ID: ";
                cin >> tripInfo.id;
                break;
            }
        }
    } while (flag);
    // Searching for the ID in the file
    ifstream inputData;
    ofstream outputData;
    inputData.open("data/tripsInfo.txt");
    outputData.open("data/temp.txt");
    for (int i = 1; i <= (NumberOfTrips * LinesEachTrip); i++) // I put i in 1 not in 0 to put the actual line number in variable "idLine"
    {
        getline(inputData, line);
        if (line == tripInfo.id)
        {
            idLine = i;
            isFound = true;
            break;
        }
    }
    inputData.close(); // Here I closed it so getline can start from beginning
    inputData.open("data/tripsInfo.txt");
    if (isFound)
    {
        for (int i = 1; i <= (NumberOfTrips * LinesEachTrip); i++)
        {
            getline(inputData, line);
            if (i >= idLine && i <= idLine + 11)
            {
                continue;
            }
            outputData << line << endl;
        }
        inputData.close();
        outputData.close();
        remove("data/tripsInfo.txt");
        rename("data/temp.txt", "data/tripsInfo.txt");
        adminMenu();
    }
    else
    {
        while (true)
        {
            cout << "Trip is not found!" << endl;
            cout << "- Press One: Try Again\n";
            cout << "- Press Two: Go To Main Menu\n";
            cout << "--> The Answer: ";
            cin >> inChar;
            while (inChar[1] != temp)
            {
                cout << "You entered an incorrect choice!" << endl;
                cout << "--> The Answer: ";
                cin >> inChar;
            }
            while (inChar[0] != '1' && inChar[0] != '2')
            {
                cout << "You entered an incorrect choice!" << endl;
                cout << "--> The Answer: ";
                cin >> inChar;
            }
            if (inChar[0] == '1')
            {
                deleteTrip();
                break;
            }
            else if (inChar[0] == '2')
            {
                adminMenu();
                break;
            }
        }
    }
}
void showReservs()
{
    // variables
    int NumberOfReservs = 0;
    string line;
    char inChar[25] = {};
    // booleans
    bool doContinue = false;
    bool flag = true; // used to check if the trip id is all numbers and no letters
    bool tripFound = false;
    bool reservFound = false;
    bool isEmpty = true;
    ifstream inputData;
    system("clear");
    cout << "User: Admin                    Action: Showing reservations..." << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << "- Press One: Show all reservations" << endl;
    cout << "- Press Two: Show reservations of a certain trip" << endl;
    cout << "--> The Answer: ";
    cin >> inChar;
    while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
    {
        cout << "You entered an incorrect choice!" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
    }
    switch (inChar[0])
    {
    case '1':
    {
        // Show all reservations
        inputData.open("data/reservsInfo.txt");
        do
        {
            if (doContinue == true && NumberOfReservs != 10)
            {

                cout << "NO MORE RESERVATIONS!" << endl;
                cout << "- Press One: Return to main menu" << endl;
                cout << "--> The Answer: ";
                cin >> inChar;
                while (inChar[1] != '\0' || inChar[0] != '1')
                {
                    cout << "You entered an incorrect choice!" << endl;
                    cout << "--> The Answer: ";
                    cin >> inChar;
                }
                if (inChar[0] == '1')
                {
                    inputData.close();
                    adminMenu();
                    break;
                }
            }
            NumberOfReservs = 0;
            system("clear");
            cout << "User: Admin                    Action: Showing reservations..." << endl;
            cout << "------------------------------------------------------------------------------------" << endl;
            while (getline(inputData, line))
            {
                isEmpty = false;
                NumberOfReservs++;
                cout << endl;
                cout << "Reservation Number: " << line << endl;
                cout << "-------------------------------------------------" << endl;
                getline(inputData, line);
                cout << "Username: " << line << endl;
                cout << "-------------------------------------------------" << endl;
                getline(inputData, line);
                cout << "Destination: " << line << endl;
                cout << "-------------------------------------------------" << endl;
                getline(inputData, line);
                cout << "Number Of Tickets: " << line << endl;
                cout << "-------------------------------------------------" << endl;
                getline(inputData, line);
                cout << "Means of Tranportation: " << line << endl;
                cout << "-------------------------------------------------" << endl;
                getline(inputData, line);
                cout << "Start Date: " << line << endl;
                cout << "-------------------------------------------------" << endl;
                getline(inputData, line);
                cout << "End Date: " << line << endl;
                cout << "-------------------------------------------------" << endl;
                getline(inputData, line);
                cout << "Hotel Name: " << line << endl;
                cout << "-------------------------------------------------" << endl;
                getline(inputData, line);
                cout << "Hotel Address: " << line << endl;
                cout << "-------------------------------------------------" << endl;
                getline(inputData, line);
                cout << "Type of Boarding: " << line << endl;
                cout << "-------------------------------------------------" << endl;
                getline(inputData, line);
                cout << "Trip Cost: " << line << "$" << endl;
                cout << "-------------------------------------------------" << endl;
                getline(inputData, line);
                if (NumberOfReservs == 10)
                {

                    cout << "- Press One: Go to the next page" << endl;
                    cout << "- Press Two: Return to main menu" << endl;
                    cout << "--> The Answer: ";
                    cin >> inChar;
                    while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
                    {
                        cout << "You entered an incorrect choice!" << endl;
                        cout << "--> The Answer: ";
                        cin >> inChar;
                    }
                    switch (inChar[0])
                    {
                    case '1':
                        doContinue = true;
                        break;
                    case '2':
                        adminMenu();
                        doContinue = false;
                        break;
                    }
                    break;
                }
            }
        } while (doContinue);
        if (isEmpty)
        {
            cout << "NO RESERVATIONS FOUND!" << endl;
            cout << "- Press One: Return to main menu" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
            while (inChar[1] != '\0' && inChar[0] != '1')
            {
                cout << "You entered an incorrect choice!" << endl;
                cout << "--> The Answer: ";
                cin >> inChar;
            }
            if (inChar[0] == '1')
            {
                adminMenu();
            }
        }
        inputData.close();
        break;
    }
    case '2':
    {
        system("clear");
        cout << "User: Admin                    Action: Showing reservations..." << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
        cout << "--> Enter Trip ID: ";
        cin >> tripInfo.id;
        // check if all letters are numbers
        while (true)
        {
            flag = true;
            for (int i = 0; i < tripInfo.id.size(); i++)
            {
                if (!(tripInfo.id[i] >= 48 && tripInfo.id[i] <= 57))
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                break;
            }
            else
            {
                // so the user entered some letters
                system("clear");
                cout << "User: Admin                    Action: Showing reservations..." << endl;
                cout << "------------------------------------------------------------------------------------" << endl;
                cout << "Please enter a correct ID!" << endl;
                cout << "--> Enter Trip ID: ";
                cin >> tripInfo.id;
            }
        }
        // check if the trip is found
        inputData.open("data/tripsInfo.txt");
        while (getline(inputData, line))
        {
            if (tripInfo.id == line)
            {
                tripFound = true;
                getline(inputData, line);
                tripInfo.startDate = line;
                getline(inputData, line);
                tripInfo.endDate = line;
                getline(inputData, line);
                tripInfo.destination = line;
                getline(inputData, line);
                tripInfo.transportation = line;
                getline(inputData, line);
                tripInfo.hotelName = line;
                getline(inputData, line);
                tripInfo.hotelAddress = line;
                getline(inputData, line);
                tripInfo.boarding = line;
                getline(inputData, line);
                getline(inputData, line);
                getline(inputData, line);
                tripInfo.tripCost = line;
                break;
            }
            else
            {
                for (int i = 0; i < 11; i++)
                {
                    getline(inputData, line); // to skip the next 11 lines to go for the next id only
                }
            }
        }
        inputData.close();
        if (tripFound)
        {
            inputData.open("data/reservsInfo.txt");
            while (getline(inputData, line))
            {
                reservationInfo.reservNum = line;
                getline(inputData, line);
                reservationInfo.clientUsername = line;
                getline(inputData, line);
                if (line == tripInfo.destination)
                {
                    getline(inputData, line); // to skip destination
                    reservationInfo.numPeople = line;
                    getline(inputData, line); // to skip # of tickets
                    if (line == tripInfo.transportation)
                    {
                        getline(inputData, line);
                        if (line == tripInfo.startDate)
                        {
                            getline(inputData, line);
                            if (line == tripInfo.endDate)
                            {
                                getline(inputData, line);
                                if (line == tripInfo.hotelName)
                                {
                                    getline(inputData, line);
                                    if (line == tripInfo.hotelAddress)
                                    {
                                        getline(inputData, line);
                                        if (line == tripInfo.boarding)
                                        {
                                            getline(inputData, line);
                                            if (line == tripInfo.tripCost)
                                            {
                                                reservFound = true;
                                                // show the reservation
                                                NumberOfReservs++;
                                                cout << endl;
                                                cout << "Reservation Number: " << reservationInfo.reservNum << endl;
                                                cout << "-------------------------------------------------" << endl;
                                                cout << "Username: " << reservationInfo.clientUsername << endl;
                                                cout << "-------------------------------------------------" << endl;
                                                cout << "Destination: " << tripInfo.destination << endl;
                                                cout << "-------------------------------------------------" << endl;
                                                cout << "Number Of Tickets: " << reservationInfo.numPeople << endl;
                                                cout << "-------------------------------------------------" << endl;
                                                cout << "Means of Tranportation: " << tripInfo.transportation << endl;
                                                cout << "-------------------------------------------------" << endl;
                                                cout << "Start Date: " << tripInfo.startDate << endl;
                                                cout << "-------------------------------------------------" << endl;
                                                cout << "End Date: " << tripInfo.endDate << endl;
                                                cout << "-------------------------------------------------" << endl;
                                                cout << "Hotel Name: " << tripInfo.hotelName << endl;
                                                cout << "-------------------------------------------------" << endl;
                                                cout << "Hotel Address: " << tripInfo.hotelAddress << endl;
                                                cout << "-------------------------------------------------" << endl;
                                                cout << "Type of Boarding: " << tripInfo.boarding << endl;
                                                cout << "-------------------------------------------------" << endl;
                                                cout << "Trip Cost: " << line << "$" << endl;
                                                cout << "-------------------------------------------------" << endl;
                                                getline(inputData, line);
                                                if (NumberOfReservs == 10)
                                                {

                                                    cout << "- Press One: Go to the next page" << endl;
                                                    cout << "- Press Two: Return to main menu" << endl;
                                                    cout << "--> The Answer: ";
                                                    cin >> inChar;
                                                    while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
                                                    {
                                                        cout << "You entered an incorrect choice!" << endl;
                                                        cout << "--> The Answer: ";
                                                        cin >> inChar;
                                                    }
                                                    switch (inChar[0])
                                                    {
                                                    case '1':
                                                        doContinue = true;
                                                        NumberOfReservs = 0;
                                                        system("clear");
                                                        cout << "User: Admin                    Action: Showing reservations..." << endl;
                                                        cout << "------------------------------------------------------------------------------------" << endl;
                                                        break;
                                                    case '2':
                                                        adminMenu();
                                                        doContinue = false;
                                                        break;
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                getline(inputData, line);
                                            }
                                        }
                                        else
                                        {
                                            for (int i = 0; i < 2; i++)
                                            {
                                                getline(inputData, line);
                                            }
                                        }
                                    }
                                    else
                                    {
                                        for (int i = 0; i < 3; i++)
                                        {
                                            getline(inputData, line);
                                        }
                                    }
                                }
                                else
                                {
                                    for (int i = 0; i < 4; i++)
                                    {
                                        getline(inputData, line);
                                    }
                                }
                            }
                            else
                            {
                                for (int i = 0; i < 5; i++)
                                {
                                    getline(inputData, line);
                                }
                            }
                        }
                        else
                        {
                            for (int i = 0; i < 6; i++)
                            {
                                getline(inputData, line);
                            }
                        }
                    }
                    else
                    {
                        for (int i = 0; i < 7; i++)
                        {
                            getline(inputData, line);
                        }
                    }
                }
                else
                {
                    for (int i = 0; i < 9; i++) // here 9 because we skipped the number of tickets so its not 8
                    {
                        getline(inputData, line);
                    }
                }
            }
            if (!reservFound)
            {
                cout << "NO RESERVATIONS FOR THIS TRIP!" << endl;
                cout << "- Press One: Try again" << endl;
                cout << "- Press Two: Return to main menu" << endl;
                cout << "--> The Answer: ";
                cin >> inChar;
                while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
                {
                    cout << "You entered an incorrect choice!" << endl;
                    cout << "--> The Answer: ";
                    cin >> inChar;
                }
                switch (inChar[0])
                {
                case '1':
                {
                    showReservs();
                    break;
                }
                case '2':
                    adminMenu();
                    break;
                }
            }
            cout << "NO MORE RESERVATIONS!" << endl;
            cout << "- Press One: Return to main menu" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
            while (inChar[1] != '\0' || inChar[0] != '1')
            {
                cout << "You entered an incorrect choice!" << endl;
                cout << "--> The Answer: ";
                cin >> inChar;
            }
            if (inChar[0] == '1')
            {
                inputData.close();
                adminMenu();
                break;
            }
            inputData.close();
        }
        else
        {
            cout << "NO RESERVATIONS FOR THIS TRIP!" << endl;
            cout << "- Press One: Try again" << endl;
            cout << "- Press Two: Return to main menu" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
            while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
            {
                cout << "You entered an incorrect choice!" << endl;
                cout << "--> The Answer: ";
                cin >> inChar;
            }
            switch (inChar[0])
            {
            case '1':
            {
                showReservs();
                break;
            }
            case '2':
                adminMenu();
                break;
            }
        }
        break;
    }
    }
}
void showUsers()
{
    // variables
    string line;
    char inChar[25] = {};
    int numberofusers = 0;
    // booleans
    bool flag = false;
    bool tripFound = false;
    bool reservFound = false;
    // file streams
    ifstream inputData;
    system("clear");
    cout << "User: Admin                    Action: Showing users..." << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << "- Press One: Show all users" << endl;
    cout << "- Press Two: Show users with certain reservations" << endl;
    cout << "--> The Answer: ";
    cin >> inChar;
    while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
    {
        cout << "You entered an incorrect choice!" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
    }
    switch (inChar[0])
    {
    case '1':
    {
        system("clear");
        cout << "User: Admin                    Action: Showing users..." << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
        inputData.open("data/usersInfo.txt");
        while (getline(inputData, line))
        {
            cout << "User ID: " << line;
            getline(inputData, line);
            cout << "        Username: " << line << endl;
            cout << "-------------------------------------------------" << endl;
            for (int i = 0; i < 8; i++)
            {
                getline(inputData, line);
            }
            numberofusers++;
            if (numberofusers == 10)
            {
                cout << "- Press One: Go to the next page" << endl;
                cout << "- Press Two: Return to main menu" << endl;
                cout << "--> The Answer: ";
                cin >> inChar;
                while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
                {
                    cout << "You entered an incorrect choice!" << endl;
                    cout << "--> The Answer: ";
                    cin >> inChar;
                }
                switch (inChar[0])
                {
                case '1':
                    numberofusers = 0;
                    system("clear");
                    cout << "User: Admin                    Action: Showing users..." << endl;
                    cout << "------------------------------------------------------------------------------------" << endl;
                    break;
                case '2':
                    adminMenu();
                    break;
                }
            }
        }
        if (numberofusers < 10)
        {
            cout << "NO MORE USERS!" << endl;
            cout << "- Press One: Return to the main menu" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
            while (inChar[1] != '\0' || inChar[0] != '1')
            {
                cout << "You entered an incorrect choice!" << endl;
                cout << "--> The Answer: ";
                cin >> inChar;
            }
            if (inChar[0] == '1')
            {
                adminMenu();
            }
        }
        inputData.close();
        break;
    }
    case '2':
    {
        system("clear");
        cout << "User: Admin                    Action: Showing users..." << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
        cout << "--> Enter Trip ID: ";
        cin >> tripInfo.id;
        // check if all letters are numbers
        while (true)
        {
            flag = true;
            for (int i = 0; i < tripInfo.id.size(); i++)
            {
                if (!(tripInfo.id[i] >= 48 && tripInfo.id[i] <= 57))
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                break;
            }
            else
            {
                // so the user entered some letters
                system("clear");
                cout << "User: Admin                    Action: Showing users..." << endl;
                cout << "------------------------------------------------------------------------------------" << endl;
                cout << "Please enter a correct ID!" << endl;
                cout << "--> Enter Trip ID: ";
                cin >> tripInfo.id;
            }
        }
        // check if the trip is found
        inputData.open("data/tripsInfo.txt");
        while (getline(inputData, line))
        {
            if (tripInfo.id == line)
            {
                tripFound = true;
                getline(inputData, line);
                tripInfo.startDate = line;
                getline(inputData, line);
                tripInfo.endDate = line;
                getline(inputData, line);
                tripInfo.destination = line;
                getline(inputData, line);
                tripInfo.transportation = line;
                getline(inputData, line);
                tripInfo.hotelName = line;
                getline(inputData, line);
                tripInfo.hotelAddress = line;
                getline(inputData, line);
                tripInfo.boarding = line;
                getline(inputData, line);
                getline(inputData, line);
                getline(inputData, line);
                tripInfo.tripCost = line;
                break;
            }
            else
            {
                for (int i = 0; i < 11; i++)
                {
                    getline(inputData, line); // to skip the next 11 lines to go for the next id only
                }
            }
        }
        inputData.close();
        if (tripFound)
        {
            inputData.open("data/reservsInfo.txt");
            while (getline(inputData, line))
            {
                reservationInfo.reservNum = line;
                getline(inputData, line);
                reservationInfo.clientUsername = line;
                getline(inputData, line);
                if (line == tripInfo.destination)
                {
                    getline(inputData, line); // to skip destination
                    reservationInfo.numPeople = line;
                    getline(inputData, line); // to skip # of tickets
                    if (line == tripInfo.transportation)
                    {
                        getline(inputData, line);
                        if (line == tripInfo.startDate)
                        {
                            getline(inputData, line);
                            if (line == tripInfo.endDate)
                            {
                                getline(inputData, line);
                                if (line == tripInfo.hotelName)
                                {
                                    getline(inputData, line);
                                    if (line == tripInfo.hotelAddress)
                                    {
                                        getline(inputData, line);
                                        if (line == tripInfo.boarding)
                                        {
                                            getline(inputData, line);
                                            if (line == tripInfo.tripCost)
                                            {
                                                reservFound = true;
                                                // show the reservation
                                                numberofusers++;
                                                cout << "- Username:    " << reservationInfo.clientUsername << endl;
                                                cout << "---------------------------------------" << endl;
                                                getline(inputData, line);
                                                if (numberofusers == 10)
                                                {

                                                    cout << "- Press One: Go to the next page" << endl;
                                                    cout << "- Press Two: Return to main menu" << endl;
                                                    cout << "--> The Answer: ";
                                                    cin >> inChar;
                                                    while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
                                                    {
                                                        cout << "You entered an incorrect choice!" << endl;
                                                        cout << "--> The Answer: ";
                                                        cin >> inChar;
                                                    }
                                                    switch (inChar[0])
                                                    {
                                                    case '1':
                                                        numberofusers = 0;
                                                        system("clear");
                                                        cout << "User: Admin                    Action: Showing users..." << endl;
                                                        cout << "------------------------------------------------------------------------------------" << endl;
                                                        break;
                                                    case '2':
                                                        adminMenu();
                                                        break;
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                getline(inputData, line);
                                            }
                                        }
                                        else
                                        {
                                            for (int i = 0; i < 2; i++)
                                            {
                                                getline(inputData, line);
                                            }
                                        }
                                    }
                                    else
                                    {
                                        for (int i = 0; i < 3; i++)
                                        {
                                            getline(inputData, line);
                                        }
                                    }
                                }
                                else
                                {
                                    for (int i = 0; i < 4; i++)
                                    {
                                        getline(inputData, line);
                                    }
                                }
                            }
                            else
                            {
                                for (int i = 0; i < 5; i++)
                                {
                                    getline(inputData, line);
                                }
                            }
                        }
                        else
                        {
                            for (int i = 0; i < 6; i++)
                            {
                                getline(inputData, line);
                            }
                        }
                    }
                    else
                    {
                        for (int i = 0; i < 7; i++)
                        {
                            getline(inputData, line);
                        }
                    }
                }
                else
                {
                    for (int i = 0; i < 9; i++) // here 9 because we skipped the number of tickets so its not 8
                    {
                        getline(inputData, line);
                    }
                }
            }
            if (!reservFound)
            {
                cout << "NO USERS FOUND!" << endl;
                cout << "- Press One: Try again" << endl;
                cout << "- Press Two: Return to main menu" << endl;
                cout << "--> The Answer: ";
                cin >> inChar;
                while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
                {
                    cout << "You entered an incorrect choice!" << endl;
                    cout << "--> The Answer: ";
                    cin >> inChar;
                }
                switch (inChar[0])
                {
                case '1':
                {
                    showUsers();
                    break;
                }
                case '2':
                    adminMenu();
                    break;
                }
            }
            cout << "NO MORE USERS!" << endl;
            cout << "- Press One: Return to main menu" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
            while (inChar[1] != '\0' || inChar[0] != '1')
            {
                cout << "You entered an incorrect choice!" << endl;
                cout << "--> The Answer: ";
                cin >> inChar;
            }
            if (inChar[0] == '1')
            {
                inputData.close();
                adminMenu();
                break;
            }
            inputData.close();
        }
        else
        {
            cout << "NO USERS RESERVED THIS TRIP!" << endl;
            cout << "- Press One: Try again" << endl;
            cout << "- Press Two: Return to main menu" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
            while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
            {
                cout << "You entered an incorrect choice!" << endl;
                cout << "--> The Answer: ";
                cin >> inChar;
            }
            switch (inChar[0])
            {
            case '1':
            {
                showUsers();
                break;
            }
            case '2':
                adminMenu();
                break;
            }
        }
        break;
    }
    }
}
void confRequests()
{
    // booleans
    bool isfileEmpty = true;
    bool flag = false; // check if the username is found
    // variables
    string line;
    string username; // to store in it the username of the client that currently needs confirmation
    int walletFileLines = 0;
    int totalbalance;
    string walletbalance;
    char inChar[25] = {};
    char inChar2[25] = {};
    int tempcnt = 0;
    ifstream inputData;
    ofstream outputData;
    inputData.open("data/walletInfo.txt");
    while (getline(inputData, line))
    {
        isfileEmpty = false;
        walletFileLines++;
    }
    inputData.close();
    system("clear");
    cout << "User: Admin             Action: Confirming Requests...          Number of Requests: "
         << (walletFileLines / LinesEachWallet) << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    if ((walletFileLines / LinesEachWallet) == 0)
    {
        cout << "NO REQUESTS YET!" << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "- Press One: Return to the main menu" << endl;
        cout << "--> The Answer: ";
        cin >> inChar2;
        while (inChar2[1] != '\0' && inChar2[0] != '1')
        {
            cout << "You entered an incorrect choice!" << endl;
            cout << "The Answer: ";
            cin >> inChar2;
        }
        if (inChar2[0] == '1')
        {
            adminMenu();
        }
    }
    // body
    for (int i = 0; i < (walletFileLines / LinesEachWallet); i++)
    {
        if (!inputData.is_open())
        {
            inputData.open("data/walletInfo.txt"); // open again to start from line 1
        }
        getline(inputData, line); // now line contains the username;
        cout << "Client Username: " << line << endl;
        username = line;
        cout << "-------------------------------------------------" << endl;
        getline(inputData, line); // now line contains the deposit value
        cout << "Deposit Value: " << line << "$" << endl;
        walletbalance = line;
        cout << "-------------------------------------------------" << endl;
        getline(inputData, line); // now line contains the payment status
        cout << "Status: " << line << endl;
        cout << "-------------------------------------------------" << endl;
        getline(inputData, line); // now line contains the dashes and we will not use it;
        cout << "- Press One:   Confirm the payment" << endl;
        cout << "- Press Two:   Skip this client" << endl;
        cout << "- Press Three: Return to the main menu" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
        while (!(inChar[1] == '\0' && (inChar[0] >= 49 || inChar[0] <= 51)))
        {
            cout << "You entered an incorrect choice!" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
        }
        if (inChar[0] == '1')
        {
            inputData.close();
            // 3awz hna ams7 el data bta3t eluser ely et3mlo confirmation mn walletInfo file
            inputData.open("data/walletInfo.txt"); // open again to start from line 1
            outputData.open("data/temp.txt");
            while (getline(inputData, line))
            {
                if (line == username)
                {
                    getline(inputData, line);
                    getline(inputData, line);
                    getline(inputData, line);
                    continue;
                }
                outputData << line << endl;
            }
            outputData.close();
            inputData.close();
            remove("data/walletInfo.txt");
            rename("data/temp.txt", "data/walletInfo.txt");
            // hna b2a hn2l elwallet balance men el walletinfo lel userInfo 34an a3ml confirm
            inputData.open("data/usersInfo.txt");
            outputData.open("data/temp.txt");
            while (getline(inputData, line))
            {
                if (username == line)
                {
                    flag = true;
                    tempcnt = 0;
                }
                if (tempcnt == 7 && flag == true)
                {
                    totalbalance = stoi(walletbalance) + stoi(line); // wallet balance hya el deposit value (requested) + line hwa elvalue ely f3ln fel wallet
                    outputData << totalbalance << endl;
                    tempcnt++; // bazwd hna bdl t7t elmrady bs 34an hwa hy3ml continue we m4 hykml
                    continue;
                }
                tempcnt++;
                outputData << line << endl;
            }
            inputData.close();
            outputData.close();
            remove("data/usersInfo.txt");
            rename("data/temp.txt", "data/usersInfo.txt");
            confRequests(); // hy3eed hna mn el2wl b3d amaa ykoon ms77
        }
        else if (inChar[0] == '2')
        {
            if (i == (walletFileLines / LinesEachWallet) - 1) // check if this is the last name and the user choosed to skip
            {
                cout << "NO MORE REQUESTS!" << endl;
                cout << "-------------------------------------------------" << endl;
                cout << "- Press One: Return to the main menu" << endl;
                cout << "--> The Answer: ";
                cin >> inChar2;
                while (inChar2[1] != '\0' && inChar2[0] != '1')
                {
                    cout << "You entered an incorrect choice!" << endl;
                    cout << "The Answer: ";
                    cin >> inChar2;
                }
                if (inChar2[0] == '1')
                {
                    inputData.close();
                    outputData.close();
                    remove("data/temp.txt");
                    adminMenu();
                    break;
                }
            }
            system("clear");
            cout << "User: Admin             Action: Confirming Requests...          Number of Requests: "
                 << (walletFileLines / LinesEachWallet) << endl;
            cout << "-----------------------------------------------------------------------------------------" << endl;
            continue;
        }
        else if (inChar[0] == '3')
        {
            system("clear");
            adminMenu();
            break;
        }
    }
    remove("data/temp.txt");
}
void adLogout()
{
    AdUser = " "; // reset the admin username
    AdPass = " "; // reset the admin password
    system("clear");
    roleInput();
}
// ----------Client---------
void clientMenu()
{
    system("clear");
    cout << "User: Client";
    cout << "                                                           **Client Menu**" << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
    char LorR[100];
    if (isClient)
    {
        cout << "* Login ( Press One )" << endl;
        cout << "* Register (Press Two )" << endl;
        cout << "The Answer: ";
        cin >> LorR;
        while ((LorR[0] != '1') && (LorR[0] != '2'))
        {
            cout << "You entered an incorrect choice. Please enter a correct choice: ";
            cin >> LorR;
        }
        switch (LorR[0])
        {
        case '1':
            isLogin = true;
            isRegister = false;
            clientLogin();
            break;
        case '2':
            isRegister = true;
            isLogin = false;
            clientRegister();
            break;
        }
    }
}
void clientLogin()
{
    cout << "--> Enter Username: ";
    cin.ignore();
    getline(cin, ClUser);
    cout << "--> Enter Password: ";
    getline(cin, ClPass);
    while (!L_ValUser())
    {
        cout << "Either the username or the password or both are incorrect!" << endl;
        cout << "--> Enter Username: ";
        //cin.ignore();
        getline(cin, ClUser);
        cout << "--> Enter Password: ";
        getline(cin, ClPass);
    }
    userReg.username = ClUser;
    while (!L_ValPass() || !L_ValUser())
    {
        cout << "Either the username or the password or both are incorrect!" << endl;
        cout << "--> Enter Username: ";
        getline(cin, ClUser);
        cout << "--> Enter Password: ";
        getline(cin, ClPass);
    }
    ClLogConf = true;
    // put client data in the struct (userReg)
    ifstream inputData;
    inputData.open("data/usersInfo.txt");
    string line;
    bool flag = false;
    cout << ClUser << endl;
    while (getline(inputData, line))
    {
        if (line == ClUser)
        {
            flag = true;
            break;
        }
    }
    if (flag)
    {
        userReg.username = line;
        getline(inputData, line);
        userReg.firstname = line;
        getline(inputData, line);
        userReg.lastname = line;
        getline(inputData, line);
        userReg.email = line;
        getline(inputData, line);
        userReg.phonenumber = line;
        getline(inputData, line);
        userReg.address = line;
        getline(inputData, line);
        userReg.password1 = line;
        getline(inputData, line);
        userReg.wallet = line;
    }
    inputData.close();
    clientMenu2();
}
void clientRegister()
{
    // ---------------Username---------------
    system("clear");
    cout << "User: Client";
    cout << "                                                           **Register Form**" << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << "--> Enter Username: ";
    cin.ignore();
    getline(cin, userReg.username);
    while (!R_Username_Unique())
    {
        cout << "This username is not available!" << endl;
        cout << "--> Enter Username: ";
        getline(cin, userReg.username);
    }
    // ---------------Names---------------
    cout << "--> Enter First Name: ";
    cin >> userReg.firstname;
    cout << "--> Enter Last Name: ";
    cin >> userReg.lastname;
    // ---------------Phone Number---------------
    cout << "--> Enter Phone Number: ";
    cin >> userReg.phonenumber;
    while (!R_Phone_CFormat(userReg.phonenumber))
    {
        cout << "Please enter your real phone number!" << endl;
        cout << "--> Enter Phone Number: ";
        cin >> userReg.phonenumber;
    }
    // ---------------Email---------------
    cout << "--> Enter Email: ";
    cin >> userReg.email;
    while (!R_Email_CFormat(userReg.email))
    {
        cout << "Please enter your real email!" << endl;
        cout << "--> Enter Email: ";
        cin >> userReg.email;
    }
    // ---------------Address---------------
    cout << "--> Enter Address: ";
    cin.ignore();
    getline(cin, userReg.address);
    // ---------------Password---------------
    cout << "--> Enter Password: ";
    getline(cin, userReg.password1);
    cout << "--> Confirm Password: ";
    getline(cin, userReg.password2);
    while (!R_Pass_Conf())
    {
        cout << "The two passwords are not the same!" << endl;
        cout << "--> Enter Password: ";
        getline(cin, userReg.password1);
        cout << "--> Confirm Password: ";
        getline(cin, userReg.password2);
    }
    userReg.wallet = "0";
    SaveClientInfo();
}
void SaveClientInfo()
{
    int id;
    if ((FileLines / LinesEachUser) == 0)
    {
        id = 1;
    }
    else
    {
        id = (FileLines / LinesEachUser) + 1;
    }
    ofstream outputData;
    outputData.open("data/usersInfo.txt", ios::app);
    outputData << id << endl;
    outputData << userReg.username << endl;
    outputData << userReg.firstname << endl;
    outputData << userReg.lastname << endl;
    outputData << userReg.email << endl;
    outputData << userReg.phonenumber << endl;
    outputData << userReg.address << endl;
    outputData << userReg.password1 << endl;
    outputData << userReg.wallet << endl;
    outputData << "-----------------------------" << endl;
    outputData.close();
    NumberOfUsers();
}
void clientMenu2()
{
    // variables
    char inChar[25] = {};
    char temp = inChar[0];
    // booleans
    system("clear");
    cout << "User: Client";
    cout << "                                                           **Client Menu**" << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << "* Reserve a Trip                           (Press One)" << endl;
    cout << "* Change a Reservation                     (Press Two)" << endl;
    cout << "* Show the History of Reservations         (Press Three)" << endl;
    cout << "* Show All Open Reservations               (Press Four)" << endl;
    cout << "* Cancel Reservation                       (Press Five)" << endl;
    cout << "* Make a Deposit                           (Press Six)" << endl;
    cout << "* Edit Your Personal Account Information   (Press Seven)" << endl;
    cout << "* Logout                                   (Press Eight)" << endl;
    cout << "--> Your Answer: ";
    cin >> inChar;
    // check if the input is only one char && the input is from 1 --> 8
    while (!(inChar[1] == temp && inChar[0] >= 49 && inChar[0] <= 56))
    {
        cout << "You entered an incorrect choice!" << endl;
        cout << "--> Your Answer: ";
        cin >> inChar;
    }
    switch (inChar[0])
    {
    case '1':
        reserveTrip();
        break;
    case '2':
        changeReserv();
        break;
    case '3':
        HistReserv();
        break;
    case '4':
        openReserv();
        break;
    case '5':
        cancelReserv();
        break;
    case '6':
        putWallet();
        break;
    case '7':
        editAccInfo();
        break;
    case '8':
        clLogout();
        break;
    }
}
void reserveTrip()
{
    ifstream inputData;
    ofstream outputData;
    // variables
    string line;
    int idLine;
    char inChar[25] = {};
    char inChar2[25] = {};
    char inChar3[25] = {};
    int tmpcnt = 0; // count lines between username and the wallet balance
    // booleans
    bool doPrint = false;
    bool flag = false;  // check if the username is found or not
    bool flag2 = false; // check if all chars are numbers
    bool isFound = false;
    refreshWallet(); // to make sure that it contain the actual value in the file bec something went wrong before
    system("clear");
    cout << "User: Client            Action: Reserving a Trip...         Current balance: " << userReg.wallet << "$" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "--> Enter Trip ID: ";
    cin >> tripInfo.id;
    // check if all chars are numbers
    do
    {
        flag2 = false;
        for (int i = 0; i < tripInfo.id.size(); i++)
        {
            if (tripInfo.id[i] < 48 || tripInfo.id[i] > 57)
            {
                flag2 = true;
                cout << "Please enter a correct ID!" << endl;
                cout << "--> Enter Trip ID: ";
                cin >> tripInfo.id;
                i = 0;
            }
        }
    } while (flag2);
    // check if the trip is found or not
    inputData.open("data/tripsInfo.txt");
    while (getline(inputData, line))
    {
        if (line == tripInfo.id)
        {
            isFound = true;
            break;
        }
        for (int i = 1; i <= 11; i++)
        {
            getline(inputData, line);
        }
    }
    inputData.close();
    if (!isFound)
    {
        cout << "Trip is not found!" << endl;
        cout << "- Press One: Try again" << endl;
        cout << "- Press Two: Return back to main menu" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
        while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
        {
            cout << "You entered an incorrect choice!" << endl;
            cout << "The Answer: ";
            cin >> inChar;
        }
        switch (inChar[0])
        {
        case '1':
            reserveTrip();
            break;
        case '2':
            clientMenu2();
            break;
        }
    }
    cout << "Trip Information: " << endl;
    cout << "-----------------------------------------------------------" << endl;
    inputData.open("data/tripsInfo.txt");
    for (int i = 1; i <= (NumberOfTrips * LinesEachTrip); i++)
    {
        if (doPrint)
        {
            if (i == idLine + 1)
            {
                tripInfo.id = line;
                cout << "Trip ID: " << line << endl;
                cout << "-----------------------------------------------------------" << endl;
            }
            else if (i == idLine + 2)
            {
                tripInfo.startDate = line;
                cout << "Start Date: " << line << endl;
                cout << "-----------------------------------------------------------" << endl;
            }
            else if (i == idLine + 3)
            {
                tripInfo.endDate = line;
                cout << "End Date: " << line << endl;
                cout << "-----------------------------------------------------------" << endl;
            }
            else if (i == idLine + 4)
            {
                tripInfo.destination = line;
                cout << "Destination: " << line << endl;
                cout << "-----------------------------------------------------------" << endl;
            }
            else if (i == idLine + 5)
            {
                tripInfo.transportation = line;
                cout << "Means of Tranportation: " << line << endl;
                cout << "-----------------------------------------------------------" << endl;
            }
            else if (i == idLine + 6)
            {
                tripInfo.hotelName = line;
                cout << "Hotel Name: " << line << endl;
                cout << "-----------------------------------------------------------" << endl;
            }
            else if (i == idLine + 7)
            {
                tripInfo.hotelAddress = line;
                cout << "Hotel Address: " << line << endl;
                cout << "-----------------------------------------------------------" << endl;
            }
            else if (i == idLine + 8)
            {
                tripInfo.boarding = line;
                cout << "Type of Boarding: " << line << endl;
                cout << "-----------------------------------------------------------" << endl;
            }
            else if (i == idLine + 9)
            {
                tripInfo.maxReservations = line;
            }
            else if (i == idLine + 10)
            {
                tripInfo.numReservations = line;
            }
            else if (i == idLine + 11)
            {
                tripInfo.tripCost = line;
                cout << "Trip Cost: " << line << "$" << endl;
                cout << "-----------------------------------------------------------" << endl;
                break;
            }
        }
        getline(inputData, line);
        if (line == tripInfo.id && doPrint == false)
        {
            idLine = i;
            doPrint = true;
        }
    }
    inputData.close();
    cout << "--> Do you want to reserve this trip? Y|N: ";
    cin >> inChar;
    while (!(inChar[1] == '\0' && (inChar[0] == 'y' || inChar[0] == 'Y' || inChar[0] == 'n' || inChar[0] == 'N')))
    {
        cout << "You entered an incorrect choice!" << endl;
        cout << "--> The Answer (Y|N): ";
        cin >> inChar;
    }
    switch (inChar[0])
    {
    case 'n':
    case 'N':
        cout << "- Press One: Try again " << endl;
        cout << "- Press Two: Go to main menu" << endl;
        cout << "--> The Answer: ";
        cin >> inChar2;
        while (!(inChar2[1] == '\0' && (inChar2[0] == '1' || inChar2[0] == '2')))
        {
            cout << "- Press One: Try again " << endl;
            cout << "- Press Two: Go to main menu" << endl;
            cout << "--> The Answer: ";
            cin >> inChar2;
        }
        if (inChar2[0] == '1')
        {
            reserveTrip();
        }
        else if (inChar2[0] == '2')
        {
            clientMenu2();
        }
        break;
    case 'y':
    case 'Y':
        cout << "--> Enter the Number of People: ";
        cin.ignore();
        getline(cin, reservationInfo.numPeople);
        cout << "--> Payment method: ";
        getline(cin, reservationInfo.paymentMeth);
        cout << tripInfo.maxReservations << endl;
        cout << tripInfo.numReservations << endl;
        cout << reservationInfo.numPeople << endl;
        cout << userReg.wallet << endl;
        cout << tripInfo.tripCost << endl;
        if ((stoi(tripInfo.maxReservations) - stoi(tripInfo.numReservations) - stoi(reservationInfo.numPeople)) >= 0 && (stoi(userReg.wallet) >= stoi(reservationInfo.numPeople) * stoi(tripInfo.tripCost)))
        {
            // wallet current balance - tripcost
            inputData.open("data/usersInfo.txt");
            outputData.open("data/temp.txt");
            while (getline(inputData, line))
            {
                if (line == userReg.username)
                {
                    flag = true;
                    tmpcnt = 0;
                }
                if (tmpcnt == 7 && flag == true)
                {
                    outputData << (stoi(userReg.wallet) - stoi(reservationInfo.numPeople) * stoi(tripInfo.tripCost)) << endl;
                    tmpcnt++;
                    continue;
                }
                tmpcnt++;
                outputData << line << endl;
            }
            inputData.close();
            outputData.close();
            remove("data/usersInfo.txt");
            rename("data/temp.txt", "data/usersInfo.txt");
            // change number of reservations in trip struct
            inputData.open("data/tripsInfo.txt");
            ofstream outputData;
            outputData.open("data/temp2.txt");
            int i = 0;
            while (getline(inputData, line))
            {
                i++;
                if (i == idLine + 9)
                {
                    outputData << stoi(tripInfo.numReservations) + stoi(reservationInfo.numPeople) << endl;
                    continue;
                }
                outputData << line << endl;
            }
            inputData.close();
            outputData.close();
            remove("data/tripsInfo.txt");
            rename("data/temp2.txt", "data/tripsInfo.txt");
            refreshWallet();
            saveReservInfo();
            system("clear");
            cout << "Trip is reserved successfully!" << endl;
            cout << "- Press One: Reserve another trip" << endl;
            cout << "- Press Two: Return to main menu" << endl;
            cout << "--> The Answer: ";
            cin >> inChar3;
            while (inChar3[1] != '\0' || (inChar3[0] != '1' && inChar3[0] != '2'))
            {
                cout << "You entered an incorrect choice!" << endl;
                cout << "--> The Answer: ";
                cin >> inChar3;
            }
            switch (inChar3[0])
            {
            case '1':
                reserveTrip();
                break;
            case '2':
                clientMenu2();
                break;
            }
            break;
        }
        else
        {
            if ((stoi(tripInfo.maxReservations) - stoi(tripInfo.numReservations) - stoi(reservationInfo.numPeople)) < 0)
            {
                cout << "The available tickets are less than " << reservationInfo.numPeople << " tickets" << endl;
                cout << "- Press One: Return to main menu" << endl;
                cout << "--> The Answer: ";
                cin >> inChar3;
                cout << inChar3[0] << endl;
                while (inChar3[1] != '\0' || inChar3[0] != '1')
                {
                    cout << "You entered an incorrect choice!" << endl;
                    cout << "The Answer: ";
                    cin >> inChar3;
                }
                if (inChar3[0] == '1')
                {
                    clientMenu2();
                    break;
                }
            }
            if (stoi(userReg.wallet) < stoi(reservationInfo.numPeople) * stoi(tripInfo.tripCost))
            {
                cout << "Your wallet doesn't contain enough money!" << endl;
                cout << "- Press One: Return to main menu" << endl;
                cout << "--> The Answer: ";
                cin >> inChar3;
                while (inChar3[1] != '\0' && inChar3[0] != '1')
                {
                    cout << "You entered an incorrect choice!" << endl;
                    cout << "The Answer: ";
                    cin >> inChar3;
                }
                if (inChar3[0] == '1')
                {
                    clientMenu2();
                    break;
                }
            }
        }
    }
}
void saveReservInfo()
{
    /*      
        Saving Format
        Reservation Num
        Username
        Destination
        Num of people
        Means of transportation
        Start Date
        End Date
        Hotel Name
        Hotel Address
        Type of boarding
        Cost
    */
    // variables
    string line;
    string prevID;
    ifstream inputData;
    ofstream outputData;
    // booleans
    bool isEmpty = true;
    // calc number of reservs made
    inputData.open("data/reservsInfo.txt");
    outputData.open("data/reservsInfo.txt", ios::app);
    while (getline(inputData, line))
    {
        isEmpty = false;
        prevID = line;
        for (int i = 0; i < 11; i++)
        {
            getline(inputData, line);
        }
    }
    inputData.close();
    // printing data in files
    if (!isEmpty)
    {
        outputData << stoi(prevID) + 1 << endl; // reservation num
    }
    else
    {
        outputData << 1 << endl;
    }
    outputData << userReg.username << endl;
    outputData << tripInfo.destination << endl;
    outputData << reservationInfo.numPeople << endl;
    outputData << tripInfo.transportation << endl;
    outputData << tripInfo.startDate << endl;
    outputData << tripInfo.endDate << endl;
    outputData << tripInfo.hotelName << endl;
    outputData << tripInfo.hotelAddress << endl;
    outputData << tripInfo.boarding << endl;
    outputData << tripInfo.tripCost << endl;
    outputData << "-----------------------------" << endl;
    outputData.close();
}
void refreshWallet()
{
    ifstream inputData;
    string line;
    // correct the value of userReg.wallet
    inputData.open("data/usersInfo.txt");
    while (getline(inputData, line))
    {
        if (line == userReg.username)
        {
            for (int i = 0; i < 7; i++) // to get the wallet value
            {
                getline(inputData, line);
            }
            userReg.wallet = line;
            break;
        }
    }
    inputData.close();
}
void changeReserv()
{
    // variables
    char inChar[25] = {};
    string line;
    // booleans
    bool isFound = false; // check if the reservation is found or not
    // body
    refreshWallet(); // in this function I will use wallet of the user so I need to refresh it
    system("clear");
    cout << "User: Client            Action: Changing a Reservation...         Current balance: " << userReg.wallet << "$" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "--> Enter Reservation Num: ";
    cin >> reservationInfo.reservNum;
    // check if the reservation is found or not
    ifstream inputData;
    inputData.open("data/reservsInfo.txt");
    while (getline(inputData, line))
    {
        if (line == reservationInfo.reservNum)
        {
            getline(inputData, line);
            if (line == userReg.username)
            {
                isFound = true;
                getline(inputData, line);
                cout << endl;
                cout << "Reservation Info: " << endl;
                cout << "---------------------------------------" << endl;
                cout << "Destination: " << line << endl;
                cout << "---------------------------------------" << endl;
                oldDestination = line;
                getline(inputData, line);
                cout << "Num of tickets: " << line << endl;
                trip1Tickets = line; // to use it in the compare in checkTrip function
                cout << "---------------------------------------" << endl;

                getline(inputData, line);
                cout << "Means of Transportation: " << line << endl;
                cout << "---------------------------------------" << endl;

                getline(inputData, line);
                cout << "Start Date: " << line << endl;
                cout << "---------------------------------------" << endl;

                getline(inputData, line);
                cout << "End Date: " << line << endl;
                cout << "---------------------------------------" << endl;

                getline(inputData, line);
                cout << "Hotel Name: " << line << endl;
                cout << "---------------------------------------" << endl;

                getline(inputData, line);
                cout << "Hotel Address: " << line << endl;
                cout << "---------------------------------------" << endl;

                getline(inputData, line);
                cout << "Type of Boarding: " << line << endl;
                cout << "---------------------------------------" << endl;

                getline(inputData, line);
                cout << "Ticket Cost: " << line << "$" << endl;
                trip1Cost = line; // to use it in the compare in checkTrip function
                cout << "---------------------------------------" << endl;
                break;
            }
        }
    }
    inputData.close();
    if (!isFound)
    {
        cout << "There is no reservation with this number!" << endl;
        cout << "- Press One: Try again" << endl;
        cout << "- Press Two: Return to main menu" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
        while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
        {
            cout << "You entered an incorrect choice!" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
        }
        switch (inChar[0])
        {
        case '1':
            changeReserv();
            break;
        case '2':
            clientMenu2();
            break;
        }
    }
    // asking the user to confirm if he wants to change this reservation
    cout << "Do you want to change this reservation? Y|N: ";
    cin >> inChar;
    while (inChar[1] != '\0' || (inChar[0] != 'Y' && inChar[0] != 'y' && inChar[0] != 'n' && inChar[0] != 'N'))
    {
        cout << "You entered an incorrect choice!" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
    }
    switch (inChar[0])
    {
    case 'n':
    case 'N':
    {
        cout << "- Press One: Try again" << endl;
        cout << "- Press Two: Return to main menu" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
        while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
        {
            cout << "You entered an incorrect choice!" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
        }
        switch (inChar[0])
        {
        case '1':
            changeReserv();
            break;
        case '2':
            clientMenu2();
            break;
        }
        break;
    }
    case 'y':
    case 'Y':
        checkTrip(); // function to ask the user for the trip number and confirm if he wants to reserve this trip
    }
}
void checkTrip()
{
    ifstream inputData;
    ofstream outputData;
    // variables
    string line;
    string trip2Cost, trip2Tickets;
    char inChar[25] = {};
    // booleans
    bool isFound2 = false; // check if the trip is found or not
    bool flag = true;      // used in loop 1909 to check if the user entered a number in num of people
    // if the client confirmed that he wants to change the reservation then I would ask him to enter the id of the trip he want to reserve
    system("clear");
    cout << "User: Client            Action: Changing a Reservation...         Current balance: " << userReg.wallet << "$" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "--> Enter the ID of the trip you want to reserve: ";
    cin >> tripInfo.id;
    // check if the trip is found or not
    inputData.open("data/tripsInfo.txt");
    while (getline(inputData, line))
    {
        if (line == tripInfo.id)
        {
            isFound2 = true;
            // if the trip is found then ask the user to confirm if this is the trip he want to reserve
            cout << endl;
            cout << "Trip info: " << endl;
            getline(inputData, line);  // so that line contains the start date
            tripInfo.startDate = line; // here we will update the data stored in the struct to be able to use it later
            cout << "Start Date: " << line << endl;
            cout << "---------------------------------------" << endl;
            getline(inputData, line);
            cout << "End Date: " << line << endl;
            tripInfo.endDate = line;
            cout << "---------------------------------------" << endl;
            getline(inputData, line);
            cout << "Destination: " << line << endl;
            tripInfo.destination = line;
            cout << "---------------------------------------" << endl;
            getline(inputData, line);
            cout << "Means of Transportation: " << line << endl;
            tripInfo.transportation = line;
            cout << "---------------------------------------" << endl;
            getline(inputData, line);
            cout << "Hotel Name: " << line << endl;
            tripInfo.hotelName = line;
            cout << "---------------------------------------" << endl;
            getline(inputData, line);
            cout << "Hotel Address: " << line << endl;
            tripInfo.hotelAddress = line;
            cout << "---------------------------------------" << endl;
            getline(inputData, line);
            cout << "Type of Boarding; " << line << endl;
            tripInfo.boarding = line;
            cout << "---------------------------------------" << endl;
            getline(inputData, line); // to store max reservations
            tripInfo.maxReservations = line;
            getline(inputData, line); // to store reserved tickets
            tripInfo.numReservations = line;
            getline(inputData, line);
            cout << "Ticket Cost: " << line << endl;
            tripInfo.tripCost = line;
            trip2Cost = line;
            cout << "---------------------------------------" << endl;
            inputData.close();
            // ask him to confirm
            cout << "Do you want to reserve this trip? Y|N: ";
            cin >> inChar;
            while (inChar[1] != '\0' || (inChar[0] != 'Y' && inChar[0] != 'y' && inChar[0] != 'n' && inChar[0] != 'N'))
            {
                cout << "You entered an incorrect choice!" << endl;
                cout << "--> The Answer: ";
                cin >> inChar;
            }
            switch (inChar[0])
            {
            case 'n':
            case 'N':
            {
                cout << "- Press One: Try again" << endl;
                cout << "- Press Two: Return to main menu" << endl;
                cout << "--> The Answer: ";
                cin >> inChar;
                while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
                {
                    cout << "You entered an incorrect choice!" << endl;
                    cout << "--> The Answer: ";
                    cin >> inChar;
                }
                switch (inChar[0])
                {
                case '1':
                    checkTrip();
                    break;
                case '2':
                    clientMenu2();
                    break;
                }
                break;
            }
            case 'y':
            case 'Y':
            {
                cout << "Enter Number of Tickets: ";
                cin >> reservationInfo.numPeople;
                // check if the user entered a number
                do
                {
                    flag = true;
                    for (int i = 0; i < reservationInfo.numPeople.size(); i++)
                    {
                        if (!(reservationInfo.numPeople[i] >= 48 && reservationInfo.numPeople[i] <= 57))
                        {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag)
                    {
                        cout << "Please enter a number value!" << endl;
                        cout << "Enter Number of Tickets: ";
                        cin >> reservationInfo.numPeople;
                    }
                } while (!flag);
                trip2Tickets = reservationInfo.numPeople;
                cout << "Enter Payment Method: ";
                cin >> reservationInfo.paymentMeth;
                // check if the user entered num of tickets greater than the number of available tickets
                if (stoi(reservationInfo.numPeople) > (stoi(tripInfo.maxReservations) - stoi(tripInfo.numReservations)))
                {
                    system("clear");
                    cout << "User: Client            Action: Changing a Reservation...         Current balance: " << userReg.wallet << "$" << endl;
                    cout << "-----------------------------------------------------------------------------------------" << endl;
                    cout << "Sorry!, the number of tickets available is less than " << reservationInfo.numPeople << " tickets. " << endl;
                    cout << "- Press One: Return to the main menu" << endl;
                    cout << "--> The Answer: ";
                    cin >> inChar;
                    while (inChar[1] != '\0' || inChar[0] != '1')
                    {
                        cout << "You entered an incorrect choice!" << endl;
                        cout << "The Answer: ";
                        cin >> inChar;
                    }
                    if (inChar[0] == '1')
                    {
                        clientMenu2();
                    }
                }
                // now we need to check about two things; - trip has enough tickets for the people he want to reserve tickets for, - he has enough money
                if ((stoi(tripInfo.maxReservations) - stoi(tripInfo.numReservations) - stoi(reservationInfo.numPeople)) >= 0)
                {
                    // case 1: old trip * num tickets >= new trip * num tickets
                    if ((stoi(trip1Cost) * stoi(trip1Tickets)) >= stoi(trip2Cost) * stoi(trip2Tickets))
                    {
                        // do the action
                        /*
                        1- edit reservation info in resevsInfo txt file
                        2- edit user wallet value in usersInfo txt file
                        3- edit the number of reservations in tripsInfo txt file
                        4- update the struct of trip info with the new trip info
                        */
                        // ----------------------------------------
                        // 1- edit reservation info in resevsInfo txt file
                        inputData.open("data/reservsInfo.txt");
                        outputData.open("data/temp.txt");
                        while (getline(inputData, line))
                        {
                            if (line == reservationInfo.reservNum)
                            {
                                outputData << line << endl;
                                getline(inputData, line); // to skip the num
                                outputData << line << endl;
                                getline(inputData, line); // to skip the username
                                outputData << tripInfo.destination << endl;
                                getline(inputData, line);
                                outputData << reservationInfo.numPeople << endl;
                                getline(inputData, line);
                                outputData << tripInfo.transportation << endl;
                                getline(inputData, line);
                                outputData << tripInfo.startDate << endl;
                                getline(inputData, line);
                                outputData << tripInfo.endDate << endl;
                                getline(inputData, line);
                                outputData << tripInfo.hotelName << endl;
                                getline(inputData, line);
                                outputData << tripInfo.hotelAddress << endl;
                                getline(inputData, line);
                                outputData << tripInfo.boarding << endl;
                                getline(inputData, line);
                                outputData << tripInfo.tripCost << endl;
                                getline(inputData, line);
                            }
                            outputData << line << endl;
                        }
                        inputData.close();
                        outputData.close();
                        remove("data/reservsInfo.txt");
                        rename("data/temp.txt", "data/reservsInfo.txt");
                        // end of editing data in reservsInfo txt
                        // ----------------------------------------
                        // 2- edit user wallet value in usersInfo txt file
                        inputData.open("data/usersInfo.txt");
                        outputData.open("data/temp2.txt");
                        while (getline(inputData, line))
                        {
                            if (line == userReg.username)
                            {
                                // to skip untill line carries the wallet balance
                                for (int i = 0; i < 6; i++)
                                {
                                    outputData << line << endl;
                                    getline(inputData, line);
                                }
                                outputData << stoi(line) + (stoi(trip1Cost) * stoi(trip1Tickets) - stoi(trip2Cost) * stoi(trip2Tickets)) << endl;
                                getline(inputData, line); // line now carries -------
                            }
                            outputData << line << endl;
                        }
                        inputData.close();
                        outputData.close();
                        remove("data/usersInfo.txt");
                        rename("data/temp2.txt", "data/usersInfo.txt");
                        refreshWallet();
                        // ----------------------------------------
                        // 3- edit the number of reservations in tripsInfo txt file
                        inputData.open("data/tripsInfo.txt");
                        outputData.open("data/temp3.txt");
                        while (getline(inputData, line))
                        {
                            if (line == tripInfo.id)
                            {
                                for (int i = 0; i < 9; i++)
                                {
                                    outputData << line << endl;
                                    getline(inputData, line);
                                }
                                outputData << stoi(line) + stoi(reservationInfo.numPeople) << endl;
                                getline(inputData, line);
                            }
                            outputData << line << endl;
                        }
                        inputData.close();
                        outputData.close();
                        remove("data/tripsInfo.txt");
                        rename("data/temp3.txt", "data/tripsInfo.txt");
                        // here we should decrease the number of reservations of the old trip
                        inputData.open("data/tripsInfo.txt");
                        outputData.open("data/temp4.txt");
                        while (getline(inputData, line))
                        {
                            if (line == oldDestination)
                            {
                                for (int i = 0; i < 6; i++)
                                {
                                    outputData << line << endl;
                                    getline(inputData, line);
                                }
                                outputData << stoi(line) - 1 << endl;
                                getline(inputData, line);
                            }
                            outputData << line << endl;
                        }
                        inputData.close();
                        outputData.close();
                        remove("data/tripsInfo.txt");
                        rename("data/temp4.txt", "data/tripsInfo.txt");
                        system("clear");
                        cout << "User: Client            Action: Changing a Reservation...         Current balance: " << userReg.wallet << "$" << endl;
                        cout << "-----------------------------------------------------------------------------------------" << endl;
                        cout << "Congratulation!, Reservation changed successfully." << endl;
                        cout << "- Press One: Return to the main menu" << endl;
                        cout << "--> The Answer: ";
                        cin >> inChar;
                        while (inChar[1] != '\0' || inChar[0] != '1')
                        {
                            cout << "You entered an incorrect choice!" << endl;
                            cout << "The Answer: ";
                            cin >> inChar;
                        }
                        if (inChar[0] == '1')
                        {
                            clientMenu2();
                        }
                    }
                    // kda m3nah en floos elreservation elgded aktr mn elreservation el2dem
                    else if (stoi(trip1Cost) * stoi(trip1Tickets) < stoi(trip2Cost) * stoi(trip2Tickets))
                    {
                        // hna b2a elmafrood a3ml check hal el wallet t2dr tzawt 3la floos trip1 34an elreservation ytm wla l2a
                        if (stoi(trip1Cost) * stoi(trip1Tickets) + stoi(userReg.wallet) >= stoi(trip2Cost) * stoi(trip2Tickets))
                        {
                            cout << "We will take " << (stoi(trip2Cost) * stoi(trip2Tickets) - stoi(trip1Cost) * stoi(trip1Tickets)) << "$ from your wallet, Do you agree? Y|N: ";
                            cin >> inChar;
                            while (inChar[1] != '\0' || (inChar[0] != 'Y' && inChar[0] != 'y' && inChar[0] != 'n' && inChar[0] != 'N'))
                            {
                                cout << "You entered an incorrect choice!" << endl;
                                cout << "Do you agree? Y|N: ";
                                cin >> inChar;
                            }
                            switch (inChar[0])
                            {
                            case 'n':
                            case 'N':
                                cout << "Reservation cannot be done!" << endl;
                                cout << "- Press One: Return to the main menu" << endl;
                                cout << "--> The Answer: ";
                                cin >> inChar;
                                while (inChar[1] != '\0' || inChar[0] != '1')
                                {
                                    cout << "You entered an incorrect choice!" << endl;
                                    cout << "The Answer: ";
                                    cin >> inChar;
                                }
                                if (inChar[0] == '1')
                                {
                                    clientMenu2();
                                }
                                break;
                            case 'y':
                            case 'Y':
                            {
                                // 1- edit reservation info in resevsInfo txt file
                                inputData.open("data/reservsInfo.txt");
                                outputData.open("data/temp.txt");
                                while (getline(inputData, line))
                                {
                                    if (line == reservationInfo.reservNum)
                                    {
                                        outputData << line << endl;
                                        getline(inputData, line); // to skip the num
                                        outputData << line << endl;
                                        getline(inputData, line); // to skip the username
                                        outputData << tripInfo.destination << endl;
                                        getline(inputData, line);
                                        outputData << reservationInfo.numPeople << endl;
                                        getline(inputData, line);
                                        outputData << tripInfo.transportation << endl;
                                        getline(inputData, line);
                                        outputData << tripInfo.startDate << endl;
                                        getline(inputData, line);
                                        outputData << tripInfo.endDate << endl;
                                        getline(inputData, line);
                                        outputData << tripInfo.hotelName << endl;
                                        getline(inputData, line);
                                        outputData << tripInfo.hotelAddress << endl;
                                        getline(inputData, line);
                                        outputData << tripInfo.boarding << endl;
                                        getline(inputData, line);
                                        outputData << tripInfo.tripCost << endl;
                                        getline(inputData, line);
                                    }
                                    outputData << line << endl;
                                }
                                inputData.close();
                                outputData.close();
                                remove("data/reservsInfo.txt");
                                rename("data/temp.txt", "data/reservsInfo.txt");
                                // end of editing data in reservsInfo txt
                                // 2- edit user wallet value in usersInfo txt file
                                inputData.open("data/usersInfo.txt");
                                outputData.open("data/temp2.txt");
                                while (getline(inputData, line))
                                {
                                    if (line == userReg.username)
                                    {
                                        for (int i = 0; i < 7; i++)
                                        {
                                            outputData << line << endl;
                                            getline(inputData, line);
                                            // here we will change the wallet balance
                                        }
                                        outputData << stoi(line) - (stoi(trip2Cost) * stoi(trip2Tickets) - stoi(trip1Cost) * stoi(trip1Tickets)) << endl;
                                        getline(inputData, line); // so line contains -------------
                                    }
                                    outputData << line << endl;
                                }
                                inputData.close();
                                outputData.close();
                                remove("data/usersInfo.txt");
                                rename("data/temp2.txt", "data/usersInfo.txt");
                                refreshWallet();
                                // 3- edit the number of reservations in tripsInfo txt file
                                // here we increase the number of trips in the new trip reservation
                                inputData.open("data/tripsInfo.txt");
                                outputData.open("data/temp3.txt");
                                while (getline(inputData, line))
                                {
                                    if (line == tripInfo.id)
                                    {
                                        for (int i = 0; i < 9; i++)
                                        {
                                            outputData << line << endl;
                                            getline(inputData, line);
                                        }
                                        outputData << stoi(line) + stoi(reservationInfo.numPeople) << endl;
                                        getline(inputData, line);
                                    }
                                    outputData << line << endl;
                                }
                                inputData.close();
                                outputData.close();
                                remove("data/tripsInfo.txt");
                                rename("data/temp3.txt", "data/tripsInfo.txt");
                                // here we should decrease the number of reservations of the old trip
                                inputData.open("data/tripsInfo.txt");
                                outputData.open("data/temp4.txt");
                                while (getline(inputData, line))
                                {
                                    if (line == oldDestination)
                                    {
                                        for (int i = 0; i < 6; i++)
                                        {
                                            outputData << line << endl;
                                            getline(inputData, line);
                                        }
                                        outputData << stoi(line) - 1 << endl;
                                        getline(inputData, line);
                                    }
                                    outputData << line << endl;
                                }
                                inputData.close();
                                outputData.close();
                                remove("data/tripsInfo.txt");
                                rename("data/temp4.txt", "data/tripsInfo.txt");
                                // here we done this because we changed in the balance of the wallet
                                // last thing to show confirmation message with the current balance
                                system("clear");
                                cout << "User: Client            Action: Changing a Reservation...         Current balance: " << userReg.wallet << "$" << endl;
                                cout << "-----------------------------------------------------------------------------------------" << endl;
                                cout << "Congratulation!, Reservation changed successfully." << endl;
                                cout << "- Press One: Return to the main menu" << endl;
                                cout << "--> The Answer: ";
                                cin >> inChar;
                                while (inChar[1] != '\0' || inChar[0] != '1')
                                {
                                    cout << "You entered an incorrect choice!" << endl;
                                    cout << "The Answer: ";
                                    cin >> inChar;
                                }
                                if (inChar[0] == '1')
                                {
                                    clientMenu2();
                                }
                                break;
                            }
                            }
                        }
                        else
                        {
                            system("clear");
                            cout << "User: Client            Action: Changing a Reservation...         Current balance: " << userReg.wallet << "$" << endl;
                            cout << "-----------------------------------------------------------------------------------------" << endl;
                            cout << "Sorry!, Reservation cannot be done as you don't have enough money." << endl;
                            cout << "- Press One: Return to the main menu" << endl;
                            cout << "--> The Answer: ";
                            cin >> inChar;
                            while (inChar[1] != '\0' || inChar[0] != '1')
                            {
                                cout << "You entered an incorrect choice!" << endl;
                                cout << "The Answer: ";
                                cin >> inChar;
                            }
                            if (inChar[0] == '1')
                            {
                                clientMenu2();
                            }
                            break;
                        }
                    }
                }
                else
                {
                }
                break;
            }
            }
        }
        else
        {
            for (int i = 0; i < 11; i++)
            {
                getline(inputData, line);
            }
        }
    }
    if (!isFound2)
    {
        cout << "There is no trip with this number!" << endl;
        cout << "- Press One: Try again" << endl;
        cout << "- Press Two: Return to main menu" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
        while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
        {
            cout << "You entered an incorrect choice!" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
        }
        switch (inChar[0])
        {
        case '1':
            checkTrip();
            break;
        case '2':
            clientMenu2();
            break;
        }
    }
}
void HistReserv()
{
    // variables
    string line;
    string tmpID; // to store the num of reservation
    char inChar[25] = {};
    // booleans
    bool isFound = false;
    ifstream inputData;
    inputData.open("data/reservsInfo.txt");
    system("clear");
    cout << "User: Client";
    cout << "                                              Action: Showing history..." << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
    // search for the username
    while (getline(inputData, line))
    {
        if (line == userReg.username)
        {
            isFound = true;
            cout << endl;
            cout << "- Reservation Number: " << tmpID << endl;
            cout << "-------------------------------------------------" << endl;
            getline(inputData, line); // to skip the username
            cout << "Destination: " << line << endl;
            cout << "-------------------------------------------------" << endl;
            getline(inputData, line);
            cout << "Number of Tickets: " << line << endl;
            cout << "-------------------------------------------------" << endl;
            getline(inputData, line);
            cout << "Means of Transportation: " << line << endl;
            cout << "-------------------------------------------------" << endl;
            getline(inputData, line);
            cout << "Start Date: " << line << endl;
            cout << "-------------------------------------------------" << endl;
            getline(inputData, line);
            cout << "End Date: " << line << endl;
            cout << "-------------------------------------------------" << endl;
            getline(inputData, line);
            cout << "Hotel Name: " << line << endl;
            cout << "-------------------------------------------------" << endl;
            getline(inputData, line);
            cout << "Hotel Address: " << line << endl;
            cout << "-------------------------------------------------" << endl;
            getline(inputData, line);
            cout << "Type of Boarding: " << line << endl;
            cout << "-------------------------------------------------" << endl;
            getline(inputData, line);
            cout << "Ticket Cost: " << line << "$" << endl;
            cout << "-------------------------------------------------" << endl;
            getline(inputData, line); // to skip ------
        }
        else
        {
            tmpID = line;
        }
    }
    inputData.close();
    if (isFound)
    {
        cout << "- Press One: Return to main menu" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
        while (inChar[1] != '\0' || inChar[0] != '1')
        {
            cout << "You entered an incorrect choice!" << endl;
            cout << "- Press One: Return to main menu" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
        }
        if (inChar[0] == '1')
        {
            clientMenu2();
        }
    }
    // check if no username is found
    if (!isFound)
    {
        cout << "NO HISTORY!" << endl;
        cout << "- Press One: Return to main menu" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
        while (inChar[1] != '\0' || inChar[0] != '1')
        {
            cout << "You entered an incorrect choice!" << endl;
            cout << "- Press One: Return to main menu" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
        }
        if (inChar[0] == '1')
        {
            clientMenu2();
        }
    }
}
void openReserv()
{
    // variables
    string line;
    char inChar[25] = {};
    // booleans
    bool isFound = false;
    ifstream inputData;
    inputData.open("data/tripsInfo.txt");
    system("clear");
    cout << "User: Client";
    cout << "                                              Action: Showing open reservations..." << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
    while (getline(inputData, line))
    {
        isFound = true;
        cout << endl;
        cout << "- Trip ID: " << line << endl;
        cout << "-------------------------------------------------" << endl;
        getline(inputData, line);
        cout << "Start Date: " << line << endl;
        cout << "-------------------------------------------------" << endl;
        getline(inputData, line);
        cout << "End Date: " << line << endl;
        cout << "-------------------------------------------------" << endl;
        getline(inputData, line);
        cout << "Destination: " << line << endl;
        cout << "-------------------------------------------------" << endl;
        getline(inputData, line);
        cout << "Means of Transportation: " << line << endl;
        cout << "-------------------------------------------------" << endl;
        getline(inputData, line);
        cout << "Hotel Name: " << line << endl;
        cout << "-------------------------------------------------" << endl;
        getline(inputData, line);
        cout << "Hotel Address: " << line << endl;
        cout << "-------------------------------------------------" << endl;
        getline(inputData, line);
        cout << "Type of Boarding: " << line << endl;
        cout << "-------------------------------------------------" << endl;
        getline(inputData, line);
        getline(inputData, line);
        getline(inputData, line);
        cout << "Ticket Cost: " << line << "$" << endl;
        cout << "-------------------------------------------------" << endl;
        getline(inputData, line);
    }
    inputData.close();
    if (isFound)
    {
        cout << "- Press One: Return to main menu" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
        while (inChar[1] != '\0' || inChar[0] != '1')
        {
            cout << "You entered an incorrect choice!" << endl;
            cout << "- Press One: Return to main menu" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
        }
        if (inChar[0] == '1')
        {
            clientMenu2();
        }
    }
    // check if no username is found
    if (!isFound)
    {
        cout << "NO OPEN RESERVATIONS!" << endl;
        cout << "- Press One: Return to main menu" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
        while (inChar[1] != '\0' || inChar[0] != '1')
        {
            cout << "You entered an incorrect choice!" << endl;
            cout << "- Press One: Return to main menu" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
        }
        if (inChar[0] == '1')
        {
            clientMenu2();
        }
    }
}
void cancelReserv()
{
    // variables
    char date[8];
    string curr_date[3] = {};
    string start_date[3] = {};
    char inChar[25] = {};
    int numLine = 0; // to store the number of the line of reservation number
    string line;
    int start_days, current_days; // current_days to contain number of days in current year - start_days to contain no. of days in the year of the trip
    int month;
    // booleans
    bool isFound = false;
    bool flag = true;
    bool doContinue = false;
    ifstream inputData;
    ofstream outputData;
    system("clear");
    cout << "User: Client";
    cout << "                                              Action: Cancelling reservations..." << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << "--> Enter the number of reservation: ";
    cin >> reservationInfo.reservNum;
    do
    {
        flag = true;
        for (int i = 0; i < reservationInfo.reservNum.size(); i++)
        {
            if (!(reservationInfo.reservNum[i] >= 48 && reservationInfo.reservNum[i] <= 57))
            {
                flag = false;
                break;
            }
        }
        if (!flag)
        {
            cout << "Please enter a number value!" << endl;
            cout << "Enter the number of reservation: ";
            cin >> reservationInfo.reservNum;
        }
    } while (!flag);
    // check the date
    // put the start date in start_date arr
    inputData.open("data/reservsInfo.txt");
    while (getline(inputData, line))
    {
        numLine++;
        if (line == reservationInfo.reservNum)
        {
            getline(inputData, line);
            if (line == userReg.username)
            {
                isFound = true;
                getline(inputData, line);
                reservationInfo.destination = line;
                for (int i = 0; i < 3; i++)
                {
                    getline(inputData, line);
                }
                tripInfo.startDate = line;
                start_date[0] = string(1, line[0]) + line[1]; // to store day
                start_date[1] = string(1, line[3]) + line[4]; // to store month
                start_date[2] = string(1, line[8]) + line[9]; // to store year
                break;
            }
        }
    }
    inputData.close();
    if (isFound)
    {
        // getting the current date
        time_t current_time;
        tm *current_tm;
        time(&current_time);
        current_tm = localtime(&current_time);
        char current_date[8];
        strftime(current_date, 8, "%d%m%y", current_tm); // ddmmyy format
        // check if both dates are in the same year
        if (stoi((string(1, current_date[4]) + current_date[5])) == stoi(start_date[2]))
        {
            strftime(current_date, 8, "%j", current_tm); // now it carry the number of days
            current_days = stoi(current_date);
            // we need to calculate the number of days in the year of the trip
            month = stoi(start_date[1]);
            if (stoi(start_date[2]) % 4 == 0) // check if it is a leap year so feb will be 29
            {
                if ((month - 1) == 0)
                {
                    start_days = stoi(start_date[0]); // start_date[0] contains the day number as line 2549
                }
                else if ((month - 1) == 1)
                {
                    start_days = 31 + stoi(start_date[0]);
                }
                else if ((month - 1) == 2)
                {
                    start_days = 60 + stoi(start_date[0]);
                }
                else if ((month - 1) == 3)
                {
                    start_days = 91 + stoi(start_date[0]);
                }
                else if ((month - 1) == 4)
                {
                    start_days = 121 + stoi(start_date[0]);
                }
                else if ((month - 1) == 5)
                {
                    start_days = 152 + stoi(start_date[0]);
                }
                else if ((month - 1) == 6)
                {
                    start_days = 182 + stoi(start_date[0]);
                }
                else if ((month - 1) == 7)
                {
                    start_days = 213 + stoi(start_date[0]);
                }
                else if ((month - 1) == 8)
                {
                    start_days = 244 + stoi(start_date[0]);
                }
                else if ((month - 1) == 9)
                {
                    start_days = 274 + stoi(start_date[0]);
                }
                else if ((month - 1) == 10)
                {
                    start_days = 305 + stoi(start_date[0]);
                }
                else if ((month - 1) == 11)
                {
                    start_days = 335 + stoi(start_date[0]);
                }
            }
            else if (stoi(start_date[2]) % 4 != 0) // it is not a leap year
            {
                if ((month - 1) == 0)
                {
                    start_days = stoi(start_date[0]); // start_date[0] contains the day number as line 2549
                }
                else if ((month - 1) == 1)
                {
                    start_days = 31 + stoi(start_date[0]);
                }
                else if ((month - 1) == 2)
                {
                    start_days = 60 + stoi(start_date[0]);
                }
                else if ((month - 1) == 3)
                {
                    start_days = 91 + stoi(start_date[0]);
                }
                else if ((month - 1) == 4)
                {
                    start_days = 121 + stoi(start_date[0]);
                }
                else if ((month - 1) == 5)
                {
                    start_days = 152 + stoi(start_date[0]);
                }
                else if ((month - 1) == 6)
                {
                    start_days = 182 + stoi(start_date[0]);
                }
                else if ((month - 1) == 7)
                {
                    start_days = 213 + stoi(start_date[0]);
                }
                else if ((month - 1) == 8)
                {
                    start_days = 244 + stoi(start_date[0]);
                }
                else if ((month - 1) == 9)
                {
                    start_days = 274 + stoi(start_date[0]);
                }
                else if ((month - 1) == 10)
                {
                    start_days = 305 + stoi(start_date[0]);
                }
                else if ((month - 1) == 11)
                {
                    start_days = 335 + stoi(start_date[0]);
                }
            }
            // now current days carries the number of days in current year
            if (start_days > current_days + 7)
            {
                // now we should return the value of reservation to the wallet
                // here we will get the total value of the reservation
                inputData.open("data/reservsInfo.txt");
                while (getline(inputData, line))
                {
                    if (line == reservationInfo.reservNum)
                    {
                        for (int i = 0; i < 3; i++)
                        {
                            getline(inputData, line);
                        }
                        reservationInfo.numPeople = line;
                        for (int i = 0; i < 7; i++)
                        {
                            getline(inputData, line);
                        }
                        reservationInfo.cost = line;
                        break;
                    }
                }
                inputData.close();
                inputData.open("data/usersInfo.txt");
                outputData.open("data/temp.txt");
                while (getline(inputData, line))
                {
                    if (line == userReg.username)
                    {
                        for (int i = 0; i < 7; i++)
                        {
                            outputData << line << endl;
                            getline(inputData, line);
                        }
                        outputData << stoi(line) + stoi(reservationInfo.numPeople) * stoi(reservationInfo.cost) << endl;
                        continue;
                    }
                    outputData << line << endl;
                }
                inputData.close();
                outputData.close();
                remove("data/usersInfo.txt");
                rename("data/temp.txt", "data/usersInfo.txt");
                refreshWallet();
                // here we will remove 1 from the number of reservations in tripsInfo.txt
                inputData.open("data/tripsInfo.txt");
                outputData.open("data/temp2.txt");
                while (getline(inputData, line))
                {
                    if (line == tripInfo.startDate)
                    {
                        outputData << line << endl;
                        getline(inputData, line);
                        outputData << line << endl;
                        getline(inputData, line);
                        if (line == reservationInfo.destination)
                        {
                            for (int i = 0; i < 6; i++)
                            {
                                outputData << line << endl;
                                getline(inputData, line);
                            }
                            outputData << stoi(line) - 1 << endl;
                            continue;
                        }
                    }
                    outputData << line << endl;
                }
                inputData.close();
                outputData.close();
                remove("data/tripsInfo.txt");
                rename("data/temp2.txt", "data/tripsInfo.txt");
                // used to delete the reservation
                inputData.open("data/reservsInfo.txt");
                outputData.open("data/temp3.txt");
                while (getline(inputData, line))
                {
                    if (line == reservationInfo.reservNum)
                    {
                        isFound = true;
                        for (int i = 0; i < 11; i++)
                        {
                            getline(inputData, line);
                        }
                        continue;
                    }
                    outputData << line << endl;
                }
                inputData.close();
                outputData.close();
                remove("data/reservsInfo.txt");
                rename("data/temp3.txt", "data/reservsInfo.txt");
                cout << "Reservation cancelled successfully!" << endl;
                cout << "- Press One: Return to main menu" << endl;
                cout << "--> The Answer: ";
                cin >> inChar;
                while (inChar[1] != '\0' || inChar[0] != '1')
                {
                    cout << "You entered an incorrect choice!" << endl;
                    cout << "- Press One: Return to main menu" << endl;
                    cout << "--> The Answer: ";
                    cin >> inChar;
                }
                if (inChar[0] == '1')
                {
                    clientMenu2();
                }
            }
            else if (start_days > current_days)
            {
                cout << "Reservation cannot be cancelled!, As there is less than one week before the trip starts." << endl;
                cout << "- Press One: Return to main menu" << endl;
                cout << "--> The Answer: ";
                cin >> inChar;
                while (inChar[1] != '\0' || inChar[0] != '1')
                {
                    cout << "You entered an incorrect choice!" << endl;
                    cout << "- Press One: Return to main menu" << endl;
                    cout << "--> The Answer: ";
                    cin >> inChar;
                }
                if (inChar[0] == '1')
                {
                    clientMenu2();
                }
            }
            else
            {
                cout << "Reservation cannot be cancelled!, As the trip ended." << endl;
                cout << "- Press One: Return to main menu" << endl;
                cout << "--> The Answer: ";
                cin >> inChar;
                while (inChar[1] != '\0' || inChar[0] != '1')
                {
                    cout << "You entered an incorrect choice!" << endl;
                    cout << "- Press One: Return to main menu" << endl;
                    cout << "--> The Answer: ";
                    cin >> inChar;
                }
                if (inChar[0] == '1')
                {
                    clientMenu2();
                }
            }
        }
        else
        {
            strftime(current_date, 8, "%d%m%y", current_tm); // ddmmyy format
            if ((stoi(string(1, current_date[4]) + current_date[5])) > stoi(start_date[2]))
            {
                cout << "Reservation cannot be cancelled!, As the trip ended." << endl;
                cout << "- Press One: Return to main menu" << endl;
                cout << "--> The Answer: ";
                cin >> inChar;
                while (inChar[1] != '\0' || inChar[0] != '1')
                {
                    cout << "You entered an incorrect choice!" << endl;
                    cout << "- Press One: Return to main menu" << endl;
                    cout << "--> The Answer: ";
                    cin >> inChar;
                }
                if (inChar[0] == '1')
                {
                    clientMenu2();
                }
            }
            else if ((stoi(string(1, current_date[4]) + current_date[5])) < stoi(start_date[2]))
            {
                strftime(current_date, 8, "%j", current_tm); // now it carry the number of days
                current_days = stoi(current_date);
                // we need to calculate the number of days in the year of the trip
                month = stoi(start_date[1]);
                if (stoi(start_date[2]) % 4 == 0) // check if it is a leap year so feb will be 29
                {
                    if ((month - 1) == 0)
                    {
                        start_days = stoi(start_date[0]); // start_date[0] contains the day number as line 2549
                    }
                    else if ((month - 1) == 1)
                    {
                        start_days = 31 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 2)
                    {
                        start_days = 60 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 3)
                    {
                        start_days = 91 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 4)
                    {
                        start_days = 121 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 5)
                    {
                        start_days = 152 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 6)
                    {
                        start_days = 182 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 7)
                    {
                        start_days = 213 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 8)
                    {
                        start_days = 244 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 9)
                    {
                        start_days = 274 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 10)
                    {
                        start_days = 305 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 11)
                    {
                        start_days = 335 + stoi(start_date[0]);
                    }
                }
                else if (stoi(start_date[2]) % 4 != 0) // it is not a leap year
                {
                    if ((month - 1) == 0)
                    {
                        start_days = stoi(start_date[0]); // start_date[0] contains the day number as line 2549
                    }
                    else if ((month - 1) == 1)
                    {
                        start_days = 31 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 2)
                    {
                        start_days = 60 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 3)
                    {
                        start_days = 91 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 4)
                    {
                        start_days = 121 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 5)
                    {
                        start_days = 152 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 6)
                    {
                        start_days = 182 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 7)
                    {
                        start_days = 213 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 8)
                    {
                        start_days = 244 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 9)
                    {
                        start_days = 274 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 10)
                    {
                        start_days = 305 + stoi(start_date[0]);
                    }
                    else if ((month - 1) == 11)
                    {
                        start_days = 335 + stoi(start_date[0]);
                    }
                }
                if (start_days + (365 - current_days) > 7)
                {
                    // now we should return the value of reservation to the wallet
                    // here we will get the total value of the reservation
                    inputData.open("data/reservsInfo.txt");
                    while (getline(inputData, line))
                    {
                        if (line == reservationInfo.reservNum)
                        {
                            for (int i = 0; i < 3; i++)
                            {
                                getline(inputData, line);
                            }
                            reservationInfo.numPeople = line;
                            for (int i = 0; i < 7; i++)
                            {
                                getline(inputData, line);
                            }
                            reservationInfo.cost = line;
                            break;
                        }
                    }
                    inputData.close();
                    inputData.open("data/usersInfo.txt");
                    outputData.open("data/temp.txt");
                    while (getline(inputData, line))
                    {
                        if (line == userReg.username)
                        {
                            for (int i = 0; i < 7; i++)
                            {
                                outputData << line << endl;
                                getline(inputData, line);
                            }
                            outputData << stoi(line) + stoi(reservationInfo.numPeople) * stoi(reservationInfo.cost) << endl;
                            continue;
                        }
                        outputData << line << endl;
                    }
                    inputData.close();
                    outputData.close();
                    remove("data/usersInfo.txt");
                    rename("data/temp.txt", "data/usersInfo.txt");
                    refreshWallet();
                    // here we will remove 1 from the number of reservations in tripsInfo.txt
                    inputData.open("data/tripsInfo.txt");
                    outputData.open("data/temp2.txt");
                    while (getline(inputData, line))
                    {
                        if (line == tripInfo.startDate)
                        {
                            outputData << line << endl;
                            getline(inputData, line);
                            outputData << line << endl;
                            getline(inputData, line);
                            if (line == reservationInfo.destination)
                            {
                                for (int i = 0; i < 6; i++)
                                {
                                    outputData << line << endl;
                                    getline(inputData, line);
                                }
                                outputData << stoi(line) - 1 << endl;
                                continue;
                            }
                        }
                        outputData << line << endl;
                    }
                    inputData.close();
                    outputData.close();
                    remove("data/tripsInfo.txt");
                    rename("data/temp2.txt", "data/tripsInfo.txt");
                    // used to delete the reservation
                    inputData.open("data/reservsInfo.txt");
                    outputData.open("data/temp3.txt");
                    while (getline(inputData, line))
                    {
                        if (line == reservationInfo.reservNum)
                        {
                            isFound = true;
                            for (int i = 0; i < 11; i++)
                            {
                                getline(inputData, line);
                            }
                            continue;
                        }
                        outputData << line << endl;
                    }
                    inputData.close();
                    outputData.close();
                    remove("data/reservsInfo.txt");
                    rename("data/temp3.txt", "data/reservsInfo.txt");
                    cout << "Reservation cancelled successfully!" << endl;
                    cout << "- Press One: Return to main menu" << endl;
                    cout << "--> The Answer: ";
                    cin >> inChar;
                    while (inChar[1] != '\0' || inChar[0] != '1')
                    {
                        cout << "You entered an incorrect choice!" << endl;
                        cout << "- Press One: Return to main menu" << endl;
                        cout << "--> The Answer: ";
                        cin >> inChar;
                    }
                    if (inChar[0] == '1')
                    {
                        clientMenu2();
                    }
                }
                else
                {
                    cout << "Reservation cannot be cancelled!, As there is less than one week before the trip starts." << endl;
                    cout << "- Press One: Return to main menu" << endl;
                    cout << "--> The Answer: ";
                    cin >> inChar;
                    while (inChar[1] != '\0' || inChar[0] != '1')
                    {
                        cout << "You entered an incorrect choice!" << endl;
                        cout << "- Press One: Return to main menu" << endl;
                        cout << "--> The Answer: ";
                        cin >> inChar;
                    }
                    if (inChar[0] == '1')
                    {
                        clientMenu2();
                    }
                }
            }
        }
    }
    if (!isFound)
    {
        cout << "There is no reservation with this number!" << endl;
        cout << "- Press One: Try again" << endl;
        cout << "- Press Two: Return to main menu" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
        while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
        {
            cout << "You entered an incorrect choice!" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
        }
        switch (inChar[0])
        {
        case '1':
            cancelReserv();
            break;
        case '2':
            clientMenu2();
            break;
        }
    }
}
void putWallet()
{
    // variables
    char inChar[25] = {};
    char temp = inChar[0];
    char inChar2[25] = {};
    // booleans
    bool isContinue = true;
    bool flag = false;
    system("clear");
    cout << "User: Client              Action: Adding money...           Current Balance: " << userReg.wallet << "$" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    // check if the user added money or not in the file
    ifstream inputData;
    inputData.open("data/walletInfo.txt");
    string line;
    while (getline(inputData, line))
    {
        if (userReg.username == line)
        {
            flag = true;
            getline(inputData, line);
            userReg.wallet = line;
            getline(inputData, line);
            if (line == "Waiting for Confirmation...")
            {
                reservationInfo.confPayment = "Waiting for Confirmation..."; // as when the program starts again all variables in the struct doesn't have any values
                canAdd = false;
                break;
            }
        }
    }
    if (!flag)
    {
        canAdd = true;
    }
    if (canAdd)
    {
        cout << "--> Enter the amount of money you want to add: ";
        cin >> userReg.wallet;
        do
        {
            isContinue = true;
            for (int i = 0; i < userReg.wallet.size(); i++)
            {
                if (userReg.wallet[i] >= 48 && userReg.wallet[i] <= 57)
                {
                    continue;
                }
                isContinue = false;
                break;
            }
            if (!isContinue)
            {
                cout << "Please enter a number value!" << endl;
                cout << "--> The Value: ";
                cin >> userReg.wallet;
            }
        } while (!isContinue);
        cout << "Do you want to add " << userReg.wallet << "$ to your account? Y|N: ";
        cin >> inChar;
        while (!(inChar[1] == temp && (inChar[0] == 'y' || inChar[0] == 'Y' || inChar[0] == 'N' || inChar[0] == 'n')))
        {
            cout << "You entered an incorrect choice!" << endl;
            cout << "The Choice: ";
            cin >> inChar;
        }
        switch (inChar[0])
        {
        case 'n':
        case 'N':
            canAdd = true;
            clientMenu2();
            break;
        case 'y':
        case 'Y':
            canAdd = false;
            reservationInfo.confPayment = "Waiting for Confirmation...";
            saveWalletInfo();
            //ask for returning to the main menu
            cout << "- Press One: Return back to the main menu" << endl;
            cout << "--> The Answer: ";
            cin >> inChar2;
            while (!(inChar2[1] == temp && inChar2[0] == '1'))
            {
                cout << "You entered an incorrect choice!" << endl;
                cout << "--> The Answer: ";
                cin >> inChar2;
            }
            switch (inChar2[0])
            {
            case '1':
                clientMenu2();
                break;
            }
            break;
        }
    }
    else
    {
        cout << "Money Added: " << userReg.wallet << "$" << endl; // userReg variable is not carrying the actual value of the wallet it's only temp(actual val in wallet file)
        cout << "----------------------------------------------" << endl;
        cout << "Current State: " << reservationInfo.confPayment << endl;
        cout << "----------------------------------------------" << endl;
        cout << "- Press One: Return back to the main menu" << endl;
        cout << "--> The Answer: ";
        cin >> inChar2;
        while (!(inChar2[1] == temp && inChar2[0] == '1'))
        {
            cout << "You entered an incorrect choice!" << endl;
            cout << "--> The Answer: ";
            cin >> inChar2;
        }
        switch (inChar2[0])
        {
        case '1':
            clientMenu2();
            break;
        }
    }
}
void saveWalletInfo()
{
    // elfunction deh 34an a3ml save lel data fel file
    ofstream outputData;
    outputData.open("data/walletInfo.txt", ios::app);
    outputData << userReg.username << endl;
    outputData << userReg.wallet << endl;
    outputData << reservationInfo.confPayment << endl;
    outputData << "---------------------------------------" << endl;
    outputData.close();
}
void editAccInfo()
{
    // variables
    string line;
    char inChar[25] = {};
    // booleans
    // filestreams
    ifstream inputData;
    ofstream outputData;
    system("clear");
    cout << "User: " << userReg.username;
    cout << "                                        Action: Editing accound information..." << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "Account Information: " << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "- Username: " << userReg.username << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "- To Edit (Press One)   --> First Name:   " << userReg.firstname << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "- To Edit (Press Two)   --> Last Name:    " << userReg.lastname << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "- to Edit (Press Three) --> Email:        " << userReg.email << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "- To Edit (Press Four)  --> Phone Number: " << userReg.phonenumber << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "- To Edit (Press Five)  --> Address:      " << userReg.address << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "- To Edit (Press Six)   --> Password:     ";
    // show password as asterisks
    for (int i = 0; i < userReg.password1.size(); i++)
    {
        cout << "*";
    }
    cout << endl;
    cout << "---------------------------------------------------------------------" << endl;
    cout << "--> The Answer: ";
    cin >> inChar;
    while (inChar[1] != '\0' || (!(inChar[0] >= 49 && inChar[0] <= 54)))
    {
        cout << "You entered an incorrect choice!" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
    }
    inputData.open("data/usersInfo.txt");
    outputData.open("data/temp.txt");
    switch (inChar[0])
    {
    case '1':
    {
        system("clear");
        cout << "User: " << userReg.username;
        cout << "                                        Action: Editing accound information..." << endl;
        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "--> Enter The New First Name: ";
        cin >> userReg.firstname;
        while (getline(inputData, line))
        {
            if (line == userReg.username)
            {
                outputData << line << endl;
                getline(inputData, line); // to get the first name
                outputData << userReg.firstname << endl;
                continue;
            }
            outputData << line << endl;
        }
        inputData.close();
        outputData.close();
        remove("data/usersInfo.txt");
        rename("data/temp.txt", "data/usersInfo.txt");
        cout << "First Name Changed Successfully!" << endl;
        cout << "- Press One: Edit another information" << endl;
        cout << "- Press Two: Return to main menu" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
        while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
        {
            cout << "You entered an incorrect choice!" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
        }
        switch (inChar[0])
        {
        case '1':
            editAccInfo();
            break;
        case '2':
            clientMenu2();
            break;
        }
        break;
    }
    case '2':
    {
        system("clear");
        cout << "User: " << userReg.username;
        cout << "                                        Action: Editing accound information..." << endl;
        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "--> Enter The New Last Name: ";
        cin >> userReg.lastname;
        while (getline(inputData, line))
        {
            if (line == userReg.username)
            {
                outputData << line << endl;
                for (int i = 0; i < 1; i++)
                {
                    getline(inputData, line);
                    outputData << line << endl;
                }
                getline(inputData, line);
                outputData << userReg.lastname << endl;
                continue;
            }
            outputData << line << endl;
        }
        inputData.close();
        outputData.close();
        remove("data/usersInfo.txt");
        rename("data/temp.txt", "data/usersInfo.txt");
        cout << "Last Name Changed Successfully!" << endl;
        cout << "- Press One: Edit another information" << endl;
        cout << "- Press Two: Return to main menu" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
        while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
        {
            cout << "You entered an incorrect choice!" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
        }
        switch (inChar[0])
        {
        case '1':
            editAccInfo();
            break;
        case '2':
            clientMenu2();
            break;
        }
        break;
    }
    case '3':
    {
        system("clear");
        cout << "User: " << userReg.username;
        cout << "                                        Action: Editing accound information..." << endl;
        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "--> Enter The New Email: ";
        cin >> userReg.email;
        while (getline(inputData, line))
        {
            if (line == userReg.username)
            {
                outputData << line << endl;
                for (int i = 0; i < 2; i++)
                {
                    getline(inputData, line);
                    outputData << line << endl;
                }
                getline(inputData, line);
                outputData << userReg.email << endl;
                continue;
            }
            outputData << line << endl;
        }
        inputData.close();
        outputData.close();
        remove("data/usersInfo.txt");
        rename("data/temp.txt", "data/usersInfo.txt");
        cout << "Email Changed Successfully!" << endl;
        cout << "- Press One: Edit another information" << endl;
        cout << "- Press Two: Return to main menu" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
        while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
        {
            cout << "You entered an incorrect choice!" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
        }
        switch (inChar[0])
        {
        case '1':
            editAccInfo();
            break;
        case '2':
            clientMenu2();
            break;
        }
        break;
    }
    case '4':
    {
        system("clear");
        cout << "User: " << userReg.username;
        cout << "                                        Action: Editing accound information..." << endl;
        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "--> Enter The New Phone Number: ";
        cin >> userReg.phonenumber;
        while (getline(inputData, line))
        {
            if (line == userReg.username)
            {
                outputData << line << endl;
                for (int i = 0; i < 3; i++)
                {
                    getline(inputData, line);
                    outputData << line << endl;
                }
                getline(inputData, line);
                outputData << userReg.phonenumber << endl;
                continue;
            }
            outputData << line << endl;
        }
        inputData.close();
        outputData.close();
        remove("data/usersInfo.txt");
        rename("data/temp.txt", "data/usersInfo.txt");
        cout << "Phone Number Changed Successfully!" << endl;
        cout << "- Press One: Edit another information" << endl;
        cout << "- Press Two: Return to main menu" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
        while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
        {
            cout << "You entered an incorrect choice!" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
        }
        switch (inChar[0])
        {
        case '1':
            editAccInfo();
            break;
        case '2':
            clientMenu2();
            break;
        }
        break;
    }
    case '5':
    {
        system("clear");
        cout << "User: " << userReg.username;
        cout << "                                        Action: Editing accound information..." << endl;
        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "--> Enter The New Address: ";
        cin >> userReg.address;
        while (getline(inputData, line))
        {
            if (line == userReg.username)
            {
                outputData << line << endl;
                for (int i = 0; i < 4; i++)
                {
                    getline(inputData, line);
                    outputData << line << endl;
                }
                getline(inputData, line);
                outputData << userReg.address << endl;
                continue;
            }
            outputData << line << endl;
        }
        inputData.close();
        outputData.close();
        remove("data/usersInfo.txt");
        rename("data/temp.txt", "data/usersInfo.txt");
        cout << "Address Changed Successfully!" << endl;
        cout << "- Press One: Edit another information" << endl;
        cout << "- Press Two: Return to main menu" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
        while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
        {
            cout << "You entered an incorrect choice!" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
        }
        switch (inChar[0])
        {
        case '1':
            editAccInfo();
            break;
        case '2':
            clientMenu2();
            break;
        }
        break;
    }
    case '6':
    {
        system("clear");
        cout << "User: " << userReg.username;
        cout << "                                        Action: Editing accound information..." << endl;
        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "--> Enter The New Password: ";
        cin >> userReg.password1;
        cout << "--> Confirm Password: ";
        cin >> userReg.password2;
        // check if the two passwords are the same
        while (userReg.password1 != userReg.password2)
        {
            system("clear");
            cout << "User: " << userReg.username;
            cout << "                                        Action: Editing accound information..." << endl;
            cout << "-----------------------------------------------------------------------------------------" << endl;
            cout << "THE TWO PASSWORDS ARE NOT THE SAME!" << endl;
            cout << "--> Enter The New Password: ";
            cin >> userReg.password1;
            cout << "--> Confirm Password: ";
            cin >> userReg.password2;
        }
        while (getline(inputData, line))
        {
            if (line == userReg.username)
            {
                outputData << line << endl;
                for (int i = 0; i < 5; i++)
                {
                    getline(inputData, line);
                    outputData << line << endl;
                }
                getline(inputData, line);
                outputData << userReg.password1 << endl;
                continue;
            }
            outputData << line << endl;
        }
        inputData.close();
        outputData.close();
        remove("data/usersInfo.txt");
        rename("data/temp.txt", "data/usersInfo.txt");
        cout << "Password Changed Successfully!" << endl;
        cout << "- Press One: Edit another information" << endl;
        cout << "- Press Two: Return to main menu" << endl;
        cout << "--> The Answer: ";
        cin >> inChar;
        while (inChar[1] != '\0' || (inChar[0] != '1' && inChar[0] != '2'))
        {
            cout << "You entered an incorrect choice!" << endl;
            cout << "--> The Answer: ";
            cin >> inChar;
        }
        switch (inChar[0])
        {
        case '1':
            editAccInfo();
            break;
        case '2':
            clientMenu2();
            break;
        }
        break;
    }
    }
    // do the action and update info
}
void clLogout()
{
    system("clear");
    roleInput();
}
// --------Register----------
bool R_Username_Unique()
{
    bool isFound = false;
    string line; // stories temp the username stored in file
    ifstream inputData;
    inputData.open("data/usersInfo.txt");
    while (getline(inputData, line))
    {
        getline(inputData, line);
        if (line == userReg.username)
        {
            isFound = true;
            break;
        }
        else
        {
            for (int i = 0; i < 8; i++)
            {
                getline(inputData, line);
            }
        }
    }
    inputData.close();
    if (isFound)
    {
        return false;
    }
    else
        return true;
}
bool R_Phone_CFormat(string number)
{
    bool isCorrect = true;
    for (int i = 0; i < 11; i++)
    {
        if (!(number[i] >= 48 && number[0] <= 57))
        {
            isCorrect = false;
            break;
        }
    }
    if (!isCorrect)
    {
        return false;
    }
    else
        return true;
}
bool R_Email_CFormat(string email)
{
    int cnt = 0;
    bool isCorrect = true;
    if (email.size() >= 8)
    {
        for (int i = 0; i < email.size(); i++)
        {
            if (email[i] == 64)
            {
                cnt++;
                if (cnt > 1)
                {
                    isCorrect = false;
                    break;
                }
            }
        }
        if (cnt == 0)
        {
            isCorrect = false;
        }
    }
    else
        isCorrect = false;
    if (!isCorrect)
    {
        return false;
    }
    else
        return true;
}
bool R_Pass_Conf()
{
    bool isCorrect = false;
    if (userReg.password1 == userReg.password2)
    {
        isCorrect = true;
    }
    if (isCorrect)
    {
        return true;
    }
    else
        return false;
}
// ---------Login-------------
bool L_ValUser()
{
    bool isFound = false;
    int UserLine = 0;
    int x = 0;
    string line;
    int savedPos = 0; // the number of checked lines
    ifstream inputData;
    inputData.open("data/usersInfo.txt");
    do
    {
        UserLine = LinesEachUser * x + 2;
        for (int i = savedPos; i < UserLine; i++)
        {
            getline(inputData, line);
            savedPos++;
        }
        x++;
        if (ClUser == line)
        {
            isFound = true;
            break;
        }
    } while (UserLine <= (FileLines));
    if (isFound)
    {
        return true;
    }
    else
        return false;
}
bool L_ValPass()
{
    bool userFound = false;
    ifstream inputData;
    inputData.open("data/usersInfo.txt");
    string line;
    while (getline(inputData, line))
    {
        if (line == userReg.username)
        {
            for (int i = 0; i < 6; i++)
            {
                getline(inputData, line);
            }
            userFound = true;
            break;
        }
    }
    if (userFound && line == ClPass)
    {
        return true;
    }
    else
    {
        return false;
    }
}
string GetFirstName(int firstnameline)
{
    ifstream inputData;
    inputData.open("data/usersInfo.txt");
    string line;
    for (int i = 0; i < firstnameline; i++)
    {
        getline(inputData, line);
    }
    return line;
}
int NumberOfUsers()
{
    NumberOfLines = 0;
    ifstream inputData;
    inputData.open("data/usersInfo.txt");
    string line;
    if (inputData.is_open())
    {
        while (getline(inputData, line))
        {
            NumberOfLines++;
        }
    }
    FileLines = NumberOfLines;
    return NumberOfLines / LinesEachUser;
}
int NumberofTrips()
{
    NumberOfTrips = 0;
    int tmp = 0;
    ifstream inputData;
    inputData.open("data/tripsInfo.txt");
    string line;
    while (getline(inputData, line))
    {
        tmp++;
    }
    NumberOfTrips = tmp / LinesEachTrip;
    return NumberOfTrips;
}
int main()
{
    NumberOfUsers();
    NumberofTrips();
    roleInput();
}
/*
        Done By: Ziad Sameh
            Release Date: 24 / 7 / 2021
                Project Name: Banking System

*/