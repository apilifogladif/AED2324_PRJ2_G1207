#ifndef AED2324_PRJ2_G1207_CSVINFO_H
#define AED2324_PRJ2_G1207_CSVINFO_H

#include "Graph.h"
#include <fstream>
#include <sstream>

/**
 * @brief Gets the info from the csv's.
 */
class csvInfo {
private:
public:
    /**
     * Vector of all the airlines
     */
    static vector<Airline> airlinesVector;

    /**
     * Vector of all the airports
     */
    static vector<Airport> airportsVector;

    /**
     * Set of all the cities
     */
    static set<string> citiesSet;

    /**
     * Set of all the countries
     */
    static set<string> countriesSet;

    /**
     * Graph of all the flights
     */
    static Graph flightsGraph;

    /**
     * @brief Default constructor
     */
    csvInfo();

    /**
     * @brief Adds all airlines present in airlines.csv to a vector
     */
    static void createAirlinesVector();

    /**
     * @brief Adds all airports present in airports.csv to a vector
     */
    static void createAirportsVector();

    /**
     * @brief Adds all flights present in flights.csv to a graph
     */
    static void createFlightsGraph();
};


#endif //AED2324_PRJ2_G1207_CSVINFO_H
