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

    return res;
}

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

vector<vector<Airport>> AuxiliarFunctions::bestFlightOp(vector<Airport> sourceAirports, vector<Airport> destAirports) {
    vector<Airport> aux;
    vector<vector<Airport>> best;

    for (auto s : sourceAirports) {
        for (auto d : destAirports) {
            aux = csvInfo::flightsGraph.pathAirport(s, d);

            if (aux.size() < best[0].size()) {
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