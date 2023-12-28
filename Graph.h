/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include "Airlines.h"
#include "Airport.h"

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
     * @param d Destination vertex.
     * @param airline_ Airline associated with the edge.
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
    /**
     * @brief Finds a vertex with the given airport in the graph.
     * @param in Airport to find.
     * @return Pointer to the found vertex or nullptr if not found.
     */
    Vertex *findVertex(Airport in) const;

    /**
     * @brief Finds a vertex with the given code in the graph.
     * @param in Code of the airport to find.
     * @return Pointer to the found vertex or nullptr if not found.
     */
    Vertex *findVertex(string in) const;

    /**
     * @brief Gets the number of vertices in the graph.
     * @return Number of vertices.
     */
    int getNumVertex() const;

    /**
     * @brief Adds a vertex with a given airport to the graph.
     * @param in Airport to add.
     * @return True if the vertex is added successfully, false otherwise.
     */
    bool addVertex(const Airport &in);

    /**
     * @brief Removes a vertex with a given airport from the graph.
     * @param in Airport to remove.
     * @return True if the vertex is removed successfully, false otherwise.
     */
    bool removeVertex(Airport in);

    /**
     * @brief Adds an edge to the graph.
     * @param sourc Source airport code.
     * @param dest Destination airport code.
     * @param airline Airline associated with the edge.
     * @return True if the edge is added successfully, false otherwise.
     */
    bool addEdge(const string &sourc, const string &dest, Airline airline);

    /**
     * @brief Removes an edge from the graph.
     * @param sourc Source airport.
     * @param dest Destination airport.
     * @return True if the edge is removed successfully, false otherwise.
     */
    bool removeEdge(const Airport &sourc, const Airport &dest);

    /**
     * @brief Gets the vector of vertices in the graph.
     * @return Vector of vertices.
     */
    vector<Vertex*> getVertexSet() const;

    /**
     * @brief Performs a depth-first search (dfs) traversal in the graph.
     * @return Vector of airports in dfs order.
     */
    vector<Airport> dfs() const;

    /**
     * @brief Performs a depth-first search (dfs) in the graph from a specific source airport.
     * @param source Source airport.
     * @return Vector of airports in dfs order from the source.
     */
    vector<Airport> dfs(const Airport & source) const;

    /**
     * @brief Performs a breadth-first search (bfs) in the graph from a specific source airport.
     * @param source Source airport.
     * @return Vector of airports in bfs order from the source.
     */
    vector<Airport> bfs(const Airport &source) const;

    /**
     * @brief Performs topological sort on the graph.
     * @return Vector of airports in topological order.
     */
    vector<Airport> topsort() const;

    /**
     * @brief Checks if the graph is a Directed Acyclic Graph (DAG).
     * @return True if the graph is acyclic, false otherwise.
     */
    bool isDAG() const;

    /**
     * @brief Cleans the graph by removing all vertices and edges.
     */
    void clean();

    /**
     * @brief Gets the number of flights departing from a given airport.
     * @param airport Departure airport.
     * @return Number of flights departing from the airport.
     */
    int getNumberOfFlights(Airport& airport) const;

    /**
    * @brief Gets the number of airlines operating at a given airport.
    * @param airport Airport of interest.
    * @return Number of airlines operating at the airport.
    */
    int getNumberOfAirlines(const Airport& airport) const;

    /**
    * @brief Gets the number of destinations reachable from a given airport.
    * @param airport Source airport.
    * @return Number of destinations reachable from the source airport.
    */
    int getNumberOfDestinations(const Airport &airport) const;

    /**
     * @brief Gets the reachable destinations from a source airport within a given number of stops.
     * @param source The source airport.
     * @param maxStops The maximum number of stops allowed.
     * @return Vector of airports representing the reachable destinations.
     */
    vector<Airport> getReachableDestinations(const Airport& source, int maxStops) const;

    /**
     * @brief Performs a depth-first search to find reachable destinations within a given number of stops.
     * @param v The current vertex being explored.
     * @param stopsLeft The remaining number of stops allowed.
     * @param visited Vector of visited airports to avoid revisiting.
     * @param reachableDestinations Vector to store the reachable destinations.
     */
    void dfsReachableDestinations(Vertex* v, int stopsLeft, vector<Airport>& visited, vector<Airport>& reachableDestinations) const;

    /**
     * @brief Gets the number of flights associated with the given airline.
     * @param airline The airline for which to retrieve the number of flights.
     * @return The number of flights associated with the airline.
     */
    int getNumberOfFlights(const Airline& airline) const;

    /**
     * @brief Gets the number of destinations served by the given airline.
     * @param airline The airline for which to retrieve the number of destinations.
     * @return The number of destinations served by the airline.
     */
    int getNumberOfDestinations(const Airline& airline) const;


    /**
     * @brief Gets the number of flights associated with the given city.
     * @param city The city for which to retrieve the number of flights.
     * @return The number of flights associated with the city.
     */
    int getNumberOfFlightsInCity(const string& city) const;

    /**
     * @brief Gets the number of airports in the specified city.
     * @param city The city for which to retrieve the number of airports.
     * @return The number of unique airports in the city.
     */
    int getNumberOfAirportsInCity(const string& city) const;

    /**
     * @brief Gets the number of unique airlines operating in the specified city.
     * @param city The city for which to retrieve the number of unique airlines.
     * @return The number of unique airlines operating in the city.
     */
    int getNumberOfAirlinesInCity(const string& city) const;

    /**
     * @brief Gets the total number of unique destinations served by airports in the specified city.
     * @param city The city for which to retrieve the total number of destinations.
     * @return The total number of unique destinations served by airports in the city.
     */
    int getTotalDestinationsInCity(const string& city) const;

    /**
     * @brief Gets the reachable destinations from airports in the specified city within a given number of stops.
     * @param city The city for which to retrieve the reachable destinations.
     * @param maxStops The maximum number of stops allowed.
     * @return Vector of airports representing the reachable destinations.
     */
    vector<Airport> getReachableDestinationsInCity(const string& city, int maxStops) const;

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

};

