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
    Airport airport;                // contents
    vector<Edge> adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;       // auxiliary field
    int indegree;          // auxiliary field
    int num;               // auxiliary field
    int low;               // auxiliary field

    void addEdge(Vertex *d, Airline airline_);
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

    Airport getAirport() const;
    void setAirport(Airport in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const vector<Edge> &getAdj() const;
    void setAdj(const vector<Edge> &adj);
    int getIndegree() const;
    void setIndegree(int indegree);
    int getNum() const;
    void setNum(int num);
    int getLow() const;
    void setLow(int low);

    friend class Graph;
};

/**
 * @brief Represents an Edge connecting two vertices in the graph.
 */
class Edge {
    Vertex* dest;      // destination vertex
    Airline airline;         // edge weight
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

    Vertex* getDest() const;
    void setDest(Vertex* dest);
    Airline getAirline() const;
    void setAirline(Airline airline_);

    friend class Graph;
    friend class Vertex;
};

/**
 * @brief Represents a graph.
 */
class Graph {
    vector<Vertex*> vertexSet;      // vertex set
    int _index_;                        // auxiliary field
    stack<Vertex> _stack_;           // auxiliary field
    list<list<Airport>> _list_sccs_;        // auxiliary field

    void dfsVisit(Vertex *v,  vector<Airport> & res) const;
    bool dfsIsDAG(Vertex *v) const;
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
    Vertex *findVertex(Airport in) const;

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
     * @brief Gets the number of vertices in the graph.
     *
     * Complexity: O(1)
     *
     * @return Number of vertices.
     */
    int getNumVertex() const;

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
    bool removeVertex(Airport in);

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
     * @brief Removes an edge from the graph.
     *
     * Complexity: O(n)
     *
     * @param sourc : Source airport.
     * @param dest : Destination airport.
     * @return True if the edge is removed successfully, false otherwise.
     */
    bool removeEdge(const Airport &sourc, const Airport &dest);

    /**
     * @brief Gets the vector of vertices in the graph.
     *
     * Complexity: O(1)
     *
     * @return Vector of vertices.
     */
    vector<Vertex*> getVertexSet() const;

    /**
     * @brief Performs a depth-first search (dfs) traversal in the graph.
     *
     * Complexity: O(n)
     *
     * @return Vector of airports in dfs order.
     */
    vector<Airport> dfs() const;

    /**
     * @brief Performs a depth-first search (dfs) in the graph from a specific source airport.
     *
     * Complexity: O(n)
     *
     * @param source : Source airport.
     * @param dest : Destination airport.
     * @param path : Path between both airports.
     * @return True if there is a path, otherwise returns false.
     */
    bool dfs(Vertex* source, Vertex* dest, vector<Airport> path) const;

    /**
     * @brief Performs a breadth-first search (bfs) in the graph from a specific source airport.
     *
     * Complexity: O(n^2)
     *
     * @param source : Source airport.
     * @return Vector of airports in bfs order from the source.
     */
    vector<Airport> bfs(const Airport &source) const;

    /**
     * @brief Performs topological sort on the graph.
     *
     * Complexity: O(n^3)
     *
     * @return Vector of airports in topological order.
     */
    vector<Airport> topsort() const;

    /**
     * @brief Checks if the graph is a Directed Acyclic Graph (DAG).
     *
     * Complexity: O(n)
     *
     * @return True if the graph is acyclic, false otherwise.
     */
    bool isDAG() const;

    /**
     * @brief Cleans the graph by removing all vertices and edges.
     *
     * Complexity: O(n)
     */
    void clean();

    /**
     * @brief Gets the number of flights departing from a given airport.
     *
     * Complexity: O(n)
     *
     * @param airport : Departure airport.
     * @return Number of flights departing from the airport.
     */
    int getNumberOfFlights(Airport& airport) const;

    /**
    * @brief Gets the number of airlines operating at a given airport.
    *
    * Complexity: O(n)
    *
    * @param airport : Airport of interest.
    * @return Number of airlines operating at the airport.
    */
    unsigned long getNumberOfAirlines(const Airport& airport) const;

    /**
    * @brief Gets the number of destinations reachable from a given airport.
    *
    * Complexity: O(1)
    *
    * @param airport Source airport.
    * @return Number of destinations reachable from the source airport.
    */
    unsigned long getNumberOfDestinations(const Airport &airport) const;

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
     * Complexity: O(n^2)
     *
     * @param airline : The airline for which to retrieve the number of flights.
     * @return The number of flights associated with the airline.
     */
    int getNumberOfFlights(const Airline& airline) const;
 ////////////////////////////////////////////////////
    /**
     * @brief Gets the number of destinations served by the given airline.
     *
     * Complexity: O
     *
     * @param airline : The airline for which to retrieve the number of destinations.
     * @return A vector of destinations served by the airline.
     */
    vector<Airport> getNumberOfDestinations(const Airline& airline) const;


    /**
     * @brief Gets the number of flights associated with the given city.
     * @param city The city for which to retrieve the number of flights.
     * @param country The country of the city.
     * @return The number of flights associated with the city.
     */
    int getNumberOfFlightsInCity(const string& city, const string& country) const;

