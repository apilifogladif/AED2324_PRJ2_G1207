#include "Graph.h"

#include <utility>
#include <cmath>
#include <limits>

// path between 2 airports using only a maximum of numAir airlines
vector<Airport> Graph::pathAirportNumAirlines(const Airport& s, const Airport& d, int NumAir) {
    vector<Airport> aux;
    for (auto v : vertexSet) {
        v->visited = false;
        v->processing = false;
    }
    auto source = findVertex(s);
    auto dest = findVertex(d);
    if (source == nullptr || dest == nullptr) return aux;

    vector<string> air;
    dfsPathFilterNumAir(source, dest, &aux, NumAir, air);
    return aux;
}

bool Graph::dfsPathFilterNumAir(Vertex* source, Vertex* dest, vector<Airport>* path, int NumAir, vector<string>& air) const {
    source->visited = true;
    source->processing = true;
    path->push_back(source->airport);
    if (source->getAirport().getCode() == dest->getAirport().getCode()) {
        return true;
    }
    queue<Vertex*> save;
    for (auto& e : source->getAdj()) {
        if (!e.dest->isVisited() && air.size() < NumAir) {
            cout << e.dest->getAirport().getCode() << endl;
            cout << air.size() << endl;
            if(find(air.begin(), air.end(), e.getAirline().getCode()) == air.end()) {
                air.push_back(e.getAirline().getCode());
            }
            save.push(e.dest);
            e.dest->visited=true;
        }
    }
    while (!save.empty()) {
        Vertex* v = save.front();
        if (dfsPathFilterNumAir(v, dest, path, NumAir, air)) {
            return true;
        }
        save.pop();
    }
    path->pop_back();
    source->processing = false;
    return false;
}

// path between 2 airports using a set of airlines
vector<vector<Airport>> Graph::pathAirportRestrictAirlines(const Airport& s, const Airport& d, vector<string> airlines) {
    vector<vector<Airport>> aux;
    for (auto v : vertexSet) {
        v->visited = false;
        v->processing = false;
    }
    auto source = findVertex(s);
    auto dest = findVertex(d);
    if (source == nullptr || dest == nullptr) return aux;

    vector<Airport> path;
    dfsPathFilterAirlines(source, dest, &path, &aux, std::move(airlines));
    return aux;
}

bool Graph::dfsPathFilterAirlines(Vertex* source, Vertex* dest, vector<Airport>* path, vector<vector<Airport>>* aux, vector<string> airlines) const {
    source->visited = true;
    source->processing = true;
    path->push_back(source->airport);
    if (source->getAirport().getCode() == dest->getAirport().getCode()) {
        if (aux->size() == 0) {
            aux->push_back(*path);
        }
        else if (aux[0].size() > path->size()) {
                aux->clear();
                aux->push_back(*path);
        }

    }
    queue<Vertex*> save;
    for (auto& e : source->getAdj()) {
        if (!e.dest->isVisited() && find(airlines.begin(), airlines.end(), e.getAirline().getCode()) != airlines.end()) {
            save.push(e.dest);
            e.dest->visited=true;
        }
    }
    while (!save.empty()) {
        Vertex* v = save.front();
        if (dfsPathFilterAirlines(v, dest, path, aux, airlines)) {
            return true;
        }
        save.pop();
    }
    path->pop_back();
    source->processing = false;
    return false;
}

// path between 2 airports
vector<Airport> Graph::pathAirport(const Airport& s, const Airport& d) {
    vector<Airport> aux;
    for (auto v : vertexSet) {
        v->visited = false;
        v->processing = false;
    }
    auto source = findVertex(s);
    auto dest = findVertex(d);
    if (source == nullptr || dest == nullptr) return aux;

    dfsPath(source, dest, &aux);
    return aux;
}

bool Graph::dfsPath(Vertex* source, Vertex* dest, vector<Airport>* path) const {
    source->visited = true;
    source->processing = true;
    path->push_back(source->airport);
    if (source->getAirport().getCode() == dest->getAirport().getCode()) {
        return true;
    }
    queue<Vertex*> save;
    for (auto& e : source->getAdj()) {
        if (!e.dest->isVisited()) {
            save.push(e.dest);
            e.dest->visited=true;
        }
    }
    while (!save.empty()) {
        Vertex* v = save.front();
        if (dfsPath(v, dest, path)) {
            return true;
        }
        save.pop();
    }
    path->pop_back();
    source->processing = false;
    return false;
}

