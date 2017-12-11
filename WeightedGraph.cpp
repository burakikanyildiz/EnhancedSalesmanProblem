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
struct distnCoin{
    int distance;
    unordered_set<int> coinsHave;
    distnCoin(){
        distance=INF;
    }
};
template<typename type>
struct myCompDistance {
    bool operator()(const type & first, const type & second) const  {
        return first.first > second.first;
    }
};

//yolun üstünden giderken gereken coin bizde var mı?
bool canGo(unordered_set<int> setx , Road r){
    for(int i=0;i<r.numOfThieves;i++){
        if(setx.find(r.thieves[i])!=setx.end()) {

        }else{
    //        cout<<"distancesi "<<r.weight<<" olan yoldan gidemem "<<r.thieves[i]<<" no'lu hirsiz var"<<endl;
            return false;
        }
    }
  // cout<<"distancesi "<<r.weight<<" olan yoldan gidiyorum"<<endl;
    return true;
}
//gidince yeni coin gelecek mi?
bool newCoin(unordered_set<int> &coinH1 ,unordered_set<int> &coinH2){
    //cout<<"girdik1"<<endl;
    unordered_set<int>::iterator itrC;
    //cout<<coinH1.size()<<endl;
    for(itrC=coinH1.begin(); itrC!=coinH1.end() ; ++itrC) {
        //cout<<"girdik2"<<endl;
        if (coinH2.find(*itrC)==coinH2.end()) {
           // cout << "yeni coin gelecek BABAĞ" << endl;
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

void WeightedGraph::shortestPath(int startNode) {
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

    //initialize
    sArr[startNode]=to_string(startNode)+" ";
    cout<<sArr[startNode]<<endl;
    distance[startNode]=0;
    for(list< int >::const_iterator ikra=coins[startNode].begin();ikra!=coins[startNode].end();++ikra){
        coinsHave[startNode].insert(*ikra);
    }
    pq.push(make_pair(distance[startNode],startNode));
    while(!isOk[V] && !pq.empty()){
        int currNode=pq.top().second;
        pq.pop();
        isOk[currNode]=true;
        list<iPair>::iterator itr2;
       // int a=0;
        for(itr2=adj[currNode].begin();itr2!=adj[currNode].end();++itr2) {
        //    cout<<++a<<endl;
            int currNeighbor = (*itr2).first;
            Road currRoad = (*itr2).second;
            if (canGo(coinsHave[currNode], currRoad)) {
                if (isOk[currNeighbor]) {
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
    myfile.open("C:\\Users\\abc\\Desktop\\outputs\\Fuzoutput3.txt", ios::trunc);
    myfile<<sArr[V];
   // cout<<sArr[V]<<endl;
    cout<<"distance["<<V<<"] is: "<<distance[V]<<endl;









    /*
    vector<vector<distnCoin>> dis;
    priority_queue<pair2> pq;

    pq.push(make_pair(0,startNode));
    cout<<dis[startNode].data()->distance<<endl;
    dis[startNode].data()->distance=0;
    cout<<"SA"<<endl;

    while(!pq.empty()){
        int currNode=pq.top().second;
        pq.pop();

        list<iPair>::iterator itr;
        for(itr=adj[currNode].begin();itr!=adj[currNode].end();itr++){
            int currNeighbor = (*itr).first;
            Road currRoad = (*itr).second;
            if(dis[currNeighbor].data()->distance > dis[currNode].data()->distance+currRoad.weight){
                if(helperFunc1(currNode,dis,currRoad)) {
                    dis[currNeighbor].data()->distance = dis[currNode].data()->distance + currRoad.weight;
                    list<int>::iterator itr2;
                    for(itr2=coins[currNeighbor].begin();itr2!=coins[currNeighbor].end();itr2++){
                        dis[currNode].data()->coinsHave.insert(*itr2);
                    }
                    pq.push(make_pair(dis[currNeighbor].data()->distance,currNeighbor));
                }
            }
        }
    }*/
   // printf("Vertex   Distance from Source %d \n",startNode);
   // for (int i = 0; i < V; ++i)
   //     printf("%d \t\t %d\n", i, dis[i].data()->distance);
}
