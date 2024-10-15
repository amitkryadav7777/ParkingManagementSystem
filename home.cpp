/*
******   Made by AMIT KUMAR YADAV  ******

Name      - Amit Kumar Yadav
Email     - amitkryadav7777@gmail.com
Github    - https://github.com/amitkryadav7777
LinkedIn  - https://linkedin.com/in/amitkryadav7777
Twitter/X - https://twitter.com/amitkryadav7777
Instagram - https://instagram.com/amitkryadav7777
Date      - 15 Oct 2024
*/

#include <iostream>
#include <conio.h>
#include <fstream>
#include <istream>
#include <sstream>
#include <ctime>
#include <time.h>
#include <string>
#include <vector>
#include <thread>
#include <graphics.h>
using namespace std;

string category; // This global varialbe identify admin and normal user
int invalid = 0;
void title() // This will show the title on the top
{
    cout << "\t\t-----------------------------------------------\n";
    cout << "\t\t\t   :: Car Parking System ::" << endl;
    cout << "\t\t-----------------------------------------------\n\n";
    return;
}
// This fun() will called after successful login...
void home(string declCategory, string vehicleNum);

// This function will check the login credentials...
void authentication(string authCategory, string username, string password);

// When the admin choose for login
int login();

// To park a new car...
void parkCar(string category);

// To release a car from the parking lot...
void releaseCar(string category, string withdrawalvehicleNum);

// To see the list of all parked cars...
void allParkedCar();

// Login for admin...
void adminLogin();

// For user...
void userLogin();

void parkCar(string category) // To park a new car
{
    system("cls");
    title();
    string name, vehicleNum, vehicleBrand, vehicleModel, mobile, duration, parkTime, releaseTime = "0";
    bool status = false;
    int charge = 1;
    fstream fout;
    fstream out;
    // opens existing csv files or creates new files to store parking details.
    fout.open("parkedCar.csv", ios::out | ios::app);
    cout << "\t\tParking a new car -- \n\n";
    cout << "\t\tParking charge : 100 Rs/Hr- \n\n";
    cout << "\t\tCar Owner's Name  : "; // Now taking input of vehicle's details
    cin.ignore();
    getline(cin, name);

    cout << "\t\tVehicle Number    : ";
    getline(cin, vehicleNum);

    cout << "\t\tVehicle Brand     : ";
    getline(cin, vehicleBrand);

    cout << "\t\tVehicle Model     : ";
    getline(cin, vehicleModel);

    cout << "\t\tMobile            : ";
    cin >> mobile;

    cout << "\t\tPark Time (Hr)    : ";
    cin >> duration;

    char delimiter = ','; // CHECK-START, Checking vehicle number's availabilty...
    std::string line;
    std::string item;
    std::ifstream file("parkedCar.csv");
    std::vector<std::string> row;
    while (std::getline(file, line))
    {
        row.clear();
        std::stringstream string_stream(line);
        while (std::getline(string_stream, item, delimiter))
        {
            row.push_back(item);
        }
        if (vehicleNum == row[1])
        {
            cout << "\t\tThis vehicle number already exists!\n"
                 << endl;
            delay(1000);
            file.close();
            parkCar(category);
            return;
        }
    } // CHECK-END

    time_t t;
    struct tm *tm;
    char Date[30];
    std::time(&t);
    tm = localtime(&t);
    strftime(Date, sizeof Date, "%x %X", tm);
    parkTime = Date;

    charge = 100 * stoi(duration);

    // Inserting the data into parkedCar.csv file
    fout << name << ","
         << vehicleNum << ","
         << vehicleBrand << ","
         << vehicleModel << ","
         << mobile << ","
         << duration << ","
         << charge << ","
         << parkTime << ","
         << releaseTime << ","
         << status
         << "\n";

    cout << "\t\tCar successfully parked." << endl;

    fout.close();
    delay(1000);
    if (category == "user")
    {
        login();
        return;
    }
    home(category, vehicleNum);
    return;
}

void releaseCar(string category, string releasevehicleNum) // To release a car...
{
    system("cls");
    title();

    string vehicleNum;
    vehicleNum = releasevehicleNum;
    bool accPresent = false;

    char delimiter = ',';
    std::string line;
    vector<string> lines;
    std::string item;
    std::ifstream file("parkedCar.csv");
    std::vector<std::string> row;
    while (std::getline(file, line))
    {
        row.clear();
        std::stringstream string_stream(line);
        while (std::getline(string_stream, item, delimiter))
        {
            row.push_back(item);
        }

        if (row[1] == vehicleNum)
        {
            cout << "\n\t\tTotal charge is    : " << row[6] << endl; // We will skip the data to be store which vehicle is releasing
            accPresent = true;
            continue;
        }

        line = "";
        for (int i = 0; i < row.size(); i++)
        {
            line.append(row[i]);
            if (i != row.size() - 1)
            {
                line.push_back(',');
            }
        }
        lines.push_back(line);
    }

    fstream fin;
    fin.open("parkedCar.csv", ios::out); // Now updating data in the database

    for (string l : lines)
    {
        fin << l << "\n";
    }
    fin.close();

    if (accPresent)
    {
        cout << "\n\t\tCar successfully released!\n\n";
    }
    if (!accPresent)
    {
        cout << "\n\n\t\tInvalid vehicle number...\n\n"
             << endl;
    }
    cout << "\t\t";
    system("PAUSE");
    if(category == "user") login();
    else home(category, vehicleNum);
    return;
}

