//
// Created by abc on 9.12.2017.
//

#ifndef PROJECT3_BURAK_YILDIZ_2015400069_ROAD_H
#define PROJECT3_BURAK_YILDIZ_2015400069_ROAD_H

#include <vector>
using namespace std;
class Road {
public:
    int weight;
    int numOfThieves;
    vector<int> thieves;
    Road(int weight,int numberOfThieves);
};


#endif //PROJECT3_BURAK_YILDIZ_2015400069_ROAD_H
