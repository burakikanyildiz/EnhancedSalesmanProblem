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
    int V;  //number of vertices
    list<iPair> *adj;   //list array to hold adjacencies of each vertex
    list<int> *coins;   //list array to hold coins in each vertex
    WeightedGraph(int V);//constructor
    void addUndirectedEdge(int u, int v,Road r);
    void shortestPath(int startNode,char* k);// performs the full process of finding shortest path
};


#endif //PROJECT3_BURAK_YILDIZ_2015400069_WEIGHTEDGRAPH_H
