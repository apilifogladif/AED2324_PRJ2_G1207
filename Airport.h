#ifndef AED2324_PRJ2_AIRPORT_H
#define AED2324_PRJ2_AIRPORT_H

#include <string>
#include <utility>
#include <unordered_set>
#include "Airport.h"
//#include "Graph.h"
#include <vector>
#include <iostream>

using namespace std;

class Airport {
private:
    string code;
    string name;
    string city;
    string country;
    float latitude;
    float longitude;
public:
    /**
     *
     * @brief Constructor of the Airport class
     * @param c Airport's code
     * @param n Airport's name
     * @param ci Airport's city
     * @param co Airport's country
     * @param la Airport's latitude
     * @param lo Airport's longitude
     */
    Airport(string c, string n, string ci, string co, float la, float lo);

    /**
     * @brief Get code of the Airport
     * @return Returns the value of the Airport's code
     */
    string getCode();

    /**
     * @brief Get name of the Airport
     * @return Returns the value of the Airport's name
     */
    string getName();

    /**
     * @brief Get city of the Airport
     * @return Returns the value of the Airport's city
     */
    string getCity();

    /**
     * @brief Get country of the Airport
     * @return Returns the value of the Airport's country
     */
    string getCountry();

    /**
     * @brief Get latitude of the Airport
     * @return Returns the value of the Airport's latitude
     */
    float getLatitude();

    /**
     * @brief Get longitude of the Airport
     * @return Returns the value of the Airport's longitude
     */
    float getLongitude();

    /**
     * @brief Get the number of flights from this airport
     * @return Number of flights
     */
    //int getNumberOfFlights(Graph &fg);

    /**
     * @brief Get the number of airlines operating at this airport
     * @return Number of airlines
     */
    //int getNumberOfAirlines(Graph &fg);

    /**
     * @brief Get the number of destinations from this airport
     * @return Number of destinations
     */
    //int getNumberOfDestinations(Graph &fg);

    /**
     * @brief Get reachable destinations within a maximum number of stops
     * @param maxStops Maximum number of stops
     * @return Vector of reachable destinations
     */
    //vector<Airport> getReachableDestinations(Graph &fg, int maxStops);

    /**
     * @brief Get reachable destinations within a maximum number of stops
     * @param fg Graph representing flights
     * @param source Source airport
     * @param maxStops Maximum number of stops
     * @param reachableDestinations Vector to store reachable destinations
     */
    //void dfsToFindReachableDestinations(Graph &fg, Airport &source, int maxStops, vector<Airport> &reachableDestinations);

};

#endif