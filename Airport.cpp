#include "Airport.h"

Airport::Airport(string c, string n, string ci, string co, float la, float lo) {
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

float Airport::getLatitude() {return latitude;}

float Airport::getLongitude() {return longitude;}

bool Airport::operator==(const Airport& other) const {
    return this->getCode() == other.getCode();
}

bool Airport::operator!=(const Airport& other) const {
    return !(*this == other);
}