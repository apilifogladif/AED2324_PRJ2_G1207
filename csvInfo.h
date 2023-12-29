#ifndef AED2324_PRJ2_G1207_CSVINFO_H
#define AED2324_PRJ2_G1207_CSVINFO_H

#include "Graph.h"
#include <fstream>
#include <sstream>

class csvInfo {
private:
public:
    static vector<Airline> airlinesVector;
    static vector<Airport> airportsVector;
    static set<string> citiesSet;
    static set<string> countriesSet;
    static Graph flightsGraph;

    csvInfo();
    static void createAirlinesVector();
    static void createAirportsVector();
    static void createFlightsGraph();
};


#endif //AED2324_PRJ2_G1207_CSVINFO_H
