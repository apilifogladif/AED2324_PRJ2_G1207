/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstddef>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <algorithm>
#include <unordered_map>
#include "Airlines.h"
#include "Airport.h"
#include <utility>

using namespace std;

class Edge;
class Graph;
class Vertex;


/****************** Provided structures  ********************/

/**
 * @brief Represents a Vertex in the graph.
 */
class Vertex {
    Airport airport;       // contents
    vector<Edge> adj;      // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;       // auxiliary field
    int num;               // auxiliary field
    int low;               // auxiliary field

    /**
     * Auxiliary function to add an outgoing edge to a vertex (this),
     * with a given destination vertex (d) and edge weight (w).
     * @param d : Vertex
     * @param airline_ : Airline
     */
    void addEdge(Vertex *d, Airline airline_);

    /**
     * Auxiliary function to remove an outgoing edge (with a given destination (d))
     * from a vertex (this).
     * Returns true if successful, and false if such edge does not exist.
     *
     * @param d : Vertex
     * @return True or False
     */
    bool removeEdgeTo(Vertex *d);
public:
    /**
     * @brief Constructor for Vertex class.
     *
     * Complexity: O(1)
     *
     * @param in Airport object to be associated with the vertex.
     */
    Vertex(Airport in);

    // Getter and setter methods for Vertex properties

    /**
     * @brief Returns the Airport
     *
     * @return Airport
     */
    Airport getAirport() const;

    /**
     * @brief Checks if an vertex was visited - auxiliary field
     *
     * @return True of false
     */
    bool isVisited() const;

    /**
     * @brief Sets the visited to true or false - auxiliary field
     *
     * @param v : True or False
     */
    void setVisited(bool v);


    /**
     * @brief Checks if an vertex is processing - auxiliary field
     *
     * @return True of false
     */
    bool isProcessing() const;

    /**
     * @brief Sets processing to true or false - auxiliary field
     *
     * @param v : True or False
     */
    void setProcessing(bool p);

    /**
     * Return the outgoing edges
     *
     * @return Outgoing edges vector
     */
    const vector<Edge> &getAdj() const;


    /**
     * @brief Returns the Number - auxiliary field
     *
     * @return Number
     */
    int getNum() const;

    /**
     * @brief Sets num - auxiliary field
     *
     * @param num : Number
     */
    void setNum(int num);

    /**
     * @brief Returns the low - auxiliary field
     *
     * @return Low int
     */
    int getLow() const;

    /**
     * @brief Sets low - auxiliary field
     *
     * @param low : Low int
     */
    void setLow(int low);

    friend class Graph;
};

/**
 * @brief Represents an Edge connecting two vertices in the graph.
 */
class Edge {
    Vertex* dest;         // destination vertex
    set<Airline> airline; // set of airlines
public:
    /**
     * @brief Constructor for Edge class.
     *
     * Complexity: 0(1)
     *
     * @param d : Destination vertex.
     * @param airline_ : Airline associated with the edge.
     */
    Edge(Vertex* d, Airline airline_);

    // Getter and setter methods for Edge properties
    /**
     * @brief Returns the destination vertex
     *
     * @return Destination vertex
     */
    Vertex* getDest() const;

    /**
     * @brief Returns the airline
     *
     * @return Airline
     */
    set<Airline> getAirline() const;


    friend class Graph;
    friend class Vertex;
};

/**
 * @brief Represents a graph.
 */
class Graph {
    vector<Vertex*> vertexSet;       // vertex set
    stack<Vertex> _stack_;           // auxiliary field
    list<list<Airport>> _list_sccs_; // auxiliary field


public:
    friend class AuxiliarFunctions;
    /**
     * @brief Finds a vertex with the given airport in the graph.
     *
     * Complexity: 0(n)
     *
     * @param in : Airport to find.
     * @return Pointer to the found vertex or nullptr if not found.
     */
    Vertex *findVertex(const Airport& in) const;

