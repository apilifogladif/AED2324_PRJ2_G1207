#include "AuxiliarFunctions.h"

//=============================================================================
// Articulation Points
//=============================================================================
void dfs_art(Graph *g, Vertex *v, stack<Airport> &s, vector<Airport> &res, int &i);

vector<Airport> AuxiliarFunctions::articulationPoints(Graph *g) {
    vector<Airport> res;
    stack<Airport> s;
    int index = 1;
    for (auto v : g->getVertexSet())
        v->setVisited(false);

    for (auto v : g->getVertexSet()) {
        if (! v->isVisited())
            dfs_art(g, v, s, res, index);
    }
    set<Airport> uniqueAirports(res.begin(), res.end());
    res.assign(uniqueAirports.begin(), uniqueAirports.end());
    for (const auto & a : res) {
        cout << a.getCode() << " ";
    }
    cout << endl;
    return res;
}

/**
 * @brief
 *
 * Complexity:
 *
 * @param g :
 * @param v :
 * @param s :
 * @param res :
 * @param i :
 */
void dfs_art(Graph *g, Vertex *v, stack<Airport> &s, vector<Airport> &res, int &i){
    v->setVisited(true);

    v->setLow(i);
    v->setNum(i);
    v->setProcessing(true);
    s.push(v->getAirport());
    i++;

    int count = 0;

    for (auto & e : v->getAdj()) {
        auto w = e.getDest();
        if (!w->isVisited()) {
            count++;
            dfs_art(g, w, s, res, i);
            v->setLow(min(v->getLow(), w->getLow()));
            if (w->getLow() >= v->getNum() && v->getNum() != 1)
                res.push_back(v->getAirport());
        } else if (w->isProcessing())
            v->setLow(min(v->getLow(), w->getNum()));
        if (count > 1 && v->getNum() == 1)
            res.push_back(v->getAirport());
    }
    v->setProcessing(false);
    s.pop();
}


// Best flight option

vector<vector<Airport>> AuxiliarFunctions::bestFlightOp(const vector<Airport>& sourceAirports, const vector<Airport>& destAirports) {
    vector<Airport> aux;
    vector<vector<Airport>> best;
    bool first = true;
    for (const Airport& s : sourceAirports) {
        for (const Airport& d : destAirports) {
            aux = csvInfo::flightsGraph.pathAirport(s, d);
            if (first) {
                best.push_back(aux);
                first = false;
            }
            else if (aux.size() < best[0].size()) {
                best.clear();
                best.push_back(aux);
            }
            else if (aux.size() == best[0].size()) {
                best.push_back(aux);
            }
        }
    }
    return best;
}

vector<vector<Airport>>
AuxiliarFunctions::filterVectorAirlines(const vector<Airport>& sourceAirports, const vector<Airport>& destAirports, const vector<string>& airlines) {
    vector<Airport> aux;
    vector<vector<Airport>> best;
    bool first = true;
    for (const Airport& s : sourceAirports) {
        for (const Airport& d : destAirports) {
            aux = csvInfo::flightsGraph.pathAirportRestrictAirlines(s, d, airlines);
            if (first) {
                best.push_back(aux);
                first = false;
            }
            else if (aux.size() < best[0].size()) {
                best.clear();
                best.push_back(aux);
            }
            else if (aux.size() == best[0].size()) {
                best.push_back(aux);
            }
        }
    }
    return best;
}

vector<vector<Airport>>
AuxiliarFunctions::filterNumAirlines(const vector<Airport>& sourceAirports, const vector<Airport>& destAirports, int numAir) {
    vector<Airport> aux;
    vector<vector<Airport>> best;
    bool first = true;
    for (const Airport& s : sourceAirports) {
        for (const Airport& d : destAirports) {
            aux = csvInfo::flightsGraph.pathAirportNumAirlines(s, d, numAir);
            if (aux.empty()) continue;
            if (first) {
                best.push_back(aux);
                first = false;
            }
            else if (aux.size() < best[0].size()) {
                best.clear();
                best.push_back(aux);
            }
            else if (aux.size() == best[0].size()) {
                best.push_back(aux);
            }
        }
    }
    return best;
}