void allParkedCar() // To all parked cars' list
{
    system("cls");
    title();
    string vehicleNum, balance;
    vehicleNum = vehicleNum;
    bool accPresent = false;
    long int finalBalance;
    fstream file;
    // opening parkedCar.csv file to fetch all details.
    file.open("parkedCar.csv", ios::out | ios::app | ios::in);
    cout << "\n\t\tAll Parked Cars - \n";
    cout << "\n\t\tName \tVehicle No\tBrand\tMobile\t\tTime\t\t\tDuration\tCharge\n" << endl;
    while (file.eof() == 0)
    {
        char delimiter = ',';
        std::string line;
        std::string item;
        std::vector<std::string> row;
        while (std::getline(file, line))
        {
            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            cout << "\t\t" << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[4] << "\t" << row[7] << "\t" << row[5] << " Hr\t\t" << row[6] << endl;
        }
    }
    file.close();
    cout << "\n\t\t";
    system("PAUSE");
    home(category, vehicleNum);
    return;
}

void adminLogin()
{ // This will called when we choose admin
    system("cls");
    title();
    string username, password;
    category = "admin";
    cout << "\t\tEnter username : ";
    cin >> username;
    cout << "\t\tEnter password : ";
    cin >> password;
    authentication(category, username, password);
    return;
}
void userLogin()
{ // This will called when we choose user
    system("cls");
    title();
    string username, password;
    category = "user";
    int userType;
    cout << "\t\t1. Park a car\n";
    cout << "\t\t2. Release a car\n";
    cout << "\n\t\tChoose your option : ";
    int option;
    cin >> option;

    if (option == 1)
    {
        parkCar(category);
        return;
    }
    else if (option == 2)
    {
        string vehicleNum, mobile;
        cout << "\n\t\tEnter your vehicle number : " ;
        cin >> vehicleNum;
        cout << "\n\t\tEnter your mobile number : " ;
        cin >> mobile;

        bool Present = false;
        fstream file;
        // opening an existing csv file to fetch account holders' details.
        file.open("parkedCar.csv", ios::out | ios::app | ios::in);
        while (file.eof() == 0)
        {
            char delimiter = ',';
            std::string line;
            std::string item;
            std::vector<std::string> row;
            while (std::getline(file, line))
            {
                row.clear();
                std::stringstream string_stream(line);
                while (std::getline(string_stream, item, delimiter))
                {
                    row.push_back(item);
                }
                if (row[1] == vehicleNum && row[4] == mobile) // Now printing data of user
                {
                    Present = true;
                    releaseCar(category, vehicleNum);
                    return ;
                }
            }
        }
        file.close();

        if(!Present) cout << "\n\t\tInvalid vehicle number or mobile number...";
        cout << "\n\n\t\t";
        system("PAUSE");
        login();
        return ;
    }
    else{
        login();
    }
    return;
}
void authentication(string authCategory, string username, string password)
{ // To verify login credentials
    char delimiter = ',';
    std::string line;
    std::string item;
    std::ifstream file("login.csv");
    std::vector<std::string> row;
    while (std::getline(file, line))
    {
        row.clear();
        std::stringstream string_stream(line);
        while (std::getline(string_stream, item, delimiter))
        {
            row.push_back(item);
        }
        if ((username == row[1]) && (password == row[2]))
        {
            cout << "\n\t\tYou have successfully logged in!\n"
                 << endl;
            delay(1000);
            file.close();
            home(authCategory, username);
            file.close();
            return;
        }
    }
    cout << "\n\t\tInvalid credentials.\n"
         << endl;
    file.close();
    delay(1000);
    system("cls");
    title();
    login();
    file.close();
    return;
}
int login() // To select type of login either Admin or User
{
    system("cls");
    title();
    int type;
    cout << "\t\tPlease choose your category -\n\n";
    cout << "\t\t1. Parking Admin\n";
    cout << "\t\t2. Vehicle Owner\n\n";
    cout << "\t\tType your category : ";
    cin >> type;

    if (type == 1)
    {
        adminLogin();
    }
    if (type == 2)
    {
        userLogin();
    }
    return 0;
}
void home(string homeCategory, string vehicleNum) // This will be executed after login
{
    int option = 0;
    system("cls");
    title();
    if (homeCategory == "admin")
    {
        cout << "\t\t1. Park a Car\n";
    }
    else
    {
        cout << "\t\t1. Your Parking Detail\n";
    }

    cout << "\t\t2. All Parked Car's List\n";
    cout << "\t\t3. Release Car\n";
    cout << "\t\t4. Logout & Exit\n";
    cout << "\n\t\tEnter your choice : ";
    cin >> option;
    string optionData;
    switch (option)
    {
    case 1:
        parkCar(homeCategory);
        break;

    case 2:
        allParkedCar();
        break;

    case 3:
        if (homeCategory == "admin")
        {
            cout << "\n\t\tEnter vehicle number to release car.. : ";
            cin >> optionData;
            releaseCar(homeCategory, optionData);
        }
        else
        {
            // If there is user then the vehicleNumwill be already fetched at login time
            releaseCar(homeCategory, vehicleNum);
        }
        break;
        
    case 4:
        cout << "\n\t\tThank You...";
        return;
    }
    return;
}

int main()
{
    int session = 0;
    fstream flogin;
    flogin.open("login.csv", ios::out | ios::app); // Creating CSV file for authentication
    flogin.close();
    title();
    category = "";

    session = login();

    return 0;
}