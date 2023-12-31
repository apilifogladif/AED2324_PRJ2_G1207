#include "Airport.h"

Airport::Airport() {
    code = "";
    name = "";
    city = "";
    country = "";
    latitude = 0;
    longitude = 0;
}

Airport::Airport(string c, string n, string ci, string co, double la, double lo) {
    code = std::move(c);
    name = std::move(n);
    city = std::move(ci);
    country = std::move(co);
    latitude = la;
    longitude = lo;
}

string Airport::getCode() const {return code;}

string Airport::getName() {return name;}

string Airport::getCity() {return city;}

string Airport::getCountry() {return country;}

double Airport::getLatitude() {return latitude;}

double Airport::getLongitude() {return longitude;}

bool Airport::operator==(const Airport& other) const {
    return this->getCode() == other.getCode();
}

bool Airport::operator!=(const Airport& other) const {
    return !(*this == other);
}

bool Airport::operator<(const Airport& other) const {
    return this->getCode() < other.getCode();
}