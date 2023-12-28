#include <set>
#include "Graph.h"

// Airport

int Graph::getNumberOfFlights(Airport& airport) const {
    int numFlights = 0;
    Vertex* airportVertex = findVertex(airport);
    if (airportVertex != NULL) {
        for (const auto& edge : airportVertex->getAdj()) {
            if (edge.getDest()->getAirport() == airport) {
                ++numFlights;
            }
        }
    }
    return numFlights;
}

int Graph::getNumberOfAirlines(const Airport& airport) const {
    set<string> uniqueAirlines;
    Vertex* airportVertex = findVertex(airport);
    if (airportVertex != NULL) {
        for (auto& edge : airportVertex->getAdj()) {
            uniqueAirlines.insert(edge.getAirline().getCode());
        }
    }
    return uniqueAirlines.size();
}

int Graph::getNumberOfDestinations(const Airport& airport) const {
    Vertex* airportVertex = findVertex(airport);
    if (airportVertex != NULL) {
        return airportVertex->getAdj().size();
    }
    return 0;
}

vector<Airport> Graph::getReachableDestinations(const Airport& source, int maxStops) const {
    vector<Airport> reachableDestinations;
    Vertex* sourceVertex = findVertex(source);
    if (sourceVertex != NULL) {
        vector<Airport> visited;
        dfsReachableDestinations(sourceVertex, maxStops, visited, reachableDestinations);
    }
    return reachableDestinations;
}

void Graph::dfsReachableDestinations(Vertex* v, int stopsLeft, vector<Airport>& visited, vector<Airport>& reachableDestinations) const {
    visited.push_back(v->getAirport());
    if (stopsLeft == 0) {
        return;
    }
    for (const auto& edge : v->getAdj()) {
        Vertex* destinationVertex = edge.getDest();
        if (find(visited.begin(), visited.end(), destinationVertex->getAirport()) == visited.end()) {
            reachableDestinations.push_back(destinationVertex->getAirport());
            dfsReachableDestinations(destinationVertex, stopsLeft - 1, visited, reachableDestinations);
        }
    }
}

// Airline

int Graph::getNumberOfFlights(const Airline& airline) const {
    int numFlights = 0;
    for (auto v : vertexSet) {
        for (const auto& edge : v->getAdj()) {
            if (edge.getAirline() == airline) {
                ++numFlights;
            }
        }
    }
    return numFlights;
}

int Graph::getNumberOfDestinations(const Airline& airline) const {
    set<Airport> uniqueDestinations;
    for (auto v : vertexSet) {
        for (const auto& edge : v->getAdj()) {
            if (edge.getAirline() == airline) {
                uniqueDestinations.insert(edge.getDest()->getAirport());
            }
        }
    }
    return uniqueDestinations.size();
}

// City

int Graph::getNumberOfFlightsInCity(const string& city) const {
    int numFlights = 0;
    for (const Vertex* v : getVertexSet()) {
        if (v->getAirport().getCity() == city) {
            for (const Edge& edge : v->getAdj()) {
                numFlights += getNumberOfFlights(edge.getAirline());
            }
        }
    }
    return numFlights;
}

int Graph::getNumberOfAirportsInCity(const string& city) const {
    set<Airport> uniqueAirports;
    for (auto v : getVertexSet()) {
        if (v->getAirport().getCity() == city) {
            uniqueAirports.insert(v->getAirport());
        }
    }
    return uniqueAirports.size();
}

int Graph::getNumberOfAirlinesInCity(const string& city) const {
    set<Airline> uniqueAirlines;
    for (auto v : getVertexSet()) {
        if (v->getAirport().getCity() == city) {
            for (const auto& edge : v->getAdj()) {
                uniqueAirlines.insert(edge.getAirline());
            }
        }
    }
    return uniqueAirlines.size();
}

int Graph::getTotalDestinationsInCity(const string& city) const {
    set<Airport> uniqueDestinations;
    for (auto v : getVertexSet()) {
        if (v->getAirport().getCity() == city) {
            for (const auto& edge : v->getAdj()) {
                uniqueDestinations.insert(edge.getDest()->getAirport());
            }
        }
    }
    return uniqueDestinations.size();
}

vector<Airport> Graph::getReachableDestinationsInCity(const string& city, int maxStops) const {
    vector<Airport> allReachableDestinations;
    for (auto v : getVertexSet()) {
        if (v->getAirport().getCity() == city) {
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
                numFlights += getNumberOfFlights(edge.getAirline());
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