// Coordinates
vector<Airport> Graph::getAirportsInCoordinates(double lat, double longi) const {
    vector<Airport> closestAirports;
    double minDist = std::numeric_limits<double>::max();

    const double R = 6371.0;
    double lat1 = lat * M_PI / 180.0;
    double lon1 = longi * M_PI / 180.0;

    for (auto v : vertexSet) {
        double lat2 = v->getAirport().getLatitude() * M_PI / 180.0;
        double lon2 = v->getAirport().getLongitude() * M_PI / 180.0;

        double dLat = lat2 - lat1;
        double dLon = lon2 - lon1;

        double a = sin(dLat / 2) * sin(dLat / 2) +
                   cos(lat1) * cos(lat2) * sin(dLon / 2) * sin(dLon / 2);
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        double distance = R * c;

        if (distance < minDist) {
            minDist = distance;
            closestAirports.clear();
            closestAirports.push_back(v->getAirport());
        } else if (distance == minDist) {
            closestAirports.push_back(v->getAirport());
        }
    }
    return closestAirports;
}

// Airport

int Graph::getNumberOfFlights(Airport& airport) const {
    int numFlights = 0;
    Vertex* airportVertex = findVertex(airport);
    if (airportVertex != nullptr) {
        for (const auto& edge : airportVertex->getAdj()) {
            if (edge.getDest()->getAirport() == airport) {
                ++numFlights;
            }
        }
    }
    return numFlights;
}

unsigned long Graph::getNumberOfAirlines(const Airport& airport) const {
    set<string> uniqueAirlines;
    Vertex* airportVertex = findVertex(airport);
    if (airportVertex != nullptr) {
        for (auto& edge : airportVertex->getAdj()) {
            uniqueAirlines.insert(edge.getAirline().getCode());
        }
    }
    return uniqueAirlines.size();
}

unsigned long Graph::getNumberOfDestinations(const Airport& airport) const {
    Vertex* airportVertex = findVertex(airport);
    if (airportVertex != nullptr) {
        return airportVertex->getAdj().size();
    }
    return 0;
}

vector<Airport> Graph::getReachableDestinations(const Airport& source, int maxStops) const {
    vector<Airport> reachableDestinations;
    Vertex* sourceVertex = findVertex(source);
    for (auto v : vertexSet) v->visited = false;
    if (sourceVertex != nullptr) {
        sourceVertex->visited = true;
        for (const auto& v : sourceVertex->getAdj())
            if (! v.getDest()->isVisited()) {
                reachableDestinations.push_back(v.getDest()->getAirport());
                dfsReachableDestinations(v.getDest(), maxStops, reachableDestinations);
            }
    }
    return reachableDestinations;
}

void Graph::dfsReachableDestinations(Vertex* v, int stopsLeft, vector<Airport>& reachableDestinations) const {
    v->visited = true;
    if (stopsLeft == 0) {
        return;
    }
    for (const auto& edge : v->getAdj()) {
        Vertex* destinationVertex = edge.getDest();
        if (!destinationVertex->visited) {
            reachableDestinations.push_back(destinationVertex->getAirport());
            dfsReachableDestinations(destinationVertex, stopsLeft - 1, reachableDestinations);
        }
    }
}

vector<Airline> Graph::getAirlines(const Airport& airport) {
    vector<Airline> airs;
    auto v = findVertex(airport);
    for (const auto& vtx : v->getAdj()) {
        auto it = find(airs.begin(), airs.end(), vtx.getAirline());
        if (it == airs.end()) airs.push_back(vtx.getAirline());
    }
    return airs;
}

// Airline

int Graph::getNumberOfFlights(const Airline& airline) const {
    int numFlights = 0;
    for (auto v : vertexSet) {
        for (const auto& edge : v->getAdj()) {
            if (edge.getAirline() == airline) {
                numFlights++;
            }
        }
    }
    return numFlights;
}

vector<Airport> Graph::getNumberOfDestinations(const Airline& airline) const {
    vector<Airport> uniqueDestinations;
    for (auto v : vertexSet) {
        for (const auto& edge : v->getAdj()) {
            if (edge.getAirline() == airline && find(uniqueDestinations.begin(), uniqueDestinations.end(), edge.getDest()->getAirport()) == uniqueDestinations.end()) {
                uniqueDestinations.push_back(edge.getDest()->getAirport());
            }
        }
    }
    return uniqueDestinations;
}

// City

int Graph::getNumberOfFlightsInCity(const string& city, const string& country) const {
    int numFlights = 0;
    for (const Vertex* v : getVertexSet()) {
        if (v->getAirport().getCity() == city && v->getAirport().getCountry() == country) {
            numFlights = v->getAdj().size();
            break;
        }
    }
    return numFlights;
}

int Graph::getNumberOfAirportsInCity(const string& city, const string& country) const {
    set<Airport> uniqueAirports;
    for (auto v : getVertexSet()) {
        if (v->getAirport().getCity() == city && v->getAirport().getCountry() == country) {
            uniqueAirports.insert(v->getAirport());
        }
    }
    return uniqueAirports.size();
}