    /**
     * @brief Finds a vertex with the given code in the graph.
     *
     * Complexity: O(n)
     *
     * @param in : Code of the airport to find.
     * @return Pointer to the found vertex or nullptr if not found.
     */
    Vertex *findVertex(string in) const;

    /**
     * @brief Adds a vertex with a given airport to the graph.
     *
     * Complexity: O(1)
     *
     * @param in : Airport to add.
     * @return True if the vertex is added successfully, false otherwise.
     */
    bool addVertex(const Airport &in);

    /**
     * @brief Removes a vertex with a given airport from the graph.
     *
     * Complexity: O(n^2)
     *
     * @param in : Airport to remove.
     * @return True if the vertex is removed successfully, false otherwise.
     */
    bool removeVertex(const Airport& in);

    /**
     * @brief Adds an edge to the graph.
     *
     * Complexity: O(n)
     *
     * @param sourc : Source airport code.
     * @param dest : Destination airport code.
     * @param airline : Airline associated with the edge.
     * @return True if the edge is added successfully, false otherwise.
     */
    bool addEdge(const string &sourc, const string &dest, Airline airline);

    /**
     * @brief Gets the vector of vertices in the graph.
     *
     * Complexity: O(1)
     *
     * @return Vector of vertices.
     */
    vector<Vertex*> getVertexSet() const;

    /**
     * @brief Performs a depth-first search (dfs) in the graph from a specific source airport.
     *
     * Complexity: O(n^3)
     *
     * @param source : Source airport.
     * @param dest : Destination airport.
     * @param path : Path between both airports.
     * @param airlines : Vector with the airlines that can be used.
     * @return True if there is a path, otherwise returns false.
     */
    vector<vector<Vertex*>> bfsPathFilterAirlines(Vertex* source, Vertex* dest, vector<string> airlines) const;

    /**
     * @brief Performs a depth-first search (dfs) in the graph from a specific source airport.
     *
     * Complexity: O(n^3)
     *
     * @param source : Source airport.
     * @param dest : Destination airport.
     * @param path : Path between both airports.
     * @param NumAir : Number of airlines that can be used.
     * @param air : Vector with the airlines that are being used.
     * @return True if there is a path, otherwise returns false.
     */
    vector<pair<vector<Vertex*>,int>> bfsPathFilterNumAir(Vertex* source, Vertex* dest, int NumAir, set<Airline> air);

    /**
     * @brief Cleans the graph by removing all vertices and edges.
     *
     * Complexity: O(n)
     */
    void clean();

    /**
     * @brief Gets the reachable destinations from a source airport within a given number of stops.
     *
     * Complexity: O(n)
     *
     * @param source : The source airport.
     * @param maxStops : The maximum number of stops allowed.
     * @return Vector of airports representing the reachable destinations.
     */
    vector<Airport> getReachableDestinations(const Airport& source, int maxStops) const;

    /**
     * @brief Performs a depth-first search to find reachable destinations within a given number of stops.
     *
     * Complexity: O(n)
     *
     * @param v : The current vertex being explored.
     * @param stopsLeft : The remaining number of stops allowed.
     * @param reachableDestinations : Vector to store the reachable destinations.
     */
    void dfsReachableDestinations(Vertex* v, int stopsLeft, vector<Airport>& reachableDestinations) const;

    /**
     * @brief Gets the number of flights associated with the given airline.
     *
     * Complexity: O(n^3)
     *
     * @param airline : The airline for which to retrieve the number of flights.
     * @return The number of flights associated with the airline.
     */
    int getNumberOfFlights(const Airline& airline) const;

    /**
     * @brief Gets the number of destinations served by the given airline.
     *
     * Complexity: O(n^2)
     *
     * @param airline : The airline for which to retrieve the number of destinations.
     * @return A vector of destinations served by the airline.
     */
    vector<Airport> getNumberOfDestinations(const Airline& airline) const;


