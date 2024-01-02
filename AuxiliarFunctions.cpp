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
 * @brief Perform depth-first search to find articulation points in the graph.
 *
 * Complexity: O(n)
 *
 * @param g : Pointer to the graph.
 * @param v : Pointer to the current vertex.
 * @param s : Reference to the stack used in DFS.
 * @param res : Reference to the vector storing articulation points.
 * @param i : Reference to the current index in DFS.
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
    vector<vector<Vertex*>> aux;
    vector<vector<Airport>> best;
    vector<Airport> aux2;


    for (const Airport& s : sourceAirports) {
        for (const Airport& d : destAirports) {
            aux = csvInfo::flightsGraph.pathAirport(s, d);
            for (const auto& a : aux){
                for (auto b : a){
                    auto c = b->getAirport();
                    aux2.push_back(c);
                }
                if (!count(best.begin(),best.end(),aux2)) {
                    best.push_back(aux2);
                }
                aux2.clear();
            }

        }
    }
    return best;
}

vector<vector<Airport>>
AuxiliarFunctions::filterVectorAirlines(const vector<Airport>& sourceAirports, const vector<Airport>& destAirports, const vector<string>& airlines) {
    vector<vector<Vertex*>> aux;
    vector<vector<Airport>> best;
    vector<Airport> aux2;


    for (const Airport& s : sourceAirports) {
        for (const Airport& d : destAirports) {
            aux = csvInfo::flightsGraph.pathAirportRestrictAirlines(s, d, airlines);
            for (const auto& a : aux){
                for (auto b : a){
                    auto c = b->getAirport();
                    aux2.push_back(c);
                }
                if (!count(best.begin(),best.end(),aux2)) {
                    best.push_back(aux2);
                }
                aux2.clear();
            }

        }
    }
    return best;
}

vector<vector<Airport>>
AuxiliarFunctions::filterNumAirlines(const vector<Airport>& sourceAirports, const vector<Airport>& destAirports, int numAir) {
    vector<pair<vector<Vertex*>,int>> aux;
    vector<vector<Airport>> best;
    vector<Airport> aux2;


    for (const Airport& s : sourceAirports) {
        for (const Airport& d : destAirports) {
            aux = csvInfo::flightsGraph.pathAirportNumAirlines(s, d, numAir);
            for (const auto& a : aux) {
                if (a.second <= numAir) {
                    for (auto b : a.first) {
                        auto c = b->getAirport();
                        aux2.push_back(c);
                    }
                    if (!count(best.begin(),best.end(),aux2)) {
                        best.push_back(aux2);
                    }
                    aux2.clear();
                }
            }

        }
    }
    return best;
}
