#ifndef AED2324_PRJ2_AIRLINE_H
#define AED2324_PRJ2_AIRLINE_H

#include <string>
#include <utility>
using namespace  std;

class Airline {
private:
    string code;
    string name;
    string callsign;
    string country;

public:
    /**
     * @brief Constructor of the Airline class
     * @param c Airline's code
     * @param n Airline's name
     * @param cs Airline's callsign
     * @param co Airline's country
     */
    Airline(string c, string n, string cs, string co);

    /**
     * @brief Get code of the Airline
     * @return Returns the value of the Airline's code
     */
    string getCode();

    /**
     * @brief Get name of the Airline
     * @return Returns the value of the Airline's name
     */
    string getName();

    /**
     * @brief Get callsign of the Airline
     * @return Returns the value of the Airline's callsign
     */
    string getCallsign();

    /**
     * @brief Get country of the Airline
     * @return Returns the value of the Airline's country
     */
    string getCountry();

};

#endif