    /**
     * @brief Gets the number of flights associated with the given city.
     *
     * Complexity: O(n^2)
     *
     * @param city : The city for which to retrieve the number of flights.
     * @param country : The country of the city.
     * @return The number of flights associated with the city.
     */
    int getNumberOfFlightsInCity(const string& city, const string& country) const;

    /**
     * @brief Gets the number of airports in the specified city.
     *
     * Complexity: O(n)
     *
     * @param city : The city for which to retrieve the number of airports.
     * @param country : The country of the city.
     * @return The number of unique airports in the city.
     */
    int getNumberOfAirportsInCity(const string& city, const string& country) const;

    /**
     * @brief Gets the airports in the specified city.
     *
     * Complexity: O(n)
     *
     * @param city : The city for which to retrieve the number of airports.
     * @param country : The country of the city.
     * @return The vector of unique airports in the city.
     */
    vector<Airport> getAirportsInCity(const string& city, const string& country) const;

    /**
     * @brief Gets the number of unique airlines operating in the specified city.
     *
     * Complexity: O(n^3)
     *
     * @param city : The city for which to retrieve the number of unique airlines.
     * @param country : The country of the city.
     * @return The number of unique airlines operating in the city.
     */
    int getNumberOfAirlinesInCity(const string& city, const string& country) const;

    /**
     * @brief Gets the total number of unique destinations served by airports in the specified city.
     *
     * Complexity: O(n^2)
     *
     * @param city : The city for which to retrieve the total number of destinations.
     * @param country : The country of the city.
     * @return The total number of unique destinations served by airports in the city.
     */
    int getTotalDestinationsInCity(const string& city, const string& country) const;

    /**
     * @brief Gets the reachable destinations from airports in the specified city within a given number of stops.
     *
     * Complexity: O(n)
     *
     * @param city : The city for which to retrieve the reachable destinations.
     * @param country : The country of the city.
     * @param maxStops : The maximum number of stops allowed.
     * @return Vector of airports representing the reachable destinations.
     */
    vector<Airport> getReachableDestinationsInCity(const string& city, const string& country, int maxStops) const;

    /**
     * @brief Gets the total number of flights departing from airports in the specified country.
     *
     * Complexity: O(n^2)
     *
     * @param country : The country for which to retrieve the number of flights.
     * @return The total number of flights departing from airports in the country.
     */
    int getNumberOfFlightsInCountry(const string& country) const;

    /**
     * @brief Gets the number of airports in the specified country.
     *
     * Complexity: O(n)
     *
     * @param country : The country for which to retrieve the number of airports.
     * @return The number of airports in the country.
     */
    int getNumberOfAirportsInCountry(const string& country) const;

    /**
     * @brief Gets the number of unique airlines operating in the specified country.
     *
     * Complexity: O(n^3)
     *
     * @param country : The country for which to retrieve the number of airlines.
     * @return The number of unique airlines in the country.
     */
    int getNumberOfAirlinesInCountry(const string& country) const;

    /**
     * @brief Gets the total number of unique destinations in the specified country.
     *
     * Complexity: O(n^2)
     *
     * @param country : The country for which to retrieve the number of destinations.
     * @return The total number of unique destinations in the country.
     */
    int getTotalDestinationsInCountry(const string& country) const;

    /**
     * @brief Gets the number of unique cities in the specified country.
     *
     * Complexity: O(n)
     *
     * @param country : The country for which to retrieve the number of cities.
     * @return The number of unique cities in the country.
     */
    int getNumberOfCitiesInCountry(const string& country) const;

    /**
     * @brief Gets the reachable destinations in the specified country within a given number of stops.
     *
     * Complexity: O(n)
     *
     * @param country : The country of interest.
     * @param maxStops : The maximum number of stops allowed.
     * @return Vector of airports representing the reachable destinations.
     */
    vector<Airport> getReachableDestinationsInCountry(const string& country, int maxStops) const;

    /**
     * @brief Gets the total number of flights in the graph.
     *
     * Complexity: O(n^2)
     *
     * @return The total number of flights in the graph.
     */
    int getTotalNumberOfFlights() const;

