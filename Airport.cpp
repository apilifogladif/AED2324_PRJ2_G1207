#include "Airport.h"

Airport::Airport(string c, string n, string ci, string co, float la, float lo) {
    code = std::move(c);
    name = std::move(n);
    city = std::move(ci);
    country = std::move(co);
    latitude = la;
    longitude = lo;
}

string Airport::getCode() {return code;}

string Airport::getName() {return name;}

string Airport::getCity() {return city;}

string Airport::getCountry() {return country;}

float Airport::getLatitude() {return latitude;}

float Airport::getLongitude() {return longitude;}

/*
int Airport::getNumberOfFlights(Graph &fg) {
    int numFlights = 0;
    for (auto &edge : fg.findVertex(*this)->getAdj()) {
        if (edge.getDest()) {
            ++numFlights;
        }
    }
    return numFlights;
}

int Airport::getNumberOfAirlines(Graph &fg) {
    unordered_set<Airline> uniqueAirlines(allAirlines.begin(), allAirlines.end());
    for (auto &edge : fg.findVertex(*this)->getAdj()) {
        uniqueAirlines.insert(edge.getAirline());
    }
    return uniqueAirlines.size();
}

int Airport::getNumberOfDestinations(Graph &fg) {
    return fg.findVertex(*this)->getAdj().size();
}

vector<Airport> Airport::getReachableDestinations(Graph &fg, int maxStops) {
    vector<Airport> reachableDestinations;
    dfsToFindReachableDestinations(fg, *this, maxStops, reachableDestinations);
    return reachableDestinations;
}

void Airport::dfsToFindReachableDestinations(Graph &fg, Airport &source, int maxStops, vector<Airport> &reachableDestinations) {
    if (stopsLeft < 0) {
        return;
    }
    fg.findVertex(source)->setVisited(true);
    for (const Edge &edge : fg.findVertex(source)->getAdj()) {
        if (!edge.getDest()->isVisited()) {
            reachableDestinations.push_back(edge.getDest()->getAirport());
            dfsToFindReachableDestinations(fg, edge.getDest()->getAirport(), maxStops - 1, reachableDestinations);
        }
    }
    fg.findVertex(source)->setVisited(false);
}
*/