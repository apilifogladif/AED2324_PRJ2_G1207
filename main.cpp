#include <map>
#include <chrono>
#include "AuxiliarFunctions.h"

using namespace std;

/**
 * @file main.cpp
 *
 * @mainpage AED project2
 * @section intro_sec Introduction
 * This project was made in the context of the Algorithms and Data Structures class.
 *
 * The aim of this project is  is precisely to develop a flight management system for the air travel network
 * of the airlines around the world that provides effective assistance to users
 * who wish to explore and plan travel.
 *
 * The system must include various functionalities such as searching information about an airport, an airline, a city,
 * a country or general information. The system also allows the user to search the best flight option
 * between two airports, cities or coordinates with or without using a filter.
 *
 *
 * This project was made by: Filipa Geraldes, Filipa Fidalgo and Leonor Couto.
 */

void typeOfDestVector(const vector<Airport>& vecDest);

Airport verifyAirportCode(const string& code);
Airport verifyAirportName(const string& name);
Airline verifyAirlineCode(const string& code);
bool verifyCity(const string& name, const string& country);
bool verifyCountry(const string& name);
bool checkDigit(string num);
void clearMenus();
void chooseAirlines();
void chooseNumAir();
int filters();
void mainMenu();
void getInfoMenu();
void destX();
void airportMenu();
int main();
void getFlightMenu();
void airlineMenu();
void cityMenu();
void countryMenu();
void globalMenu();

/**
 * Global variable
 */
map<std::string, int> m {{"main", 0}, {"getInfo", 1}, {"bestFlight", 2}, {"airportInfo", 3},
                         {"airlineInfo", 4}, {"cityInfo", 5}, {"countryInfo", 6},
                         {"globalInfo", 7}, {"destX", 8}};
stack<string> menus;
bool over = false;
bool quit = false;
Airport air_;

// filters
vector<string> airlines;
int numAir;

/**
 * @brief Checks if the airport code has an airport associated
 *
 * Complexity: O(n)
 *
 * @param code : Airport code
 * @return The airport corresponding to the airport code
 */
Airport verifyAirportCode(const string& code) {
    Airport airport;
    for (Airport a : csvInfo::airportsVector) {
        if (a.getCode() == code) {
            airport = a;
            break;
        }
    }
    return airport;
}

/**
 * @brief Checks if the airport name has an airport associated
 *
 * Complexity: O(n)
 *
 * @param name : Airport name
 * @return The airport corresponding to the airport name given
 */
Airport verifyAirportName(const string& name) {
    Airport airport;
    for (Airport a : csvInfo::airportsVector) {
        if (a.getName() == name) {
            airport = a;
            break;
        }
    }
    return airport;
}

/**
 * @brief Checks if the airline code has an airline associated
 *
 * Complexity: O(n)
 *
 * @param code : Airline code
 * @return The airline corresponding to the airline code given
 */
Airline verifyAirlineCode(const string& code) {
    Airline airline;
    for (Airline a : csvInfo::airlinesVector) {
        if (a.getCode() == code) {
            airline = a;
            break;
        }
    }
    return airline;
}

/**
 * @brief Checks if the city exists in the airports vector
 *
 * Complexity: O(n)
 *
 * @param name : City name
 * @param country : Country name
 * @return True or False
 */
bool verifyCity(const string& name, const string& country) {
    for (Airport a : csvInfo::airportsVector) {
        if (a.getCity() == name && a.getCountry() == country) return true;
    }
    return false;
}

/**
 * @brief Checks if the country exists in the countries set
 *
 * Complexity: O(1)
 *
 * @param name : Country name
 * @return True or False
 */
bool verifyCountry(const string& name) {
    if (csvInfo::countriesSet.find(name) != csvInfo::countriesSet.end()) return true;
    return false;
}

/**
 * @brief Checks if given input is made of all digits
 *
 * Complexity: O(n)
 *
 * @param num : String to check
 * @return True or False
 */
bool checkDigit(string num) {
    for (auto c : num) {
        if (!isdigit(c)) return false;
    }
    return true;
}

/**
 * @brief Clears all the menus
 *
 * Complexity: O(n)
 */
void clearMenus() {
    while (!menus.empty()) {
        menus.pop();
    }
}

/**
 * @brief Menu to choose an Airline
 *
 * Complexity: O(n)
 */