    /**
     * @brief Gets the total number of airports in the graph.
     *
     * Complexity: O(1)
     *
     * @return The total number of airports in the graph.
     */
    int getTotalNumberOfAirports() const;

    /**
     * @brief Gets the total number of unique airlines operating in the graph.
     *
     * Complexity: O(n^3)
     *
     * @return The total number of unique airlines operating in the graph.
     */
    int getTotalNumberOfAirlines() const;

    /**
     * @brief Gets the total number of unique countries in the graph.
     *
     * Complexity: O(n)
     *
     * @return The total number of unique countries in the graph.
     */
    int getTotalNumberOfCountries() const;

    /**
     * @brief Gets the total number of unique cities in the graph.
     *
     * Complexity: O(n)
     *
     * @return The total number of unique cities in the graph.
     */
    int getTotalNumberOfCities() const;

    /**
     * @brief Gets a vector of airlines associated with a specific airport.
     *
     * Complexity: O(n^2)
     *
     * @param airport : The airport for which to retrieve the associated airlines.
     * @return A vector of Airline objects representing the airlines associated with the airport.
     */
    vector<Airline> getAirlines(const Airport& airport);

    /**
     * @brief Gets the top airports based on the number of flights.
     *
     * Complexity: O(n)
     *
     * @param k : The number of top airports to retrieve.
     * @return A vector of pairs representing the top airports and their respective number of flights.
     */
    vector<pair<Airport, int>> getTopKAirports(int k) const;

    /**
     * @brief Finds the maximum stops trip and corresponding source-destination airport pairs, using breadth-first search (BFS)
     * The result is printed to the terminal.
     *
     * Complexity: O(n^3)
     */
    void findMaxStopsTrip();

    /**
     * @brief Gets airports closest to the specified coordinates.
     *
     * Complexity: O(n)
     *
     * @param lat : Latitude of the target location in degrees.
     * @param longi : Longitude of the target location in degrees.
     * @return Vector of airports closest to the specified coordinates.
     */
    vector<Airport> getAirportsInCoordinates(double lat, double longi) const;

    /**
     * @brief Finds a path between two airports in the graph using depth-first search (DFS).
     *
     * Complexity: O(n)
     *
     * @param s : Source airport.
     * @param d : Destination airport.
     * @return Vector of airports representing the path from source to destination.
     */
    vector<vector<Vertex*>> pathAirport(const Airport& s, const Airport& d);

    /**
     * @brief Finds a path between two airports in the graph using depth-first search (DFS).
     *
     * Complexity: O(n)
     *
     * @param s : Source airport.
     * @param d : Destination airport.
     * @param airlines : Vector with the airlines that can be used.
     * @return Vector of vectors of airports representing the path from source to destination.
     */
    vector<vector<Vertex*>> pathAirportRestrictAirlines(const Airport& s, const Airport& d, const vector<string>& airlines);

    /**
     * @brief Finds a path between two airports in the graph using depth-first search (DFS).
     *
     * Complexity: O(n)
     *
     * @param s : Source airport.
     * @param d : Destination airport.
     * @param NumAir : Number of airlines that can be used.
     * @return Vector of airports representing the path from source to destination.
     */
    vector<pair<vector<Vertex*>,int>> pathAirportNumAirlines(const Airport& s, const Airport& d, int NumAir);

    /**
     * @brief Find the best paths using bfs
     *
     * Complexity: O(n^2)
     *
     * @param source : Source vertex
     * @param dest : Destination vertex
     * @return Paths
     */
    vector<vector<Vertex*>> bfsPath(Vertex* source, Vertex *dest) const;

    /**
     * @brief Return the number of flights out an airport
     *
     * Complexity: O(n)
     *
     * @param airport : Airport
     * @return Number of flights out the given airport
     */
    int getNumberOfFlights(const Airport &airport) const;
};

#endif /* GRAPH_H_ */