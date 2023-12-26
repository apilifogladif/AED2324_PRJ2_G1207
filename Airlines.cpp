#include "Airlines.h"

Airline::Airline(string c, string n, string cs, string co) {
    code = std::move(c);
    name = std::move(n);
    callsign = std::move(cs);
    country = std::move(co);
}

string Airline::getCode() {return code;}

string Airline::getName() {return name;}

string Airline::getCallsign() {return callsign;}

string Airline::getCountry() {return country;}