vector<Airport> Graph::getAirportsInCity(const string& city, const string& country) const {
    vector<Airport> uniqueAirports;
    for (auto v : getVertexSet()) {
        if (v->getAirport().getCity() == city && v->getAirport().getCountry() == country) {
            uniqueAirports.push_back(v->getAirport());
        }
    }
    return uniqueAirports;
}

int Graph::getNumberOfAirlinesInCity(const string& city, const string& country) const {
    set<Airline> uniqueAirlines;
    for (auto v : getVertexSet()) {
        if (v->getAirport().getCity() == city && v->getAirport().getCountry() == country) {
            for (const auto& edge : v->getAdj()) {
                uniqueAirlines.insert(edge.getAirline());
            }
        }
    }
    return uniqueAirlines.size();
}

int Graph::getTotalDestinationsInCity(const string& city, const string& country) const {
    set<Airport> uniqueDestinations;
    for (auto v : getVertexSet()) {
        if (v->getAirport().getCity() == city && v->getAirport().getCountry() == country) {
            for (const auto& edge : v->getAdj()) {
                uniqueDestinations.insert(edge.getDest()->getAirport());
            }
        }
    }
    return uniqueDestinations.size();
}

vector<Airport> Graph::getReachableDestinationsInCity(const string& city, const string& country, int maxStops) const {
    vector<Airport> allReachableDestinations;
    for (auto v : getVertexSet()) {
        if (v->getAirport().getCity() == city && v->getAirport().getCountry() == country) {
            vector<Airport> reachableDestinations = getReachableDestinations(v->getAirport(), maxStops);
            allReachableDestinations.insert(allReachableDestinations.end(), reachableDestinations.begin(), reachableDestinations.end());
        }
    }
    set<Airport> uniqueDestinations(allReachableDestinations.begin(), allReachableDestinations.end());
    return vector<Airport>(uniqueDestinations.begin(), uniqueDestinations.end());
}

// Country

int Graph::getNumberOfFlightsInCountry(const string& country) const {
    int numFlights = 0;
    for (auto v : getVertexSet()) {
        if (v->getAirport().getCountry() == country) {
            numFlights += v->getAdj().size();
        }
    }
    return numFlights;
}

int Graph::getNumberOfAirportsInCountry(const string& country) const {
    set<Airport> uniqueAirports;
    for (auto v : getVertexSet()) {
        if (v->getAirport().getCountry() == country) {
            uniqueAirports.insert(v->getAirport());
        }
    }
    return uniqueAirports.size();
}

int Graph::getNumberOfAirlinesInCountry(const string& country) const {
    set<Airline> uniqueAirlines;
    for (auto v : getVertexSet()) {
        for (const auto& edge : v->getAdj()) {
            if (edge.getDest()->getAirport().getCountry() == country) {
                uniqueAirlines.insert(edge.getAirline());
            }
        }
    }
    return uniqueAirlines.size();
}

int Graph::getTotalDestinationsInCountry(const string& country) const {
    set<Airport> uniqueDestinations;
    for (auto v : getVertexSet()) {
        if (v->getAirport().getCountry() == country) {
            for (const auto& edge : v->getAdj()) {
                uniqueDestinations.insert(edge.getDest()->getAirport());
            }
        }
    }
    return uniqueDestinations.size();
}

int Graph::getNumberOfCitiesInCountry(const string& country) const {
    set<string> uniqueCities;
    for (auto v : getVertexSet()) {
        if (v->getAirport().getCountry() == country) {
            uniqueCities.insert(v->getAirport().getCity());
        }
    }
    return uniqueCities.size();
}

vector<Airport> Graph::getReachableDestinationsInCountry(const string& country, int maxStops) const {
    vector<Airport> allReachableDestinations;
    for (auto v : getVertexSet()) {
        if (v->getAirport().getCountry() == country) {
            vector<Airport> reachableDestinations = getReachableDestinations(v->getAirport(), maxStops);
            allReachableDestinations.insert(allReachableDestinations.end(), reachableDestinations.begin(), reachableDestinations.end());
        }
    }
    set<Airport> uniqueDestinations(allReachableDestinations.begin(), allReachableDestinations.end());
    return vector<Airport>(uniqueDestinations.begin(), uniqueDestinations.end());
}

// Global

int Graph::getTotalNumberOfFlights() const {
    int numFlights = 0;
    for (auto v : getVertexSet()) {
        numFlights += v->getAdj().size();
    }
    return numFlights;
}

int Graph::getTotalNumberOfAirports() const {
    return getVertexSet().size();
}

int Graph::getTotalNumberOfAirlines() const {
    set<Airline> uniqueAirlines;
    for (auto v : getVertexSet()) {
        for (const auto& edge : v->getAdj()) {
            uniqueAirlines.insert(edge.getAirline());
        }
    }
    return uniqueAirlines.size();
}

