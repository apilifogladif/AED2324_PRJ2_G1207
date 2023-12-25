#include "csvInfo.h"

csvInfo::csvInfo() = default;

vector<Airline> csvInfo::airlinesVector;
vector<Airport> csvInfo::airportsVector;
Graph csvInfo::flightsGraph;

void csvInfo::createAirlinesVector() {
//    airlinesVector.clear();
//    file.open("../data/classes_per_uc.csv");
//    if (!file.is_open()) {
//        cerr << "Error: Unable to open the file." << endl;
//        return;
//    }
//    getline(file, line);
//    while(getline(file, line)) {
//        stringstream s(line);
//        getline(s, UcCode, ',');
//        getline(s, ClassCode);
//        if (UcCode == lastUcCode) {
//            classes.insert(ClassCode);
//        } else {
//            ClassesPerUcVector.emplace_back(lastUcCode, classes);
//            classes.clear();
//            classes.insert(ClassCode);
//        }
//        lastUcCode = UcCode;
//    }
}

void csvInfo::createAirportsVector() {

}

void csvInfo::createFlightsGraph() {

}