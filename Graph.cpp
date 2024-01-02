#include "Graph.h"

#include <utility>
#include <cmath>
#include <limits>

// path between 2 airports using only a maximum of numAir airlines
//vector<pair<vector<Vertex*>, int>> Graph::pathAirportNumAirlines(const Airport& s, const Airport& d, int NumAir) {
//    Vertex* source = nullptr;
//    Vertex* dest = nullptr;
//
//    for (auto v : vertexSet) {
//        v->visited = false;
//        if (v->airport.getCode() == s.getCode())
//            source = v;
//
//        if (v->airport.getCode() == d.getCode())
//            dest = v;
//    }
//    if (source == nullptr || dest == nullptr) return {};
//
//    set<Airline> air;
//    return bfsPathFilterNumAir(source, dest, NumAir, air);
//}
//
//vector<pair<vector<Vertex*>, int>> Graph::bfsPathFilterNumAir(Vertex* source, Vertex* dest, int NumAir, set<Airline> air) {
//    vector<pair<vector<Vertex*>, int>> paths;
//    queue<pair<vector<Vertex*>, int>> q;
//    int min = INT_MAX;
//
//    for (auto v : vertexSet) v->visited = false;
//
//    q.emplace(vector<Vertex*>{source}, 0);
//
//    while (!q.empty()) {
//        auto p = q.front();
//        q.pop();
//        p.first.back()->setVisited(true);
//
//        if (p.second > min) break;
//
//        if (p.first.back() == dest) {
//            if (p.second < min) paths.clear();
//            min = p.second;
//            paths.emplace_back(p.first, static_cast<int>(air.size()));
//            cout << air.size() << endl;
//            continue;
//        }
//
//        for (const auto& e : p.first.back()->getAdj()) {
//            for (const auto& a : e.getAirline()) {
//                if (!e.getDest()->isVisited()) {
//                    set<Airline> newAir = air; // Create a new set to avoid modification of the original set
//                    newAir.insert(a);
//                    auto newTrip = p.first;
//                    newTrip.push_back(e.getDest());
//                    q.emplace(newTrip, p.second + 1);
//                }
//            }
//        }
//    }
//    return paths;
//}

vector<vector<Vertex*>> Graph::pathAirportNumAirlines(const Airport& s, const Airport& d, int NumAir) {
    vector<vector<Vertex*>> paths;

    Vertex* source = nullptr;
    Vertex* dest = nullptr;

    for (auto v : vertexSet) {
        v->visited = false;
        if (v->airport.getCode() == s.getCode())
            source = v;

        if (v->airport.getCode() == d.getCode())
            dest = v;
    }

    if (source == nullptr || dest == nullptr)
        return paths;

    queue<pair<vector<Vertex*>, set<Airline>>> q;
    q.emplace(vector<Vertex*>{source}, set<Airline>{});

    while (!q.empty()) {
        auto p = q.front();
        q.pop();

        p.first.back()->setVisited(true);

        if (p.first.back() == dest) {
            if (static_cast<int>(p.second.size()) <= NumAir) {
                paths.push_back(p.first);
            }
            continue;
        }

        for (const auto& e : p.first.back()->getAdj()) {
            for (const auto& a : e.getAirline()) {
                if (!e.getDest()->isVisited()) {
                    set<Airline> newAir = p.second; // Create a new set to avoid modification of the original set
                    newAir.insert(a);

                    if (static_cast<int>(newAir.size()) <= NumAir) {
                        auto newTrip = p.first;
                        newTrip.push_back(e.getDest());
                        q.emplace(newTrip, newAir);
                    }
                }
            }
        }
    }
    return paths;
}

// path between 2 airports using a set of airlines
vector<vector<Vertex*>> Graph::pathAirportRestrictAirlines(const Airport& s, const Airport& d, const vector<string>& airlines) {
    Vertex* source;
    Vertex* dest;

    for (auto v : vertexSet) {
        v->visited = false;
        if (v->airport.getCode() == s.getCode())
            source = v;

        if (v->airport.getCode() == d.getCode())
            dest = v;
    }
    if (source == nullptr || dest == nullptr) return {};


    return bfsPathFilterAirlines(source,dest,airlines);
}

vector<vector<Vertex*>> Graph::bfsPathFilterAirlines(Vertex* source, Vertex* dest, vector<string> airlines) const {
    vector<vector<Vertex*>> paths;
    queue<pair<vector<Vertex*>,int>> q;
    int min = INT_MAX;

    for (auto v : vertexSet)
        v->visited = false;

    q.emplace(vector<Vertex*> {source},0);
    while(!q.empty()){
        auto pair = q.front();
        q.pop();
        pair.first.back()->setVisited(true);

        if(pair.second > min) break;

        if(pair.first.back() == dest){
            if(pair.second < min) paths.clear();
            min = pair.second;
            paths.push_back(pair.first);
            continue;
        }

        for (const auto& e : pair.first.back()->getAdj()){
            bool ok = false;
            for (const auto& a : e.getAirline()) {
                if (find(airlines.begin(), airlines.end(), a.getCode()) != airlines.end()) {
                    ok = true;
                    break;
                }
            }
            if (ok) {
                if (e.getDest()->isVisited()) continue;
                auto newTrip = pair.first;
                newTrip.push_back(e.getDest());
                q.emplace(newTrip,pair.second+1);
            }
        }


    }

    return paths;
}