int Graph::getTotalNumberOfCountries() const {
    set<string> uniqueCountries;
    for (auto v : getVertexSet()) {
        uniqueCountries.insert(v->getAirport().getCountry());
    }
    return uniqueCountries.size();
}

int Graph::getTotalNumberOfCities() const {
    set<string> uniqueCities;
    for (auto v : getVertexSet()) {
        uniqueCities.insert(v->getAirport().getCity());
    }
    return uniqueCities.size();
}

int Graph::getTotalReachableDestinations(int maxStops) const {
    set<Airport> uniqueDestinations;
    for (auto v : getVertexSet()) {
        vector<Airport> reachableDestinations = getReachableDestinations(v->getAirport(), maxStops);
        uniqueDestinations.insert(reachableDestinations.begin(), reachableDestinations.end());
    }
    return uniqueDestinations.size();
}

// Others

void Graph::findMaxStopsTrip() {
    vector<pair<string, string>> maxStopsTripPairs;
    int maxStops = 0;

    for (auto sourceVertex : vertexSet) {

        for (auto v : vertexSet) {
            v->setVisited(false);
        }

        queue<pair<Vertex *, int>> q;
        q.emplace(sourceVertex, 0);
        q.front().first->setVisited(true);

        while (!q.empty()) {
            Vertex *currentVertex = q.front().first;
            int stopsCount = q.front().second;
            q.pop();

            for (auto &edge : currentVertex->getAdj()) {
                auto destVertex = edge.getDest();

                if (!destVertex->isVisited()) {
                    q.emplace(destVertex, stopsCount + 1);
                    destVertex->setVisited(true);

                    if (maxStops < stopsCount + 1) {
                        maxStopsTripPairs.clear();
                    }

                    if (maxStops <= stopsCount + 1) {
                        maxStops = stopsCount + 1;
                        maxStopsTripPairs.emplace_back(sourceVertex->getAirport().getCode(), destVertex->getAirport().getCode());
                    }
                }
            }
        }
    }

    cout << "Maximum trip with " << maxStops << " stops." << endl;
    cout << "Pairs of source-destination airports: " << endl;

    for (auto &tripPair : maxStopsTripPairs) {
        cout << tripPair.first << " - " << tripPair.second << endl;
    }
}

vector<pair<Airport, int>> Graph::getTopKAirports(int k) const {
    vector<pair<Airport, int>> airportFlights;
    for (auto vertex : getVertexSet()) {
        int numFlights = vertex->getAdj().size();
        airportFlights.emplace_back(vertex->getAirport(), numFlights);
    }
    auto comp = [](const auto& a, const auto& b) {
        return a.second > b.second;
    };
    sort(airportFlights.begin(), airportFlights.end(), comp);
    vector<pair<Airport, int>> topAirports;
    if (k > 0 && k <= static_cast<int>(airportFlights.size())) {
        topAirports.assign(airportFlights.begin(), airportFlights.begin() + k);
    }
    return topAirports;
}

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
    airline = std::move(airline_);
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(const Airport& in) const {
    for (auto v : vertexSet)
        if (v->airport.getCode() == in.getCode())
            return v;
    return nullptr;
}

bool Vertex::isVisited() const {
    return visited;
}

int Vertex::getIndegree() const {
    return indegree;
}

void Vertex::setIndegree(int indegree_) {
    Vertex::indegree = indegree_;
}

int Vertex::getNum() const {
    return num;
}

void Vertex::setNum(int num_) {
    Vertex::num = num_;
}

int Vertex::getLow() const {
    return low;
}

void Vertex::setLow(int low_) {
    Vertex::low = low_;
}

void Vertex::setVisited(bool v) {
    Vertex::visited = v;
}

const vector<Edge> &Vertex::getAdj() const {
    return adj;
}

void Vertex::setAdj(const vector<Edge> &adj_) {
    Vertex::adj = adj_;
}


/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const Airport &in) {
    auto *v = new Vertex(in);
    vertexSet.push_back(v);
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
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2,std::move(airline_));
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
void Vertex::addEdge(Vertex *d, Airline airline_) {
    adj.push_back(Edge(d, std::move(airline_)));
}


/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
bool Graph::removeEdge(const Airport &sourc, const Airport &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
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
bool Graph::removeVertex(const Airport& in) {
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

/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */
vector<Airport> Graph::bfs(const Airport & source) const {
    vector<Airport> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;
    for (auto v : vertexSet)
        v->visited = false;
    queue<Vertex *> q;
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
    for (auto v : vertexSet) {
        if (v->airport.getCode() == in)

            return v;
    }
    return NULL;
}

