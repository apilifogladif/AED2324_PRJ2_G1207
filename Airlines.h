#include <string>
#include <utility>
using namespace  std;

class Airline {
private:
    Airline(int c, int n, int cs, int co);

    string code;
    string name;
    string callsign;
    string country;

public:
    Airline(string c, string n, string cs, string co);
    string getCode();
    string getName();
    string getCallsign();
    string getCountry();
};

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