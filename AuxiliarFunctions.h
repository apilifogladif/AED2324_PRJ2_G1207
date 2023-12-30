#ifndef AED2324_PRJ2_G1207_AUXILIARFUNCTIONS_H
#define AED2324_PRJ2_G1207_AUXILIARFUNCTIONS_H

#include <unordered_set>
#include "csvInfo.h"

using namespace std;

class AuxiliarFunctions {
public:
    /**
     * @brief
     *
     * Complexity:
     *
     * @param g :
     * @return
     */
    static vector<Airport> articulationPoints(Graph* g);

    /**
     * @brief
     *
     * Complexity:
     *
     * @param g :
     * @return
     */
    static vector<Airport> essentialAirports(Graph *g);

    /**
     * @brief
     *
     * Complexity:
     *
     * @param sourceAirports :
     * @param destAirports :
     * @return
     */
    static vector<vector<Airport>> bestFlightOp(const vector<Airport>& sourceAirports, const vector<Airport>& destAirports);
};


#endif //AED2324_PRJ2_G1207_AUXILIARFUNCTIONS_H