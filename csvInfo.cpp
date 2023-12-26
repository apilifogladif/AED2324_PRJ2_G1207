#include "csvInfo.h"

csvInfo::csvInfo() = default;

vector<Airline> csvInfo::airlinesVector;
vector<Airport> csvInfo::airportsVector;
Graph csvInfo::flightsGraph;

void csvInfo::createAirlinesVector() {
    airlinesVector.clear();
    fstream file;
    file.open("../data/airlines.csv");
    if (!file.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return;
    }
    string line;
    getline(file, line);
    string code;
    string name;
    string callsign;
    string country;
    while(getline(file, line)) {
        stringstream s(line);
        getline(s, code, ',');
        getline(s, name, ',');
        getline(s, callsign, ',');
        getline(s, country);
        Airline airline = Airline(code, name, callsign, country);
        airlinesVector.push_back(airline);
    }
    file.close();
}

void csvInfo::createAirportsVector() {
    airportsVector.clear();
    fstream file;
    file.open("../data/airports.csv");
    if (!file.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return;
    }
    string line;
    getline(file, line);
    string code;
    string name;
    string city;
    string country;
    string latitude;
    string longitude;
    while(getline(file, line)) {
        stringstream s(line);
        getline(s, code, ',');
        getline(s, name, ',');
        getline(s, city, ',');
        getline(s, country, ',');
        getline(s, latitude, ',');
        getline(s, longitude);
        Airport airport = Airport(code, name, city, country, stof(latitude), stof(longitude));
        airportsVector.push_back(airport);
        flightsGraph.addVertex(airport);
    }
    file.close();
}

void csvInfo::createFlightsGraph() {
    flightsGraph.clean();
    fstream file;
    file.open("../data/flights.csv");
    if (!file.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return;
    }
    string line;
    getline(file, line);
    string source;
    string dest;
    string airline;

    while(getline(file, line)) {
        stringstream s(line);
        getline(s, source, ',');
        getline(s, dest, ',');
        getline(s, airline);
        Airline al = Airline("", "", "", "");
        for (auto a : airlinesVector) {
            if (a.getCode() == airline) {
                al = a;
                break;
            }
        }
        flightsGraph.addEdge(source, dest, al);
    }
    file.close();
}