#ifndef AED2324_PRJ2_G1207_AUXILIARFUNCTIONS_H
#define AED2324_PRJ2_G1207_AUXILIARFUNCTIONS_H

#include <unordered_set>
#include "csvInfo.h"

using namespace std;

class AuxiliarFunctions {
public:
    /**
     * @brief Finds articulation points in the given graph using DFS (depth-first search).
     *
     * Complexity: O(n)
     *
     * @param g : Pointer to the graph.
     * @return Vector of unique airports representing articulation points.
     */
    static vector<Airport> articulationPoints(Graph* g);

    /**
     * @brief Find the best flight options between source and destination airports.
     *
     * Complexity: O(n^3)
     *
     * @param sourceAirports : Vector of source airports.
     * @param destAirports : Vector of destination airports.
     * @return Vector of vectors representing the best flight paths.
     */
    static vector<vector<Airport>> bestFlightOp(const vector<Airport>& sourceAirports, const vector<Airport>& destAirports);

    /**
     * @brief Finds the best flight paths between source and destination airports with airline restrictions.
     *
     * Complexity: O(n^3)
     *
     * @param sourceAirports : Vector of source airports.
     * @param destAirports : Vector of destination airports.
     * @param airlines : Vector of airline codes for restrictions.
     * @return Vector of vectors representing the best flight paths according to the user input.
     */
    static vector<vector<Airport>> filterVectorAirlines(const vector<Airport>& sourceAirports, const vector<Airport>& destAirports, const vector<string>& airlines);

    /**
     * @brief Finds the best flight paths between source and destination airports with a specified number of airlines.
     *
     * Complexity: O(n^3)
     * @param sourceAirports : Vector of source airports.
     * @param destAirports : Vector of destination airports.
     * @param numAir : Number of airlines for restrictions.
     * @return Vector of vectors representing the best flight paths according to the user input.
     */
    static vector<vector<Airport>> filterNumAirlines(const vector<Airport>& sourceAirports, const vector<Airport>& destAirports, int numAir);
};


#endif //AED2324_PRJ2_G1207_AUXILIARFUNCTIONS_H
