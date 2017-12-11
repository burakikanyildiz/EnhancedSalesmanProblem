//
// Created by abc on 9.12.2017.
//

#ifndef PROJECT3_BURAK_YILDIZ_2015400069_WEIGHTEDGRAPH_H
#define PROJECT3_BURAK_YILDIZ_2015400069_WEIGHTEDGRAPH_H

#include "Road.h"
#include <vector>
#include <list>
typedef pair<int, Road> iPair;
using namespace std;
class WeightedGraph {
public:
    int V;
    list<iPair> *adj;
    list<int> *coins;
    WeightedGraph(int V);
    void addUndirectedEdge(int u, int v,Road r);
    void shortestPath(int startNode);
};


#endif //PROJECT3_BURAK_YILDIZ_2015400069_WEIGHTEDGRAPH_H
