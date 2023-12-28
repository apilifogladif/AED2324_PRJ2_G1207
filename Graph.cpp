#include <set>
#include "Graph.h"

int Graph::getNumberOfFlights(Airport& airport) const {
    int numFlights = 0;
    Vertex* airportVertex = findVertex(airport);
    if (airportVertex != NULL) {
        for (auto edge : airportVertex->getAdj()) {
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
        for (auto edge : airportVertex->getAdj()) {
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
    for (auto edge : v->getAdj()) {
        Vertex* destinationVertex = edge.getDest();
        if (find(visited.begin(), visited.end(), destinationVertex->getAirport()) == visited.end()) {
            reachableDestinations.push_back(destinationVertex->getAirport());
            dfsReachableDestinations(destinationVertex, stopsLeft - 1, visited, reachableDestinations);
        }
    }
}