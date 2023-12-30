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
     * @brief Default constructor of the Airline class.
     *
     * Complexity: O(1)
     */
    Airline();

    /**
     * @brief Constructor of the Airline class.
     *
     * Complexity: O(1)
     *
     * @param c : Airline's code.
     * @param n : Airline's name.
     * @param cs : Airline's callsign.
     * @param co : Airline's country.
     *
     */
    Airline(string c, string n, string cs, string co);

    /**
     * @brief Get code of the Airline.
     *
     * Complexity: O(1)
     *
     * @return Returns the value of the Airline's code.
     *
     */
    string getCode() const;

    /**
     * @brief Get name of the Airline.
     *
     * Complexity: O(1)
     *
     * @return Returns the value of the Airline's name.
     *
     */
    string getName() const;

    /**
     * @brief Get callsign of the Airline.
     *
     * Complexity: O(1)
     *
     * @return Returns the value of the Airline's callsign.
     *
     */
    string getCallsign() const;

    /**
     * @brief Get country of the Airline.
     *
     * Complexity: O(1)
     *
     * @return Returns the value of the Airline's country.
     *
     */
    string getCountry() const;

    /**
     * @brief Equality operator for Airline objects.
     *
     * Complexity: O(1)
     *
     * @param a : The first Airline object.
     * @param b : The second Airline object.
     * @return True if the Airline objects are equal, false otherwise.
     */
    bool operator==(const Airline& other) const;

    /**
     * @brief Overloaded less-than comparison operator for Airline objects.
     *
     * Complexity: O(1)
     *
     * @param other : The Airline object to compare against.
     * @return True if this Airline is less than the other, false otherwise.
     */
    bool operator<(const Airline& other) const;

};

#endif