/****************** Provided constructors and functions ********************/

Vertex::Vertex(Airport in): airport(in) {}

int Graph::getNumVertex() const {
    return vertexSet.size();
}


Edge::Edge(Vertex *d, Airline airline_): dest(d), airline(airline_) {}

vector<Vertex * > Graph::getVertexSet() const {
    return vertexSet;
}

Airport Vertex::getAirport() const {
    return airport;
}

void Vertex::setAirport(Airport in) {
    airport = in;
}

bool Vertex::isProcessing() const {
    return processing;
}

void Vertex::setProcessing(bool p) {
    Vertex::processing = p;
}

Vertex *Edge::getDest() const {
    return dest;
}

void Edge::setDest(Vertex *d) {
    Edge::dest = d;
}

Airline Edge::getAirline() const {
    return airline;
}

void Edge::setAirline(Airline airline_) {
    airline = airline_;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(Airport in) const {
    for (auto v : vertexSet)
        if (v->airport.getCode() == in.getCode())
            return v;
    return NULL;
}

bool Vertex::isVisited() const {
    return visited;
}

int Vertex::getIndegree() const {
    return indegree;
}

void Vertex::setIndegree(int indegree) {
    Vertex::indegree = indegree;
}

int Vertex::getNum() const {
    return num;
}

void Vertex::setNum(int num) {
    Vertex::num = num;
}

int Vertex::getLow() const {
    return low;
}

void Vertex::setLow(int low) {
    Vertex::low = low;
}

void Vertex::setVisited(bool v) {
    Vertex::visited = v;
}

const vector<Edge> &Vertex::getAdj() const {
    return adj;
}

void Vertex::setAdj(const vector<Edge> &adj) {
    Vertex::adj = adj;
}


/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const Airport &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex(in));
    return true;
}


/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const string &sourc, const string &dest, Airline airline_) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,airline_);
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
void Vertex::addEdge(Vertex *d, Airline airline_) {
    adj.push_back(Edge(d, airline_));
}


/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
bool Graph::removeEdge(const Airport &sourc, const Airport &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
bool Vertex::removeEdgeTo(Vertex *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest  == d) {
            adj.erase(it);
            return true;
        }
    return false;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
bool Graph::removeVertex(Airport in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->airport.getCode()  == in.getCode()) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}


/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) traversal in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
vector<Airport> Graph::dfs() const {
    vector<Airport> res;
    for (auto v : vertexSet)
        v->visited = false;
    for (auto v : vertexSet)
        if (! v->visited)
            dfsVisit(v, res);
    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
void Graph::dfsVisit(Vertex *v, vector<Airport> & res) const {
    v->visited = true;
    res.push_back(v->airport);
    for (auto & e : v->adj) {
        auto w = e.dest;
        if ( ! w->visited)
            dfsVisit(w, res);
    }
}


/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order,
 * from the source node.
 */
vector<Airport> Graph::dfs(const Airport & source) const {
    vector<Airport> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;

    for (auto v : vertexSet)
        v->visited = false;

    dfsVisit(s, res);
    return res;
}


/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */
vector<Airport> Graph::bfs(const Airport & source) const {
    vector<Airport> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    queue<Vertex *> q;
    for (auto v : vertexSet)
        v->visited = false;
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->airport);
        for (auto & e : v->adj) {
            auto w = e.dest;
            if ( ! w->visited ) {
                q.push(w);
                w->visited = true;
            }
        }
    }
    return res;
}


/****************** isDAG  ********************/
/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

bool Graph::isDAG() const {
    for (auto v : vertexSet) {
        v->visited = false;
        v->processing = false;
    }
    for (auto v : vertexSet)
        if (! v->visited)
            if ( ! dfsIsDAG(v) )
                return false;
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
bool Graph::dfsIsDAG(Vertex *v) const {
    v->visited = true;
    v->processing = true;
    for (auto & e : v->adj) {
        auto w = e.dest;
        if (w->processing)
            return false;
        if (! w->visited)
            if (! dfsIsDAG(w))
                return false;
    }
    v->processing = false;
    return true;
}


/****************** topsort ********************/

vector<Airport> Graph::topsort() const {
    vector<Airport> res;
    queue<Vertex*> aux;

    // Set In-degree
    for (Vertex* v : vertexSet) {
        int c = 0;
        for (auto vtx : vertexSet) {
            for (auto edge : vtx->getAdj()) {
                if (edge.getDest() == v) {
                    c++;
                    continue;
                }
            }
        }
        v->setIndegree(c);
        if (v->getIndegree() == 0) aux.push(v);
    }

    // Topological Sort
    while (!aux.empty()) {
        Vertex* u = aux.front();
        aux.pop();
        res.push_back(u->getAirport());

        for (Edge edge : u->getAdj()) {
            edge.getDest()->setIndegree(edge.getDest()->getIndegree() - 1);
            if (edge.getDest()->getIndegree() == 0) {
                aux.push(edge.getDest());
            }
        }
    }

    if (res.size() != vertexSet.size()) {
        res.clear();
    }
    return res;
}

void Graph::clean() {
    for (auto v : vertexSet) {
        removeVertex(v->getAirport());
    }
}

Vertex *Graph::findVertex(string in) const {
    for (auto v : vertexSet)
        if (v->airport.getCode() == in)
            return v;
    return NULL;
}

#endif /* GRAPH_H_ */