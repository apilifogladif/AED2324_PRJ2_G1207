#ifndef AED2324_PRJ2_G1207_AUXILIARFUNCTIONS_H
#define AED2324_PRJ2_G1207_AUXILIARFUNCTIONS_H

#include <unordered_set>
#include "csvInfo.h"

using namespace std;

class AuxiliarFunctions {
public:
    static vector<Airport> articulationPoints(Graph* g);

    static vector<vector<Airport>> bestFlightOp(vector<Airport> sourceAirports, vector<Airport> destAirports);
};


#endif //AED2324_PRJ2_G1207_AUXILIARFUNCTIONS_H