    /**
     * @brief Gets the number of airports in the specified city.
     * @param city The city for which to retrieve the number of airports.
     * @param country The country of the city.
     * @return The number of unique airports in the city.
     */
    int getNumberOfAirportsInCity(const string& city, const string& country) const;

    /**
     * @brief Gets the airports in the specified city.
     * @param city The city for which to retrieve the number of airports.
     * @param country The country of the city.
     * @return The vector of unique airports in the city.
     */
    vector<Airport> getAirportsInCity(const string& city, const string& country) const;

    /**
     * @brief Gets the number of unique airlines operating in the specified city.
     * @param city The city for which to retrieve the number of unique airlines.
     * @param country The country of the city.
     * @return The number of unique airlines operating in the city.
     */
    int getNumberOfAirlinesInCity(const string& city, const string& country) const;

    /**
     * @brief Gets the total number of unique destinations served by airports in the specified city.
     * @param city The city for which to retrieve the total number of destinations.
     * @param country The country of the city.
     * @return The total number of unique destinations served by airports in the city.
     */
    int getTotalDestinationsInCity(const string& city, const string& country) const;

    /**
     * @brief Gets the reachable destinations from airports in the specified city within a given number of stops.
     * @param city The city for which to retrieve the reachable destinations.
     * @param country The country of the city.
     * @param maxStops The maximum number of stops allowed.
     * @return Vector of airports representing the reachable destinations.
     */
    vector<Airport> getReachableDestinationsInCity(const string& city, const string& country, int maxStops) const;

    /**
     * @brief Gets the total number of flights departing from airports in the specified country.
     * @param country The country for which to retrieve the number of flights.
     * @return The total number of flights departing from airports in the country.
     */
    int getNumberOfFlightsInCountry(const string& country) const;

    /**
     * @brief Gets the number of airports in the specified country.
     * @param country The country for which to retrieve the number of airports.
     * @return The number of airports in the country.
     */
    int getNumberOfAirportsInCountry(const string& country) const;

    /**
     * @brief Gets the number of unique airlines operating in the specified country.
     * @param country The country for which to retrieve the number of airlines.
     * @return The number of unique airlines in the country.
     */
    int getNumberOfAirlinesInCountry(const string& country) const;

    /**
     * @brief Gets the total number of unique destinations in the specified country.
     * @param country The country for which to retrieve the number of destinations.
     * @return The total number of unique destinations in the country.
     */
    int getTotalDestinationsInCountry(const string& country) const;

    /**
     * @brief Gets the number of unique cities in the specified country.
     * @param country The country for which to retrieve the number of cities.
     * @return The number of unique cities in the country.
     */
    int getNumberOfCitiesInCountry(const string& country) const;

    /**
     * @brief Gets the reachable destinations in the specified country within a given number of stops.
     * @param country The country of interest.
     * @param maxStops The maximum number of stops allowed.
     * @return Vector of airports representing the reachable destinations.
     */
    vector<Airport> getReachableDestinationsInCountry(const string& country, int maxStops) const;

    /**
     * @brief Gets the total number of flights in the graph.
     * @return The total number of flights in the graph.
     */
    int getTotalNumberOfFlights() const;

    /**
     * @brief Gets the total number of airports in the graph.
     * @return The total number of airports in the graph.
     */
    int getTotalNumberOfAirports() const;

    /**
     * @brief Gets the total number of unique airlines operating in the graph.
     * @return The total number of unique airlines operating in the graph.
     */
    int getTotalNumberOfAirlines() const;

    /**
     * @brief Gets the total number of unique countries in the graph.
     * @return The total number of unique countries in the graph.
     */
    int getTotalNumberOfCountries() const;

    /**
     * @brief Gets the total number of unique cities in the graph.
     * @return The total number of unique cities in the graph.
     */
    int getTotalNumberOfCities() const;

    /**
     * @brief Gets the total number of reachable destinations within a maximum number of stops in the graph.
     * @param maxStops The maximum number of stops allowed.
     * @return The total number of reachable destinations within the specified number of stops.
     */
    int getTotalReachableDestinations(int maxStops) const;

    /**
     * @brief Gets a vector of airlines associated with a specific airport.
     * @param airport The airport for which to retrieve the associated airlines.
     * @return A vector of Airline objects representing the airlines associated with the airport.
     */
    vector<Airline> getAirlines(Airport airport);

    /**
     * @brief Gets the top airports based on the number of flights.
     * @param k The number of top airports to retrieve.
     * @return A vector of pairs representing the top airports and their respective number of flights.
     */
    vector<pair<Airport, int>> getTopKAirports(int k) const;

    /**
     * @brief Finds the maximum stops trip and corresponding source-destination airport pairs, using breadth-first search (BFS)
     * The result is printed to the terminal.
     */
    void findMaxStopsTrip();

    /**
     * @brief Gets airports closest to the specified coordinates.
     * @param lat Latitude of the target location in degrees.
     * @param longi Longitude of the target location in degrees.
     * @return Vector of airports closest to the specified coordinates.
     */
    vector<Airport> getAirportsInCoordinates(float lat, float longi) const;

    /**
     * @brief Finds a path between two airports in the graph using depth-first search (DFS).
     * @param s Source airport.
     * @param d Destination airport.
     * @return Vector of airports representing the path from source to destination.
     */
    vector<Airport> pathAirport(Airport s, Airport d);
};

#endif /* GRAPH_H_ */