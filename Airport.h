#ifndef AED2324_PRJ2_AIRPORT_H
#define AED2324_PRJ2_AIRPORT_H

#include <string>
#include <utility>
#include <unordered_set>
#include <vector>
#include <iostream>

using namespace std;

/**
 * @brief Represents a Airport.
 */
class Airport {
private:
    string code;
    string name;
    string city;
    string country;
    double latitude;
    double longitude;
public:
    /**
     * @brief Default constructor of the Airport class
     *
     * Complexity: O(1)
     */
    Airport();
    /**
     *
     * @brief Constructor of the Airport class
     *
     * Complexity: O(1)
     *
     * @param c : Airport's code
     * @param n : Airport's name
     * @param ci : Airport's city
     * @param co : Airport's country
     * @param la : Airport's latitude
     * @param lo : Airport's longitude
     */
    Airport(string c, string n, string ci, string co, double la, double lo);

    /**
     * @brief Get code of the Airport
     *
     * Complexity: O(1)
     *
     * @return Returns the value of the Airport's code
     */
    string getCode() const;

    /**
     * @brief Get name of the Airport
     *
     * Complexity: O(1)
     *
     * @return Returns the value of the Airport's name
     */
    string getName();

    /**
     * @brief Get city of the Airport
     *
     * Complexity: O(1)
     *
     * @return Returns the value of the Airport's city
     */
    string getCity();

    /**
     * @brief Get country of the Airport
     *
     * Complexity: O(1)
     *
     * @return Returns the value of the Airport's country
     */
    string getCountry();

    /**
     * @brief Get latitude of the Airport
     *
     * Complexity: O(1)
     *
     * @return Returns the value of the Airport's latitude
     */
    double getLatitude();

    /**
     * @brief Get longitude of the Airport
     *
     * Complexity: O(1)
     *
     * @return Returns the value of the Airport's longitude
     */
    double getLongitude();

    /**
    * @brief Equality comparison operator for airports
    *
    * Complexity: O(1)
    *
    * @param other : The other airport to compare with
    * @return True if the airports are equal, false otherwise
    */
    bool operator==(const Airport& other) const;

    /**
    * @brief Inequality comparison operator for airports
    *
    * Complexity: O(1)
    *
    * @param other : The other airport to compare with
    * @return True if the airports are not equal, false otherwise
    */
    bool operator!=(const Airport& other) const;

    /**
     * @brief Less than operator for comparing two Airport objects
     *
     * Complexity: O(1)
     *
     * @param other : The Airport object to compare against
     * @return True if this Airport is considered less than the other, false otherwise
     */
    bool operator<(const Airport& other) const;
};

#endif