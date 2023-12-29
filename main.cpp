#include <map>
#include "csvInfo.h"

using namespace std;

Airport verifyAirport(const string& code);
Airline verifyAirline(const string& code);
bool verifyCity(const string& name, const string& c);
bool verifyCountry(const string& name);
bool checkDigit(string num);
void clearMenus();

void mainMenu();
void getInfoMenu();
void airportMenu();
int main();
void getFlightMenu();
void airlineMenu();
void cityMenu();
void countryMenu();
void globalMenu();
void getFlightwFiltersMenu();

// global variables
map<std::string, int> m {{"main", 0}, {"getInfo", 1}, {"bestFlight", 2}, {"airportInfo", 3},
                         {"airlineInfo", 4}, {"cityInfo", 5}, {"countryInfo", 6},
                         {"globalInfo", 7}, {"destX", 8}, {"countriesX", 9}, {"flightFilters", 10}};
stack<string> menus;
bool over = false;
bool quit = false;

Airport airport = Airport("", "", "", "", 0, 0);
Airline airline = Airline("", "", "", "");

int typeOfDest(const set<Airport>& setDest) {
    int op = 0;
    cout << endl << "----------------------------------------" << endl;
    cout << endl << "  Number of which type of destination?  " << endl;
    cout << endl << "----------------------------------------" << endl;
    cout << "1 - Airports." << endl;
    cout << "2 - City." << endl;
    cout << "3 - Countries." << endl;

    set<string> aux;
    while (true) {
        cout << "Write the number of what you want to do: ";
        if (cin >> op) {
            switch (op) {
                case 1 :
                    return setDest.size();
                case 2:
                    for (auto i : setDest) {
                        if (aux.find(i.getCity() + i.getCountry()) == aux.end()) {
                            aux.insert(i.getCity() + i.getCountry());
                        }
                    }
                    return aux.size();
                case 3:
                    for (auto i : setDest) {
                        if (aux.find(i.getCountry()) == aux.end()) {
                            aux.insert(i.getCountry());
                        }
                    }
                    return aux.size();
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

Airport verifyAirport(const string& code) {
    Airport null = Airport("", "", "", "", 0, 0);
    for (Airport a : csvInfo::airportsVector) {
        if (a.getCode() == code) return a;
    }
    return null;
}

Airline verifyAirline(const string& code) {
    Airline null = Airline("", "", "", "");
    for (Airline a : csvInfo::airlinesVector) {
        if (a.getCode() == code) return a;
    }
    return null;
}

bool verifyCity(const string& name, const string& c) {
    for (Airport a : csvInfo::airportsVector) {
        if (a.getCity() == name && a.getCountry() == c) return true;
    }
    return false;
}

bool verifyCountry(const string& name) {
    if (csvInfo::countriesSet.find(name) != csvInfo::countriesSet.end()) return true;
    return false;
}

bool checkDigit(string num) {
    for (auto c : num) {
        if (!isdigit(c)) return false;
    }
    return true;
}

void clearMenus() {
    while (!menus.empty()) {
        menus.pop();
    }
}

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
    auto reachDests = csvInfo::flightsGraph.getReachableDestinations(airport, stops);
    cout << "There are " << reachDests.size() << " reachable destinations from " << airport.getName() << " with the maximum of " << stops << " stops." << endl;
    over = true;
}

void countriesX() {
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
    auto reachCountries = csvInfo::flightsGraph.getCountries(airport, stops);
    cout << "There are " << reachCountries.size() << " reachable destinations from " << airport.getName() << " with the maximum of " << stops << " stops." << endl;
    over = true;
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
    cout << endl << ap.getCode() << "; " << ap.getName() << "; " << ap.getCity() << "; " << ap.getCountry() << "; "<< ap.getLatitude() << "; " << ap.getLongitude() << endl;
    airport = ap;

    cout << "1 - Number of flights out of the airport." << endl;
    cout << "2 - Destinations in a maximum number of X stops." << endl;
    cout << "3 - Reachable countries in a maximum number of X stops." << endl;
    cout << "4 - Number of airlines with flights departing from this airport." << endl;
    cout << "0 - Return to last menu." << endl;

    Vertex* v;
    vector<Airline> airs;
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
                case 4:
                    airs = csvInfo::flightsGraph.getAirlines(airport);
                    cout << "There are " << airs.size() << " airlines with flights departing from this airport." << endl;
                    over = true;
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

void airlineMenu() {
    int op = 0;
    cout << endl << "-------------------------------------" << endl;
    cout << endl << "   Get information about an airline  " << endl;
    cout << endl << "-------------------------------------" << endl;

    string code;
    Airline air = Airline("", "", "", "");
    while (true) {
        cout << "Enter the code of the airline: ";
        if (cin >> code) {
            air = verifyAirline(code);
            if (!air.getCode().empty()) {
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

    cout << endl << air.getCode() << "; " << air.getName() << "; " << air.getCountry() << endl;
    cout << "1 - Number of flights." << endl;
    cout << "2 - Destinations." << endl;
    cout << "0 - Return to last menu." << endl;

    set<Airport> dest;
    while (true) {
        cout << "Write the number of what you want to do: ";
        if (cin >> op) {
            switch (op) {
                case 1 :
                    cout << csvInfo::flightsGraph.getNumberOfFlights(air) << " flights." << endl;
                    over = true;
                    return;
                case 2:
                    dest = csvInfo::flightsGraph.getNumberOfDestinations(air);
                    cout << dest.size() << " destinations." << endl;
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
    cout << "2 - Airlines with airplanes stopping in airports of the city." << endl;
    cout << "3 - Destinations from airports of the city." << endl;
    cout << "4 - Airports in the city." << endl;
    cout << "5 - Reachable destinations in a maximum number of X stops." << endl;
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
                    cout << reachDests.size() << " Reachable destinations in a maximum number of " << stops << " stops." << endl;
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
    cout << "6 - Reachable destinations in a maximum number of X stops." << endl;
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
                    cout << reachDests.size() << " Reachable destinations in a maximum number of " << stops << " stops." << endl;
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

void globalMenu() {
    int op = 0;
    cout << endl << "-------------------------------------" << endl;
    cout << endl << "        Get global information       " << endl;
    cout << endl << "-------------------------------------" << endl;
    cout << "1 - Number of flights." << endl;
    cout << "2 - Number of airlines." << endl;
    cout << "3 - Number of airports." << endl;
    cout << "4 -Number of cities." << endl;
    cout << "5 -Number of countries." << endl;
    cout << "0 - Return to last menu." << endl;

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
                    cout << csvInfo::flightsGraph.getTotalNumberOfAirlines() << " airlines." << endl;
                    over = true;
                    return;
                case 5:
                    cout << csvInfo::flightsGraph.getTotalNumberOfCities() << " cities." << endl;
                    over = true;
                    return;
                case 6:
                    cout << csvInfo::flightsGraph.getTotalNumberOfCountries() << " countries." << endl;
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

// TODO
void getFlightMenu() {
    int op = 0;
    cout << endl << "-------------------------------------" << endl;
    cout << endl << "          Best flight option         " << endl;
    cout << endl << "-------------------------------------" << endl;
    cout << "Where are you departing from?" << endl;
    cout << "1 - Airport code." << endl;
    cout << "2 - Airport name." << endl;
    cout << "3 - City name." << endl;
    cout << "4 - Coordinates." << endl;
    cout << "0 - Exit." << endl;

}

// TODO
void flightFiltersMenu() {
    int op = 0;
    cout << endl << "-------------------------------------" << endl;
    cout << endl << "       Best flight option ...        " << endl;
    cout << endl << "-------------------------------------" << endl;
    cout << "Where are you departing from?" << endl;
    cout << "1 - with filters." << endl;
    cout << "2 - without filters." << endl;
    cout << "0 - Exit." << endl;
}

int main() {
    csvInfo::createAirportsVector();
    csvInfo::createAirlinesVector();
    csvInfo::createFlightsGraph();

    cout << "<<< SIZE >>>" << endl;
    cout << csvInfo::flightsGraph.getVertexSet().size() << endl;
    cout << csvInfo::airportsVector.size() << endl;
    cout << csvInfo::airlinesVector.size() << endl;

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
            case 9:
                countriesX();
                menus.pop();
                break;
            case 10:
                flightFiltersMenu();
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