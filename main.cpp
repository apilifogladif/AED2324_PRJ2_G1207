#include <iostream>
#include <stack>
#include <map>
#include "csvInfo.h"

using namespace std;

void mainMenu();
void getInfoMenu();
void airportMenu();
int main();

Airport verifyAirport(const string& code);

// global variables
map<std::string, int> m {{"main", 0}, {"getInfo", 1}, {"getFlight", 2}, {"airportInfo", 3},
                         {"airlineInfo", 4}, {"cityInfo", 5}, {"countryInfo", 6},
                         {"globalInfo", 7}};
stack<string> menus;
bool over = false;

Airport verifyAirport(const string& code) {
    Airport null = Airport("", "", "", "", 0, 0);
    for (Airport a : csvInfo::airportsVector) {
        if (a.getCode() == code) return a;
    }
    return null;
}

void mainMenu() {
    int op = 0;
    cout << endl << "----------------------------" << endl;
    cout << endl << "      Main Menu   " << endl;
    cout << endl << "----------------------------" << endl;
    cout << "1 - Get information about..." << endl; // airport, airline, city, country, global
    cout << "2 - Get flight..." << endl;
    // To an airport, city, country, airlines, origin
    cout << "3 - Others... " << endl;
    // Reachable airports with X max flights
    // Reachable cities with X max flights
    // Reachable countries with X max flights
    // Maximum trip
    // Top K airport with the greatest air traffic capacity
    // Essential airports
    cout << "0 - Exit." << endl;
    while (true) {
        cout << "Write the number of what you want to do: ";
        if (cin >> op) {
            switch (op) {
                case 1 :
                    menus.emplace("getInfo");
                    return;
                case 2:
                    menus.emplace("getFlight");
                    return;
                case 0:
                    menus.pop();
                    return;
                default:
                    cout << "Invalid number! The number should be between 1 and 6." << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }
}

void getInfoMenu() {
    int op = 0;
    cout << endl << "-----------------------------" << endl;
    cout << endl << "   Get information about...  " << endl;
    cout << endl << "-----------------------------" << endl;
    cout << "1 - an airport." << endl;
    cout << "2 - an airline." << endl;
    cout << "3 - a city." << endl;
    cout << "4 - a country." << endl;
    cout << "5 - a global." << endl;
    cout << "6 - Return to last menu." << endl;

    while (true) {
        cout << "Write the number of what you want to do: ";
        if (cin >> op) {
            switch (op) {
                case 1 :
                    menus.emplace("airportInfo");
                    return;
                case 2:
                    menus.emplace("airlineInfo");
                    return;
                case 3:
                    menus.emplace("cityInfo");
                    return;
                case 4:
                    menus.emplace("countryInfo");
                    return;
                case 5:
                    menus.emplace("globalInfo");
                    return;
                case 6:
                    menus.pop();
                    return;
                default:
                    cout << "Invalid number! The number should be between 1 and 6." << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }
}

void airportMenu() {
    int op = 0;
    cout << endl << "-------------------------------------" << endl;
    cout << endl << "   Get information about an airport  " << endl;
    cout << endl << "-------------------------------------" << endl;

    string code;
    Airport ap = Airport("", "", "", "", 0, 0);
    while (true) {
        cout << "Enter the code of the airport: ";
        if (cin >> code) {
            ap = verifyAirport(code);
            if (!ap.getCode().empty()) {
                break;  // Input is valid, exit the loop
            }
            else if (code == "q") return;
            else {
                cout << "Invalid Airport Code!" << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid Airport Code." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }
    cout << endl << ap.getCode() << "; " << ap.getName() << "; " << ap.getCity() << "; " << ap.getCountry() << "; "<< ap.getLatitude() << "; " << ap.getLongitude() << endl;

    cout << "1 - number of flights out of the airport." << endl;
    cout << "2 - destinations in a maximum number of X stops." << endl;
    cout << "3 - reachable countries." << endl;
    cout << "0 - Return to last menu." << endl;

    Vertex* v;
    while (true) {
        cout << "Write the number of what you want to do: ";
        if (cin >> op) {
            switch (op) {
                case 1 :
                    v = csvInfo::flightsGraph.findVertex(ap);
                    cout << v->getAdj().size() << " flights out of the airport." << endl;
                    over = true;
                    return;
                case 2:
                    menus.emplace("destX");
                    return;
                case 3:
                    menus.emplace("countriesX");
                    return;
                case 0:
                    menus.pop();
                    return;
                default:
                    cout << "Invalid number! The number should be between 1 and 5." << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }
}

int main() {
    menus.emplace("main");
    while (true) {
        string next = menus.top();
        switch (m.at(next)) {
            case 0:
                mainMenu();
                if (menus.empty()) system("exit");
                break;
            case 1:
                getInfoMenu();
                break;
            default:
                system("exit");
        }
        if (over) {
            int op = 0;
            cout << endl;
            cout << "1 - Return to last Menu" << endl;
            cout << "2 - Return to Main Menu" << endl;
            cout << "3 - Quit." << endl;
            while (true) {
                cout << "Write the number of what you want to do: ";
                if (cin >> op) {
                    if (op == 1) break;
                    else if (op == 2) {
                        menus.pop();
                        break;
                    }
                    else if (op == 3) system("exit");
                    else {
                        cout << "Invalid number! The number should be between 1 and 3." << endl;
                    }
                } else {
                    cout << "Invalid input! Please enter a valid number." << endl;
                    cin.clear();          // Clear the error state
                    cin.ignore(INT_MAX, '\n'); // Ignore the invalid input
                }
            }
            over = false;
        }
    }
}


// Airport
// Number of flights
// Number of airlines
// Number of destinations
// Reachable destinations in a maximum number of X stops

// Airline
// Number of flights
// Number of destinations

// City
// Number of flights
// Number of airports
// Number of airlines
// Number of destinations
// Reachable destinations in a maximum number of X stops

// Country
// Number of flights
// Number of airports
// Number of airlines
// Number of destinations
// Number of cities
// Reachable destinations in a maximum number of X stops

// Global
// Number of flights
// Number of airports
// Number of airlines
// Number of countries
// Number of cities
// Reachable destinations in a maximum number of X stops