// path between 2 airports
vector<vector<Vertex*>> Graph::pathAirport(const Airport& s, const Airport& d) {
    Vertex* source;
    Vertex* dest;

    for (auto v : vertexSet) {
        v->visited = false;
        if (v->airport.getCode() == s.getCode())
            source = v;

        if (v->airport.getCode() == d.getCode())
            dest = v;
    }
    if (source == nullptr || dest == nullptr) return {};


    return bfsPath(source,dest);
}

vector<vector<Vertex*>> Graph::bfsPath(Vertex* source, Vertex* dest) const{
    vector<vector<Vertex*>> paths;
    queue<pair<vector<Vertex*>,int>> q;
    int min = INT_MAX;

    for (auto v : vertexSet)
        v->visited = false;

    q.emplace(vector<Vertex*> {source},0);
    while(!q.empty()){
        auto pair = q.front();
        q.pop();
        pair.first.back()->setVisited(true);

        if(pair.second > min) break;

        if(pair.first.back() == dest){
            if(pair.second < min) paths.clear();
            min = pair.second;
            paths.push_back(pair.first);
            continue;
        }

        for (auto e : pair.first.back()->getAdj()){
            if(e.getDest()->isVisited()) continue;
            auto newTrip = pair.first;
            newTrip.push_back(e.getDest());
            q.emplace(newTrip,pair.second+1);
        }


    }

    return paths;
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
int Graph::getNumberOfFlights(const Airport& airport) const {
    int numFlights = 0;
    for (auto v : vertexSet) {
        if (airport.getCode() == v->getAirport().getCode()) {
            for (const auto& edge : v->getAdj()) {
                numFlights += edge.getAirline().size();
            }
            break;
        }
    }
    return numFlights;
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
    set<Airline> airs;
    auto v = findVertex(airport);
    for (const auto& vtx : v->getAdj()) {
        for (auto a : vtx.getAirline()) {
            airs.insert(a);
        }
    }
    vector<Airline> vc(airs.begin(), airs.end());
    return vc;
}

// Airline

int Graph::getNumberOfFlights(const Airline& airline) const {
    int numFlights = 0;
    for (auto v : vertexSet) {
        for (const auto& edge : v->getAdj()) {
            for (const auto& a : edge.getAirline()) {
                if (a == airline) {
                    numFlights++;
                }
            }
        }
    }
    return numFlights;
}

vector<Airport> Graph::getNumberOfDestinations(const Airline& airline) const {
    vector<Airport> uniqueDestinations;
    for (auto v : vertexSet) {
        for (const auto& edge : v->getAdj()) {
            for (const auto& a : edge.getAirline()) {
                if (a == airline) {
                    if (find(uniqueDestinations.begin(), uniqueDestinations.end(), edge.getDest()->getAirport()) == uniqueDestinations.end()) {
                        uniqueDestinations.push_back(edge.getDest()->getAirport());
                    }
                }
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
            for (const auto& edge : v->getAdj()) {
                numFlights += edge.getAirline().size();
            }
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
                for (auto a : edge.getAirline()) {
                    uniqueAirlines.insert(a);
                }
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
            for (const auto& edge : v->getAdj()) {
                numFlights += edge.getAirline().size();
            }
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
                for (auto a : edge.getAirline()) {
                    uniqueAirlines.insert(a);
                }
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
        for (const auto& edge : v->getAdj()) {
            numFlights += edge.getAirline().size();
        }
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
            for (auto a : edge.getAirline()) {
                uniqueAirlines.insert(a);
            }
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
        int numFlights = getNumberOfFlights(vertex->getAirport());
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

Edge::Edge(Vertex *d, Airline airline_): dest(d) {
    airline.insert(airline_);
}

vector<Vertex * > Graph::getVertexSet() const {
    return vertexSet;
}

Airport Vertex::getAirport() const {
    return airport;
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

set<Airline> Edge::getAirline() const {
    return airline;
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
    bool t = false;
    for (Edge& i : adj) {
        if (i.getDest()->getAirport().getCode() == d->getAirport().getCode()) {
            i.airline.insert(airline_);
            t = true;
            break;
        }
    }
    if (!t) {
        adj.emplace_back(d, std::move(airline_));
    }
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

set<Airline> Graph::findAirlines(Vertex *vtx, Vertex *vtx2) {
    for (auto v : vtx->getAdj()) {
        if (v.getDest()->getAirport() == vtx2->getAirport()) {
            return v.getAirline();
        }
    }
    return set<Airline>();
}
