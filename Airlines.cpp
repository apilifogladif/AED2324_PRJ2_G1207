#include "Airlines.h"

Airline::Airline() {
    code = "";
    name = "";
    callsign = "";
    country = "";
}

Airline::Airline(string c, string n, string cs, string co) {
    code = std::move(c);
    name = std::move(n);
    callsign = std::move(cs);
    country = std::move(co);
}

string Airline::getCode() const {return code;}

string Airline::getName() const {return name;}

string Airline::getCallsign() const {return callsign;}

string Airline::getCountry() const {return country;}

bool Airline::operator==(const Airline& other) const {
    return this->code == other.getCode() && this->name == other.getName() && this->callsign == other.getCallsign() && this->country == other.getCountry();
}

bool Airline::operator<(const Airline& other) const {
    return this->code < other.getCode();
}
