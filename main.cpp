#include <map>
#include "AuxiliarFunctions.h"

using namespace std;

void typeOfDestVector(const vector<Airport>& vecDest);

Airport verifyAirportCode(const string& code);
Airport verifyAirportName(const string& name);
Airline verifyAirlineCode(const string& code);
bool verifyCity(const string& name, const string& country);
bool verifyCountry(const string& name);
bool checkDigit(string num);
void clearMenus();

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

// global variables
map<std::string, int> m {{"main", 0}, {"getInfo", 1}, {"bestFlight", 2}, {"airportInfo", 3},
                         {"airlineInfo", 4}, {"cityInfo", 5}, {"countryInfo", 6},
                         {"globalInfo", 7}, {"destX", 8}};
stack<string> menus;
bool over = false;
bool quit = false;
Airport air_;

/**
 * @brief
 *
 * Complexity:
 *
 * @param vecDest :
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
 * @brief
 *
 * Complexity:
 *
 * @param code :
 * @return
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
 * @brief
 *
 * Complexity:
 *
 * @param name :
 * @return
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
 * @brief
 *
 * Complexity:
 *
 * @param code :
 * @return
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
 * @brief
 *
 * Complexity:
 *
 * @param name :
 * @param country :
 * @return
 */
bool verifyCity(const string& name, const string& country) {
    for (Airport a : csvInfo::airportsVector) {
        if (a.getCity() == name && a.getCountry() == country) return true;
    }
    return false;
}

/**
 * @brief
 *
 * Complexity:
 *
 * @param name :
 * @return
 */
bool verifyCountry(const string& name) {
    if (csvInfo::countriesSet.find(name) != csvInfo::countriesSet.end()) return true;
    return false;
}

/**
 * @brief
 *
 * Complexity:
 *
 * @param num :
 * @return
 */
bool checkDigit(string num) {
    for (auto c : num) {
        if (!isdigit(c)) return false;
    }
    return true;
}

/**
 * @brief
 *
 * Complexity:
 */
void clearMenus() {
    while (!menus.empty()) {
        menus.pop();
    }
}

/**
 * @brief
 *
 * Complexity:
 */
void mainMenu() {
    int op = 0;
    cout << endl << "----------------------------" << endl;
    cout << endl << "      Main Menu   " << endl;
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
 * @brief
 *
 * Complexity:
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
 * @brief
 *
 * Complexity:
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
 * @brief
 *
 * Complexity:
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
                    cout << v->getAdj().size() << " flights out of the airport." << endl;
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
 * @brief
 *
 * Complexity:
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

/**
 * @brief
 *
 * Complexity:
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

/**
 * @brief
 *
 * Complexity:
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

/**
 * @brief
 *
 * Complexity:
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
 * @brief
 *
 * Complexity:
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
    float latitude;
    float longitude;
    vector<Airport> sourceAirports;

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
                    while (true) {
                        cout << "Enter the name of the airport: ";
                        if (cin >> code) {
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
                    while (true) {
                        cout << "Enter the name of the country: ";
                        if (cin >> code) {
                            if (verifyCountry(code)) {
                                country = code;
                                break;  // Input is valid, exit the loop
                            }
                            else if (code == "q") {
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
                        if (cin >> code) {
                            if (verifyCity(code, country)) {
                                city = code;
                                break;  // Input is valid, exit the loop
                            }
                            else if (code == "q") {
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
                            if (to_string(stof(code)) == code) {
                                latitude = stof(code);
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
                            if (to_string(stof(code)) == code) {
                                longitude = stof(code);
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
    float Dlat;
    float Dlong;
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
                    while (true) {
                        cout << "Enter the name of the airport: ";
                        if (cin >> Dcode) {
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
                    while (true) {
                        cout << "Enter the name of the country: ";
                        if (cin >> Dcode) {
                            if (verifyCountry(Dcode)) {
                                Dcountry = Dcode;
                                break;  // Input is valid, exit the loop
                            }
                            else if (Dcode == "q") {
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
                        if (cin >> Dcode) {
                            if (verifyCity(Dcode, Dcountry)) {
                                Dcity = Dcode;
                                break;  // Input is valid, exit the loop
                            }
                            else if (Dcode == "q") {
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
                            if (to_string(stof(Dcode)) == Dcode) {
                                Dlat = stof(Dcode);
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
                            if (to_string(stof(Dcode)) == Dcode) {
                                Dlong = stof(Dcode);
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

    char opt;
    vector<vector<Airport>> answer;
    cout << endl << endl;
    cout << "Do you want to filter your search? (Y/N)" << endl;
    while (true) {
        if (cin >> opt) {
            if (opt == 'Y') {
                // answer = AuxiliarFunctions::bestFlightOpWFilters(sourceAirports, destAirports);
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

    // print flight options
    for (int i = 0; i < answer.size(); i++) {
        cout << "Option " << i << ": ";
        for (int a = 0; a < answer[i].size() - 1; a++) {
            cout << answer[i][a].getCode() << " -> ";
        }
        cout << answer[i][answer[i].size() - 1].getCode() << endl;
    }
}

/**
 * @brief
 *
 * Complexity:
 *
 * @return
 */
int main() {
    csvInfo::createAirportsVector();
    csvInfo::createAirlinesVector();
    csvInfo::createFlightsGraph();

    cout << "<<< SIZE >>>" << endl;
    cout << csvInfo::flightsGraph.getVertexSet().size() << endl;
    cout << csvInfo::airportsVector.size() << endl;
    cout << csvInfo::airlinesVector.size() << endl;
    int c = 0;
    for (auto v : csvInfo::flightsGraph.getVertexSet()) {
        c += v->getAdj().size();
    }
    cout << c << endl;
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
            cout << "3 - Quit." << endl;
            while (true) {
                cout << "Write the number of what you want to do: ";
                if (cin >> op) {
                    if (op == 1) break;
                    else if (op == 2) {
                        clearMenus();
                        menus.emplace("main");
                        break;
                    }
                    else if (op == 3) {
                        quit = true;
                        break;
                    }
                    else {
                        cout << "Invalid number! The number should be between 1 and 3." << endl;
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