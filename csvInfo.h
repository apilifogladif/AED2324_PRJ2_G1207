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

    /**
     * @brief Default constructor
     */
    csvInfo();

    /**
     * @brief Adds all Airlines present in airlines.csv to a vector
     */
    static void createAirlinesVector();

    /**
     * @brief Adds all Airports present in airports.csv to a vector
     */
    static void createAirportsVector();

    /**
     * @brief Adds all Flights present in arlines.csv to a graph
     */
    static void createFlightsGraph();
};


#endif //AED2324_PRJ2_G1207_CSVINFO_H
