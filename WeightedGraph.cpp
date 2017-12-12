//
// Created by abc on 9.12.2017.
//

#include "WeightedGraph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
#include <fstream>

# define INF 0x3f3f3f3f
typedef pair<int, int> pair2;
//distance based comparision for priority queue
template<typename type>
struct myCompDistance {
    bool operator()(const type & first, const type & second) const  {
        return first.first > second.first;
    }
};

//return whether we have the required coin as walking on the road
bool canGo(unordered_set<int> setx , Road r){
    for(int i=0;i<r.numOfThieves;i++){
        if(setx.find(r.thieves[i])!=setx.end()) {
        }else{
            return false;
        }
    }
    return true;
}
//return whether we will have new coin(s) if we go through the road
bool newCoin(unordered_set<int> &coinH1 ,unordered_set<int> &coinH2){
    unordered_set<int>::iterator itrC;
    for(itrC=coinH1.begin(); itrC!=coinH1.end() ; ++itrC) {
        if (coinH2.find(*itrC)==coinH2.end()) {
            return true;
        }
    }
    return false;
}
WeightedGraph::WeightedGraph(int V) {
    this->V=V;
    this->adj=new list<iPair>[V+1];
    this->coins=new list<int>[V+1];
}

void WeightedGraph::addUndirectedEdge(int u, int v, Road r) {
    adj[u].push_back(make_pair(v,r));
    adj[v].push_back(make_pair(u,r));
}

void WeightedGraph::shortestPath(int startNode,char* k) {
    //initializations

    string sArr[V+1];
    bool isOk[V+1];
    priority_queue<pair2,vector<pair2>,myCompDistance<pair2>> pq;
    int distance[V+1];
    for(int i=0; i<V+1;i++){
        distance[i]=INF;
        isOk[i]=false;
        sArr[i]=to_string(-1);
    }
    unordered_set<int> coinsHave[V+1];
    sArr[startNode]=to_string(startNode)+" ";
    cout<<sArr[startNode]<<endl;
    distance[startNode]=0;
    for(list< int >::const_iterator ikra=coins[startNode].begin();ikra!=coins[startNode].end();++ikra){
        coinsHave[startNode].insert(*ikra);
    }
    pq.push(make_pair(distance[startNode],startNode));

    //main loop process until find the path to the destination or there is no new possible iteration
    while(!isOk[V] && !pq.empty()){
        int currNode=pq.top().second;
        pq.pop();
        isOk[currNode]=true;
        list<iPair>::iterator itr2;
        //iterate through the adjancies of the Current Node
        for(itr2=adj[currNode].begin();itr2!=adj[currNode].end();++itr2) {
            int currNeighbor = (*itr2).first;
            Road currRoad = (*itr2).second;
            if (canGo(coinsHave[currNode], currRoad)) {
                if (isOk[currNeighbor]) {
                    //will we get new coin by going this path or can we decrease the distance
                    if ( newCoin(coinsHave[currNode],coinsHave[currNeighbor]) || distance[currNeighbor] > distance[currNode] + currRoad.weight) {
                        distance[currNeighbor] = distance[currNode] + currRoad.weight;
                        unordered_set<int>::iterator it;
                        for(it=coinsHave[currNode].begin();it!=coinsHave[currNode].end();++it){
                            coinsHave[currNeighbor].insert(*it);
                        }
                        if(!this->coins[currNeighbor].empty()){
                            for(auto l=this->coins[currNeighbor].begin();l!=this->coins[currNeighbor].end();++l){
                                coinsHave[currNeighbor].insert(*l);
                            }
                        }
                        sArr[currNeighbor]=sArr[currNode]+to_string(currNeighbor)+" ";
                        pq.push(make_pair(distance[currNeighbor],currNeighbor));
                    }
                }else{
                    //can we decrease the distance between the nodes
                    if (distance[currNeighbor] > distance[currNode] + currRoad.weight ) {
                        distance[currNeighbor] = distance[currNode] + currRoad.weight;
                        unordered_set<int>::iterator it;
                        for(it=coinsHave[currNode].begin();it!=coinsHave[currNode].end();++it){
                            coinsHave[currNeighbor].insert(*it);
                        }
                        if(!this->coins[currNeighbor].empty()){
                            for(auto l=this->coins[currNeighbor].begin();l!=this->coins[currNeighbor].end();++l){
                                coinsHave[currNeighbor].insert(*l);
                            }
                        }
                        sArr[currNeighbor]=sArr[currNode]+to_string(currNeighbor)+" ";
                        pq.push(make_pair(distance[currNeighbor],currNeighbor));
                    }
                }
            }
        }
    }
    ofstream myfile;
    myfile.open(k, ios::trunc);
    myfile<<sArr[V];
    myfile.close();
    cout<<"distance["<<V<<"] is: "<<distance[V]<<endl;

}
