#ifndef AED2324_PRJ2_G1207_AUXILIARFUNCTIONS_H
#define AED2324_PRJ2_G1207_AUXILIARFUNCTIONS_H

#include <unordered_set>
#include "csvInfo.h"

using namespace std;

/**
 * @brief Has some the auxiliar functions used.
 */
class AuxiliarFunctions {
public:
    /**
     * @brief Finds articulation points in the given graph using DFS (depth-first search)
     *
     * Complexity: O(n)
     *
     * @param g : Pointer to the graph
     * @return Vector of unique airports representing articulation points
     */
    static vector<Airport> articulationPoints(Graph* g);

    /**
     * @brief Find the best flight options between source and destination airports
     *
     * Complexity: O(n^4)
     *
     * @param sourceAirports : Vector of source airports
     * @param destAirports : Vector of destination airports
     * @return Vector of vectors representing the best flight paths
     */
    static vector<vector<Airport>> bestFlightOp(const vector<Airport>& sourceAirports, const vector<Airport>& destAirports);

    /**
     * @brief Checks what is  best path
     * Calls the function that restricts the airline used
     *
     * Complexity: O(n^4)
     *
     * @param sourceAirports : Source airports
     * @param destAirports : Destination airports
     * @param airlines : Airlines allowed
     * @return Best path found
     */
    static vector<vector<Airport>> filterVectorAirlines(const vector<Airport>& sourceAirports, const vector<Airport>& destAirports, const vector<string>& airlines);

    /**
     * @brief Checks what is best path
     * Calls the function that restricts the number of airlines used
     *
     * Complexity: O(n^3)
     *
     * @param sourceAirports : Source airports
     * @param destAirports : Destination airports
     * @param numAir : Number of airlines allowed
     * @return Best path found
     */
    static vector<vector<Airport>> filterNumAirlines(const vector<Airport>& sourceAirports, const vector<Airport>& destAirports, int numAir);
};


#endif //AED2324_PRJ2_G1207_AUXILIARFUNCTIONS_H