void chooseAirlines() {
    cout << endl << "-----------------------------------------" << endl;
    cout << endl << "     Write the code of the airlines      " << endl;
    cout << endl << "  (Enter q to save the set of airlines)  " << endl;
    cout << endl << "-----------------------------------------" << endl;
    string code;
    Airline airline;
    int i = 1;
    while (true) {
        cout << i << ": ";
        if (cin >> code) {
            airline = verifyAirlineCode(code);
            if (!airline.getCode().empty()) {
                airlines.push_back(airline.getCode());
                i++;
                continue;  // Input is valid, exit the loop
            }
            else if (code == "q") {
                break;
            }
            else {
                cout << "Invalid Airline Code!" << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid Airline Code." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }
}

/**
 * @brief Menu to choose the number of Airlines
 *
 * Complexity: O(n)
 */
void chooseNumAir() {
    int op = 0;
    cout << endl << "------------------------------" << endl;
    cout << endl << "     Maximum of airlines      " << endl;
    cout << endl << "------------------------------" << endl;
    while (true) {
        cout << "Write the number: ";
        if (cin >> op) {
            if (op <= 444) {
                numAir = op;
                break;
            }
            else {
                cout << "There are only 444 airlines. Enter a valid number." << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }
}

/**
 * @brief Main Menu
 *
 * Complexity: O(n)
 */
void mainMenu() {
    int op = 0;
    cout << endl << "----------------------------" << endl;
    cout << endl << "         Main Menu          " << endl;
    cout << endl << "----------------------------" << endl;
    cout << "1 - Get information about..." << endl; // airport, airline, city, country, global
    cout << "2 - Best flight option..." << endl;
    cout << "0 - Exit." << endl;
    while (true) {
        cout << "Write the number of what you want to do: ";
        if (cin >> op) {
            switch (op) {
                case 1 :
                    menus.emplace("getInfo");
                    return;
                case 2:
                    menus.emplace("bestFlight");
                    return;
                case 0:
                    quit = true;
                    return;
                default:
                    cout << "Invalid number! The number should be between 0 and 2." << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }
}

/**
 * @brief Menu to choose the type of filter
 *
 * Complexity: O(n)
 *
 * @return An int depending on the menu the user chooses
 */
// 0 -> return to bestFlightOpMenu; 1 -> vector of airlines; 2 -> number of airlines
int filters() {
    int op = 0;
    cout << endl << "-----------------------------" << endl;
    cout << endl << "    Select type of filter    " << endl;
    cout << endl << "-----------------------------" << endl;
    cout << "1 - Choose airlines." << endl;
    cout << "2 - Choose number of different airlines." << endl;
    cout << "0 - Return to last menu." << endl;
    while (true) {
        cout << "Write the number of what you want to do: ";
        if (cin >> op) {
            switch (op) {
                case 1 :
                    chooseAirlines();
                    return 1;
                case 2:
                    chooseNumAir();
                    return 2;
                case 0:
                    return 0;
                default:
                    cout << "Invalid number! The number should be between 0 and 2." << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }
}

/**
 * @brief Menu to choose the type of destination
 *
 * Complexity: O(n^2)
 *
 * @param vecDest : The destinations vector
 */
void typeOfDestVector(const vector<Airport>& vecDest) {
    int op = 0;
    cout << endl << "----------------------------------------" << endl;
    cout << endl << "  Number of which type of destination?  " << endl;
    cout << endl << "----------------------------------------" << endl;
    cout << "1 - Airports." << endl;
    cout << "2 - Cities." << endl;
    cout << "3 - Countries." << endl;

    set<string> aux;
    while (true) {
        cout << "Write the number of what you want to do: ";
        if (cin >> op) {
            switch (op) {
                case 1 :
                    cout << vecDest.size() << " airports.";
                    return;
                case 2:
                    for (auto i : vecDest) {
                        if (aux.find(i.getCity() + i.getCountry()) == aux.end()) {
                            aux.insert(i.getCity() + i.getCountry());
                        }
                    }
                    cout << aux.size() << " cities.";
                    return;
                case 3:
                    for (auto i : vecDest) {
                        if (aux.find(i.getCountry()) == aux.end()) {
                            aux.insert(i.getCountry());
                        }
                    }
                    cout << aux.size() << " countries.";
                    return              ;
                default:
                    cout << "Invalid number! The number should be between 1 and 3." << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }
}

/**
 * @brief Menu to get information
 *
 * Complexity: O(n)
 */
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
    cout << "0 - Return to last menu." << endl;

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
                case 0:
                    menus.pop();
                    return;
                default:
                    cout << "Invalid number! The number should be between 0 and 5." << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }
}

/**
 * @brief Gets the number of maximum of stops the user chooses
 *
 * Complexity: O(n)
 */
void destX() {
    string X;
    while (true) {
        cout << "Which is the maximum of stops? ";
        if (cin >> X) {
            if (X == "q") {
                menus.pop();
                return;
            }
            else if (checkDigit(X)) {
                break;  // Input is valid, exit the loop
            }
            else {
                cout << stoi(X) << endl;
                cout << "Invalid number of stops!" << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid number of stops." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }

    int stops = stoi(X);
    auto reachDests = csvInfo::flightsGraph.getReachableDestinations(air_, stops);
    typeOfDestVector(reachDests);
    over = true;
}

/**
 * @brief Menu to get information about an airport
 *
 * Complexity: O(n)
 */
void airportMenu() {
    int op = 0;
    cout << endl << "-------------------------------------" << endl;
    cout << endl << "   Get information about an airport  " << endl;
    cout << endl << "-------------------------------------" << endl;

    string code;
    Airport airport;
    while (true) {
        cout << "Enter the code of the airport: ";
        if (cin >> code) {
            airport = verifyAirportCode(code);
            if (!airport.getCode().empty()) {
                break;  // Input is valid, exit the loop
            }
            else if (code == "q") {
                menus.pop();
                return;
            }
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
    cout << endl << airport.getCode() << "; " << airport.getName() << "; " << airport.getCity() << "; " << airport.getCountry() << "; "<< airport.getLatitude() << "; " << airport.getLongitude() << endl;
    air_ = airport;

    cout << "1 - Number of flights out of the airport." << endl;
    cout << "2 - Number of reachable destinations in a maximum number of X stops." << endl;
    cout << "3 - Number of airlines with flights departing from this airport." << endl;
    cout << "0 - Return to last menu." << endl;

    Vertex* v;
    vector<Airline> airs;
    while (true) {
        cout << "Write the number of what you want to do: ";
        if (cin >> op) {
            switch (op) {
                case 1 :
                    v = csvInfo::flightsGraph.findVertex(airport);
                    cout << csvInfo::flightsGraph.getNumberOfFlights(airport) << " flights out of the airport." << endl;
                    over = true;
                    return;
                case 2:
                    menus.emplace("destX");
                    return;
                case 3:
                    airs = csvInfo::flightsGraph.getAirlines(airport);
                    cout << "There are " << airs.size() << " airlines with flights departing from this airport." << endl;
                    over = true;
                    return;
                case 0:
                    menus.pop();
                    return;
                default:
                    cout << "Invalid number! The number should be between 0 and 3." << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }
}

/**
 * @brief Menu to get information about an airline
 *
 * Complexity: O(n)
 */
void airlineMenu() {
    int op = 0;
    cout << endl << "-------------------------------------" << endl;
    cout << endl << "   Get information about an airline  " << endl;
    cout << endl << "-------------------------------------" << endl;

    string code;
    Airline airline;
    while (true) {
        cout << "Enter the code of the airline: ";
        if (cin >> code) {
            airline = verifyAirlineCode(code);
            if (!airline.getCode().empty()) {
                break;  // Input is valid, exit the loop
            }
            else if (code == "q") {
                menus.pop();
                return;
            }
            else {
                cout << "Invalid Airline Code!" << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid Airline Code." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }

    cout << endl << airline.getCode() << "; " << airline.getName() << "; " << airline.getCountry() << endl;
    cout << "1 - Number of flights." << endl;
    cout << "2 - Number of destinations." << endl;
    cout << "0 - Return to last menu." << endl;

    vector<Airport> dest;
    while (true) {
        cout << "Write the number of what you want to do: ";
        if (cin >> op) {
            switch (op) {
                case 1 :
                    cout << csvInfo::flightsGraph.getNumberOfFlights(airline) << " flights." << endl;
                    over = true;
                    return;
                case 2:
                    dest = csvInfo::flightsGraph.getNumberOfDestinations(airline);
                    typeOfDestVector(dest);
                    over = true;
                    return;
                case 0:
                    menus.pop();
                    return;
                default:
                    cout << "Invalid number! The number should be between 0 and 2." << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }
}

/**
 * @brief Menu to get information about an city
 *
 * Complexity: O(n)
 */
void cityMenu() {
    int op = 0;
    cout << endl << "-------------------------------------" << endl;
    cout << endl << "    Get information about a city     " << endl;
    cout << endl << "-------------------------------------" << endl;

    string country;
    getline(cin, country);
    while (true) {
        cout << "Enter the name of the country: ";
        if (getline(cin, country)) {
            if (verifyCountry(country)) {
                break;  // Input is valid, exit the loop
            }
            else if (country == "q") {
                menus.pop();
                return;
            }
            else {
                cout << "Invalid country name!" << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid country name." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }

    string city;
    while (true) {
        cout << "Enter the name of the city: ";
        if (getline(cin, city)) {
            if (verifyCity(city, country)) {
                break;  // Input is valid, exit the loop
            }
            else if (city == "q") {
                menus.pop();
                return;
            }
            else {
                cout << "Invalid city name!" << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid city name." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }
    cout << endl << city << "; " << country << endl;
    cout << "1 - Number of flights out of the city." << endl;
    cout << "2 - Number of airlines with airplanes stopping in airports of the city." << endl;
    cout << "3 - Number of destinations from airports of the city." << endl;
    cout << "4 - Number of airports in the city." << endl;
    cout << "5 - Number of reachable destinations in a maximum number of X stops." << endl;
    cout << "0 - Return to last menu." << endl;

    set<Airport> dest;
    string X;
    vector<Airport> reachDests;
    int stops;
    while (true) {
        cout << "Write the number of what you want to do: ";
        if (cin >> op) {
            switch (op) {
                case 1 :
                    cout << csvInfo::flightsGraph.getNumberOfFlightsInCity(city, country) << " flights." << endl;
                    over = true;
                    return;
                case 2 :
                    cout << csvInfo::flightsGraph.getNumberOfAirlinesInCity(city, country) << " airlines." << endl;
                    over = true;
                    return;
                case 3 :
                    cout << csvInfo::flightsGraph.getTotalDestinationsInCity(city, country) << " destinations from airports of the city." << endl;
                    over = true;
                    return;
                case 4 :
                    cout << csvInfo::flightsGraph.getNumberOfAirportsInCity(city, country) << " airports." << endl;
                    over = true;
                    return;
                case 5 :
                    while (true) {
                        cout << "Which is the maximum of stops? ";
                        if (cin >> X) {
                            if (X == "q") {
                                menus.pop();
                                return;
                            }
                            else if (checkDigit(X)) {
                                break;  // Input is valid, exit the loop
                            }
                            else {
                                cout << stoi(X) << endl;
                                cout << "Invalid number of stops!" << endl;
                            }
                        }
                        else {
                            cout << "Invalid input! Please enter a valid number of stops." << endl;
                            cin.clear();          // Clear the error state
                            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
                        }
                    }

                    stops = stoi(X);
                    reachDests = csvInfo::flightsGraph.getReachableDestinationsInCity(city, country, stops);
                    typeOfDestVector(reachDests);
                    over = true;
                    return;
                case 0:
                    menus.pop();
                    return;
                default:
                    cout << "Invalid number! The number should be between 0 and 5." << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }
}

/**
 * @brief Menu to get information about a country
 *
 * Complexity: O(n^2)
 */
void countryMenu() {
    int op = 0;
    cout << endl << "-------------------------------------" << endl;
    cout << endl << "   Get information about a country   " << endl;
    cout << endl << "-------------------------------------" << endl;

    string country;
    getline(cin, country);
    while (true) {
        cout << "Enter the name of the country: ";
        if (getline(cin, country)) {
            if (verifyCountry(country)) {
                break;  // Input is valid, exit the loop
            }
            else if (country == "q") {
                menus.pop();
                return;
            }
            else {
                cout << "Invalid country name!" << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid country name." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }

    cout << "1 - Number of flights out of the country." << endl;
    cout << "2 - Number of airlines with airplanes stopping in airports of the country." << endl;
    cout << "3 - Number of destinations from airports of the country." << endl;
    cout << "4 - Number of airports in the country." << endl;
    cout << "5 - Number of cities in the country." << endl;
    cout << "6 - Number of reachable destinations in a maximum number of X stops." << endl;
    cout << "0 - Return to last menu." << endl;

    string X;
    vector<Airport> reachDests;
    int stops;
    while (true) {
        cout << "Write the number of what you want to do: ";
        if (cin >> op) {
            switch (op) {
                case 1 :
                    cout << csvInfo::flightsGraph.getNumberOfFlightsInCountry(country) << " flights out of the country." << endl;
                    over = true;
                    return;
                case 2 :
                    cout << csvInfo::flightsGraph.getNumberOfAirlinesInCountry(country) << " airlines in the country." << endl;
                    over = true;
                    return;
                case 3 :
                    cout << csvInfo::flightsGraph.getTotalDestinationsInCountry(country) << " destinations." << endl;
                    over = true;
                    return;
                case 4 :
                    cout << csvInfo::flightsGraph.getNumberOfAirportsInCountry(country) << " airports in the country." << endl;
                    over = true;
                    return;
                case 5 :
                    cout << csvInfo::flightsGraph.getNumberOfCitiesInCountry(country) << " cities in the country." << endl;
                    over = true;
                    return;
                case 6 :
                    while (true) {
                        cout << "Which is the maximum of stops? ";
                        if (cin >> X) {
                            if (X == "q") {
                                menus.pop();
                                return;
                            }
                            else if (checkDigit(X)) {
                                break;  // Input is valid, exit the loop
                            }
                            else {
                                cout << stoi(X) << endl;
                                cout << "Invalid number of stops!" << endl;
                            }
                        }
                        else {
                            cout << "Invalid input! Please enter a valid number of stops." << endl;
                            cin.clear();          // Clear the error state
                            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
                        }
                    }

                    stops = stoi(X);
                    reachDests = csvInfo::flightsGraph.getReachableDestinationsInCountry(country, stops);
                    typeOfDestVector(reachDests);
                    over = true;
                    return;
                case 0:
                    menus.pop();
                    return;
                default:
                    cout << "Invalid number! The number should be between 0 and 6." << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }
}

/**
 * @brief Menu to get global information
 *
 * Complexity: O(n^2)
 */
void globalMenu() {
    int op = 0;
    cout << endl << "-------------------------------------" << endl;
    cout << endl << "        Get global information       " << endl;
    cout << endl << "-------------------------------------" << endl;
    cout << "1 - Number of flights." << endl;
    cout << "2 - Number of airlines." << endl;
    cout << "3 - Number of airports." << endl;
    cout << "4 - Number of cities." << endl;
    cout << "5 - Number of countries." << endl;
    cout << "6 - The flight trips with the greatest number of stops in between them." << endl;
    cout << "7 - Top-k airports with the greatest air traffic capacity." << endl;
    cout << "8 - Airports that are essential to the network’s circulation capability." << endl;
    cout << "0 - Return to last menu." << endl;

    vector<pair<Airport, int>> aux;
    string X;
    int k;
    int i;
    vector<Airport> articulationPoints;
    while (true) {
        cout << "Write the number of what you want to do: ";
        if (cin >> op) {
            switch (op) {
                case 1 :
                    cout << csvInfo::flightsGraph.getTotalNumberOfFlights() << " flights." << endl;
                    over = true;
                    return;
                case 2:
                    cout << csvInfo::flightsGraph.getTotalNumberOfAirlines() << " airlines." << endl;
                    over = true;
                    return;
                case 3:
                    cout << csvInfo::flightsGraph.getTotalNumberOfAirports() << " airports." << endl;
                    over = true;
                    return;
                case 4:
                    cout << csvInfo::flightsGraph.getTotalNumberOfCities() << " cities." << endl;
                    over = true;
                    return;
                case 5:
                    cout << csvInfo::flightsGraph.getTotalNumberOfCountries() << " countries." << endl;
                    over = true;
                    return;
                case 6:
                    csvInfo::flightsGraph.findMaxStopsTrip();
                    over = true;
                    return;
                case 7:
                    while (true) {
                        cout << "How many do you want to be shown? ";
                        if (cin >> X) {
                            if (X == "q") {
                                menus.pop();
                                return;
                            }
                            else if (checkDigit(X)) {
                                break;  // Input is valid, exit the loop
                            }
                            else {
                                cout << "Invalid number!" << endl;
                            }
                        }
                        else {
                            cout << "Invalid input! Please enter a valid number." << endl;
                            cin.clear();          // Clear the error state
                            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
                        }
                    }
                    k = stoi(X);
                    aux = csvInfo::flightsGraph.getTopKAirports(k);
                    cout << "Top " << X << ": " << endl;
                    i = 1;
                    for (auto a : aux) {
                        cout << i << " - " << a.first.getCode() << ";" << a.first.getName() << "; " << a.first.getCity() << "; " << a.first.getCountry() << endl;
                        i++;
                    }
                    over = true;
                    return;
                case 8:
                    cout << "Essential airports: ";
                    articulationPoints = AuxiliarFunctions::articulationPoints(&csvInfo::flightsGraph);
                    cout << "(" << articulationPoints.size() << " airports)" << endl;
                    over = true;
                    return;
                case 0:
                    menus.pop();
                    return;
                default:
                    cout << "Invalid number! The number should be between 0 and 8." << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }
}

/**
 * @brief Menu to get information about a flight
 *
 * Complexity: O(n^3)
 */
void getFlightMenu() {
    int op = 0;
    cout << endl << "-------------------------------------" << endl;
    cout << endl << "          Best flight option         " << endl;
    cout << endl << "-------------------------------------" << endl;

    // SOURCE

    cout << "Where are you departing from?" << endl;
    cout << "1 - Airport code." << endl;
    cout << "2 - Airport name." << endl;
    cout << "3 - City name." << endl;
    cout << "4 - Coordinates." << endl;
    cout << "0 - Exit." << endl;

    string input = "";
    bool o = false;

    // source values
    string code;
    Airport airport;
    string city;
    string country;
    double latitude;
    double longitude;
    vector<Airport> sourceAirports;
    size_t pos = 0;

    while (true) {
        cout << "Write the number of what you want to do: ";
        if (cin >> op) {
            switch (op) {
                case 1 :
                    while (true) {
                        cout << "Enter the code of the airport: ";
                        if (cin >> code) {
                            airport = verifyAirportCode(code);
                            if (airport.getCode() == code) {
                                break;  // Input is valid, exit the loop
                            }
                            else if (code == "q") {
                                menus.pop();
                                return;
                            }
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
                    sourceAirports.push_back(airport);
                    o = true;
                    break;
                case 2:
                    getline(cin, code);
                    while (true) {
                        cout << "Enter the name of the airport: ";
                        if (getline(cin, code)) {
                            airport = verifyAirportName(code);
                            if (airport.getName() == code) {
                                break;  // Input is valid, exit the loop
                            }
                            else if (code == "q") {
                                menus.pop();
                                return;
                            }
                            else {
                                cout << "Invalid Airport Name!" << endl;
                            }
                        }
                        else {
                            cout << "Invalid input! Please enter a valid Airport Name." << endl;
                            cin.clear();          // Clear the error state
                            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
                        }
                    }
                    sourceAirports.push_back(airport);
                    o = true;
                    break;
                case 3:
                    getline(cin, country);
                    while (true) {
                        cout << "Enter the name of the country: ";
                        if (getline(cin, country)) {
                            if (verifyCountry(country)) {
                                break;  // Input is valid, exit the loop
                            }
                            else if (country == "q") {
                                menus.pop();
                                return;
                            }
                            else {
                                cout << "Invalid country name!" << endl;
                            }
                        }
                        else {
                            cout << "Invalid input! Please enter a valid country name." << endl;
                            cin.clear();          // Clear the error state
                            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
                        }
                    }

                    while (true) {
                        cout << "Enter the name of the city: ";
                        if (getline(cin, city)) {
                            if (verifyCity(city, country)) {
                                break;  // Input is valid, exit the loop
                            }
                            else if (city == "q") {
                                menus.pop();
                                return;
                            }
                            else {
                                cout << "Invalid city name!" << endl;
                            }
                        }
                        else {
                            cout << "Invalid input! Please enter a valid city name." << endl;
                            cin.clear();          // Clear the error state
                            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
                        }
                    }
                    sourceAirports = csvInfo::flightsGraph.getAirportsInCity(city, country);
                    o = true;
                    break;
                case 4:
                    while (true) {
                        cout << "Enter the latitude: ";
                        if (cin >> code) {
                            stod(code, &pos);
                            if (pos == code.length()) {
                                latitude = stod(code);
                                break;  // Input is valid, exit the loop
                            }
                            else if (code == "q") {
                                menus.pop();
                                return;
                            }
                            else {
                                cout << "Invalid number!" << endl;
                            }
                        }
                        else {
                            cout << "Invalid input! Please enter a valid number." << endl;
                            cin.clear();          // Clear the error state
                            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
                        }
                    }
                    while (true) {
                        cout << "Enter the longitude: ";
                        if (cin >> code) {
                            stod(code, &pos);
                            if (pos == code.length()) {
                                longitude= stod(code);
                                break;  // Input is valid, exit the loop
                            }
                            else if (code == "q") {
                                menus.pop();
                                return;
                            }
                            else {
                                cout << "Invalid number!" << endl;
                            }
                        }
                        else {
                            cout << "Invalid input! Please enter a valid number." << endl;
                            cin.clear();          // Clear the error state
                            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
                        }
                    }
                    sourceAirports = csvInfo::flightsGraph.getAirportsInCoordinates(latitude, longitude);
                    o = true;
                    break;
                case 0:
                    menus.pop();
                    return;
                default:
                    cout << "Invalid number! The number should be between 0 and 4." << endl;
            }
            if (o) break;
        }
        else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }

    for(auto a : sourceAirports){
        cout << endl << a.getCode() << "; " << a.getName() << "; " << a.getCity() << "; " << a.getCountry() << "; " << a.getLatitude() << "; " << a.getLongitude();
    }
    cout <<  endl;

    // DESTINATION

    cout << endl << endl;
    cout << "Where are you going to?" << endl;
    cout << "1 - Airport code." << endl;
    cout << "2 - Airport name." << endl;
    cout << "3 - City name." << endl;
    cout << "4 - Coordinates." << endl;
    cout << "0 - Exit." << endl;

    o = false;

    // destination values
    string Dcode;
    Airport Dairport;
    string Dcity;
    string Dcountry;
    double Dlat;
    double Dlong;
    vector<Airport> destAirports;

    while (true) {
        cout << "Write the number of what you want to do: ";
        if (cin >> op) {
            switch (op) {
                case 1 :
                    while (true) {
                        cout << "Enter the code of the airport: ";
                        if (cin >> Dcode) {
                            Dairport = verifyAirportCode(Dcode);
                            if (Dairport.getCode() == Dcode) {
                                break;  // Input is valid, exit the loop
                            }
                            else if (Dcode == "q") {
                                menus.pop();
                                return;
                            }
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
                    destAirports.push_back(Dairport);
                    o = true;
                    break;
                case 2:
                    getline(cin,Dcode);
                    while (true) {
                        cout << "Enter the name of the airport: ";
                        if (getline(cin, Dcode)) {
                            Dairport = verifyAirportName(Dcode);
                            if (Dairport.getName() == Dcode) {
                                break;  // Input is valid, exit the loop
                            }
                            else if (Dcode == "q") {
                                menus.pop();
                                return;
                            }
                            else {
                                cout << "Invalid Airport Name!" << endl;
                            }
                        }
                        else {
                            cout << "Invalid input! Please enter a valid Airport Name." << endl;
                            cin.clear();          // Clear the error state
                            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
                        }
                    }
                    destAirports.push_back(Dairport);
                    o = true;
                    break;
                case 3:
                    getline(cin, Dcountry);
                    while (true) {
                        cout << "Enter the name of the country: ";
                        if (getline(cin, Dcountry)) {
                            if (verifyCountry(Dcountry)) {
                                break;  // Input is valid, exit the loop
                            }
                            else if (Dcountry == "q") {
                                menus.pop();
                                return;
                            }
                            else {
                                cout << "Invalid country name!" << endl;
                            }
                        }
                        else {
                            cout << "Invalid input! Please enter a valid country name." << endl;
                            cin.clear();          // Clear the error state
                            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
                        }
                    }

                    while (true) {
                        cout << "Enter the name of the city: ";
                        if (getline(cin, Dcity)) {
                            if (verifyCity(Dcity, Dcountry)) {
                                break;  // Input is valid, exit the loop
                            }
                            else if (Dcity == "q") {
                                menus.pop();
                                return;
                            }
                            else {
                                cout << "Invalid city name!" << endl;
                            }
                        }
                        else {
                            cout << "Invalid input! Please enter a valid city name." << endl;
                            cin.clear();          // Clear the error state
                            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
                        }
                    }
                    destAirports = csvInfo::flightsGraph.getAirportsInCity(Dcity, Dcountry);
                    o = true;
                    break;
                case 4:
                    while (true) {
                        cout << "Enter the latitude: ";
                        if (cin >> Dcode) {
                            stod(Dcode, &pos);
                            if (pos == Dcode.length()) {
                                Dlat= stod(Dcode);
                                break;  // Input is valid, exit the loop
                            }
                            else if (Dcode == "q") {
                                menus.pop();
                                return;
                            }
                            else {
                                cout << "Invalid number!" << endl;
                            }
                        }
                        else {
                            cout << "Invalid input! Please enter a valid number." << endl;
                            cin.clear();          // Clear the error state
                            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
                        }
                    }
                    while (true) {
                        cout << "Enter the longitude: ";
                        if (cin >> Dcode) {
                            stod(Dcode, &pos);
                            if (pos == Dcode.length()) {
                                Dlong= stod(Dcode);
                                break;  // Input is valid, exit the loop
                            }
                            else if (Dcode == "q") {
                                menus.pop();
                                return;
                            }
                            else {
                                cout << "Invalid number!" << endl;
                            }
                        }
                        else {
                            cout << "Invalid input! Please enter a valid number." << endl;
                            cin.clear();          // Clear the error state
                            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
                        }
                    }
                    destAirports = csvInfo::flightsGraph.getAirportsInCoordinates(Dlat, Dlong);
                    o = true;
                    break;
                case 0:
                    menus.pop();
                    return;
                default:
                    cout << "Invalid number! The number should be between 0 and 4." << endl;
            }
            if (o) break;
        }
        else {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }

    for(auto b : destAirports){
        cout << endl << b.getCode() << "; " << b.getName() << "; " << b.getCity() << "; " << b.getCountry() << "; " << b.getLatitude() << "; " << b.getLongitude();
    }
    cout <<  endl;

    char opt;
    vector<vector<Airport>> answer;
    cout << endl << endl;
    cout << "Do you want to filter your search? (Y/N)" << endl;
    while (true) {
        if (cin >> opt) {
            if (opt == 'Y') {
                op = filters();
                if (op == 0) return;
                if (op == 1)
                    answer = AuxiliarFunctions::filterVectorAirlines(sourceAirports, destAirports, airlines);
                if (op == 2)
                    answer = AuxiliarFunctions::filterNumAirlines(sourceAirports, destAirports, numAir);
                break;  // Input is valid, exit the loop
            }
            else if (opt == 'N') {
                answer = AuxiliarFunctions::bestFlightOp(sourceAirports, destAirports);
                break;  // Input is valid, exit the loop
            }
            else if (opt == 'q') {
                menus.pop();
                return;
            }
            else {
                cout << "Invalid character!" << endl;
            }
        }
        else {
            cout << "Invalid input! Please enter a valid character." << endl;
            cin.clear();          // Clear the error state
            cin.ignore(INT_MAX , '\n'); // Ignore the invalid input
        }
    }

    over = true;

    // print flight options
    if (answer.empty()) {
        cout << "There are no flights connecting the source and the destination";
        if (opt == 'Y') cout << " with the filters you chose." << endl;
        else cout << "." << endl;
        return;
    }
    for (int i = 0; i < answer.size(); i++) {
        cout << "Option " << i + 1 << ": ";
        for (int a = 0; a < answer[i].size() - 1; a++) {
            cout << answer[i][a].getCode() << " -> ";
        }
        cout << answer[i][answer[i].size() - 1].getCode() << endl;
    }
}

/**
 * @brief Main function to initialize data and run the program.
 *
 * Complexity: O(n)
 *
 * @return Program exit status.
 */
int main() {
    auto start = chrono::high_resolution_clock::now();
    csvInfo::createAirportsVector();
    csvInfo::createAirlinesVector();
    csvInfo::createFlightsGraph();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> dif = end - start;
    cout << dif.count() << " seconds" << endl;

    menus.emplace("main");
    while (true) {
        string next = menus.top();
        switch (m.at(next)) {
            case 0:
                mainMenu();
                break;
            case 1:
                getInfoMenu();
                break;
            case 2:
                getFlightMenu();
                break;
            case 3:
                airportMenu();
                break;
            case 4:
                airlineMenu();
                break;
            case 5:
                cityMenu();
                break;
            case 6:
                countryMenu();
                break;
            case 7:
                globalMenu();
                break;
            case 8:
                destX();
                menus.pop();
                break;
            default:
                quit = true;
        }
        if (over) {
            int op = 0;
            cout << endl;
            cout << "1 - Return to last Menu" << endl;
            cout << "2 - Return to Main Menu" << endl;
            cout << "0 - Exit." << endl;
            while (true) {
                cout << "Write the number of what you want to do: ";
                if (cin >> op) {
                    if (op == 1) break;
                    else if (op == 2) {
                        clearMenus();
                        menus.emplace("main");
                        break;
                    }
                    else if (op == 0) {
                        quit = true;
                        break;
                    }
                    else {
                        cout << "Invalid number! The number should be between 0 and 2." << endl;
                    }
                }
                else {
                    cout << "Invalid input! Please enter a valid number." << endl;
                    cin.clear();          // Clear the error state
                    cin.ignore(INT_MAX, '\n'); // Ignore the invalid input
                }
            }
            over = false;
        }
        if (quit) break;
    }
    system("exit");
}