// Name: Kenny Lee Yuan Hong
// Student ID: 0125942

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <limits>

#pragma warning(disable : 4996)

using namespace std;

int i = 0;
int dependentSIZE = 5;

struct Address {
    string hseAddress, hseNumber, city, state;
    int postcode;
};

struct Dependent {
    string name, relation, gender, icNum;
    int age;
};

struct User {
    string name, gender, icNum, phoneNum;
    int age;
    Address address;
    Dependent dependent[5];
};

struct History {
    string location, name, phoneNum;
    char* dateTime;

    History* nxtHistory;
} *top;

void displayMenu() {
    system("cls");
    cout << "=================================\n" << endl;
    cout << "      Welcome to sejahteraMy!\n" << endl;
    cout << "=================================\n" << endl;

    cout << "[Enter -1 to stop the application]\n" << endl;
    cout << "1. Check-in" << endl;
    cout << "2. View history" << endl;
    cout << "3. Add dependent" << endl;
    cout << "4. View dependent" << endl;
    cout << "Enter selection: ";
}

void regUser(User*& u) { // register user ==========================================================
    cout << "Name: ";
    getline(cin, u->name, '\n');

    do
    {
        cout << "Gender(M/F): ";
        cin >> u->gender;
        if (u->gender == "m" || u->gender == "M") {
            cout << "Male!" << endl;
            u->gender = "Male";
        }
        else if (u->gender == "f" || u->gender == "F") {
            cout << "Female!" << endl;
            u->gender = "Female";
        }
        else
        {
            cout << "Error! Only input M or F" << endl;
        }
    } while (u->gender != "Female" && u->gender != "Male");

    cout << "IC number: ";
    cin.ignore();
    getline(cin, u->icNum, '\n');

    cout << "Age: ";
    cin >> u->age;

    cout << "Phone Number: ";
    cin >> u->phoneNum;

    cout << "House Address: ";
    cin.ignore();
    getline(cin, u->address.hseAddress, '\n');

    cout << "House Number: ";
    cin.ignore();
    getline(cin, u->address.hseNumber, '\n');

    cout << "City: ";
    cin.ignore();
    getline(cin, u->address.city, '\n');

    cout << "State: ";
    cin.ignore();
    getline(cin, u->address.state, '\n');

    cout << "Postcode: ";
    cin >> u->address.postcode;
}

void push(History* &h, User* &u) // check-in ======================================================
{
    h = new History;
    time_t now = time(0);
    char* dt = ctime(&now);

    cout << "\n+++ Check-in +++" << endl;
    cout << "Where are you entering?" << endl;
    cin.ignore();
    getline(cin, h->location, '\n');
    h->name = u->name;
    h->phoneNum = u->phoneNum;
    h->dateTime = dt;
    h->nxtHistory = NULL;

    h->nxtHistory = top;
    top = h;

    cout << "\nThank you for checking in. Your information have been recorded. You may view them on history." << endl;
    _sleep(3000);

}

void display() // view history ====================================================================
{
    cout << "\n--- Your history ---\n";
    if (top == NULL)
    {
        cout << "History is empty :(. Start going places!" << endl;
        return;
    }

    History* navi = top;
    
    while (navi != NULL)
    {
        cout << "Location: " << navi-> location << endl;
        cout << "Name: " << navi-> name << endl;
        cout << "Phone Number: " << navi-> phoneNum << endl;
        cout << "Date and Time: " << navi-> dateTime << endl;
        navi = navi->nxtHistory;
    }

    _sleep(3000);
}

void addDependent(User*& u) { // add dependent ======================================================
    cout << "\n*** Add dependents ***\n";
    cout << "You have selected to add dependent. Please enter the details as follow." << endl;
    cout << "Name: ";
    cin.ignore();
    getline(cin, u->dependent[i].name, '\n');

    cout << "Relation(e.g. Mother, Son, etc.): ";
    getline(cin, u->dependent[i].relation, '\n');

    do
    {
        cout << "Gender(M/F): ";
        cin >> u->dependent[i].gender;
        if (u->dependent[i].gender == "m" || u->dependent[i].gender == "M") {
            u->dependent[i].gender = "Male";
        }
        else if (u->dependent[i].gender == "f" || u->dependent[i].gender == "F") {
            u->dependent[i].gender = "Female";
        }
        else
        {
            cout << "Error! Only input M or F" << endl;
        }
    } while (u->dependent[i].gender != "Female" && u->dependent[i].gender != "Male");

    cout << "IC Number: ";
    cin.ignore();
    getline(cin, u->dependent[i].icNum, '\n');

    cout << "Age: ";
    cin >> u->dependent[i].age;

    i++;

    cout << "\n\nYou have successfully added a dependent under your wing!" << endl;
    _sleep(3000);
}

void removeDependent(User*& u) { // remove dependent ========================================================

}

void viewDependent(User*& u) { // view depedent ========================================================

    cout << "\n\n^^^ View Dependents ^^^\n\n";

    size_t n = sizeof(u->dependent) / sizeof(u->dependent[0]);

    for (int i = 0; i < n; i++){
        cout << "Dependent " << i+1 << endl;
        cout << "Name: " << u->dependent[i].name << endl;
        cout << "Relation: " << u->dependent[i].relation << endl;
        cout << "Gender: " << u->dependent[i].gender << endl;
        cout << "IC Number: " << u->dependent[i].icNum << endl;
        cout << "Age: " << u->dependent[i].age << endl << endl;
    }

    _sleep(3000);
}

int main() { // main function ====================================================================
    History* historyNode = new History();
    User* userNode = new User();
    int option = 0;
    char opt;

    cout << "Hello there, welcome! Kindly register yourself in the application as follows." << endl;
    regUser(userNode);

    do {

        displayMenu();

        cin >> option;

        switch (option) {

        case 1: // Check-in
            push(historyNode, userNode);
            break;

        case 2: // View history
            display();    

            cout << endl;
            system("pause");
            break;

        case 3: // Add dependent
            if (i < 5) {
                addDependent(userNode);
                system("pause");
            }
            else
            {
                cout << "\nSorry but you have reached the limit of 5 dependents per user :(" << endl;
                system("pause");
            }
            break;

        case 4: // View dependent
            viewDependent(userNode);
            system("pause");
            break;

        case -1:
            cout << "You have chosen to exit the program, goodbye!" << endl;
            exit(0);
            break;

        default:
            cout << "\nPlease enter only the numbers shown!" << endl;
            _sleep(3000);
        }
    } while (option != -1);
}