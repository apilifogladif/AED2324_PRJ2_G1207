#include <string>
#include <utility>
using namespace  std;

class Airport {
private:
    string code;
    string name;
    string city;
    string country;
    float latitude;
    float longitude;

public:
    Airport(string c, string n, string ci, string co, float la, float lo);
    string getCode();
    string getName();
    string getCity();
    string getCountry();
    float getLatitude();
    float getLongitude();
};

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