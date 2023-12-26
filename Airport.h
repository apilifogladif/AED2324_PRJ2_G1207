#include <string>
#include <utility>
using namespace std;

class Airport {
private:
    string code;
    string name;
    string city;
    string country;
    float latitude;
    float longitude;

public:
    /**
     *
     * @brief Constructor of the Airport class
     * @param c : Airport's code
     * @param n : Airport's name
     * @param ci : Airport's city
     * @param co : Airport's country
     * @param la : Airport's latitude
     * @param lo : Airport's longitude
     */
    Airport(string c, string n, string ci, string co, float la, float lo);

    /**
     * @brief Get code of the Airport
     * @return Returns the value of the Airport's code
     */
    string getCode();

    /**
     * @brief Get name of the Airport
     * @return Returns the value of the Airport's name
     */
    string getName();

    /**
     * @brief Get city of the Airport
     * @return Returns the value of the Airport's city
     */
    string getCity();

    /**
     * @brief Get country of the Airport
     * @return Returns the value of the Airport's country
     */
    string getCountry();

    /**
     * @brief Get latitude of the Airport
     * @return Returns the value of the Airport's latitude
     */
    float getLatitude();

    /**
     * @brief Get longitude of the Airport
     * @return Returns the value of the Airport's longitude
     */
    float getLongitude();
};
