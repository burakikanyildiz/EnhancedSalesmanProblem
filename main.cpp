#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include <vector>
#include "WeightedGraph.h"

using namespace std;


template<class Container>
void split1(const string& str, Container& cont){
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),back_inserter(cont));
}
int main(int argc, char* argv[]) {
    if(argc!=3){
        cout<<"Run the code with following command: ./project3 [input_file] [output_file]"<<endl;
        return 1;
    }
    ifstream infile(argv[1]);
    string line;
    getline(infile, line);
    vector<string> words;
    split1(line,words);
    const int numOfTowns=stoi(words[0]);
    WeightedGraph myGraph(numOfTowns);
    const int numOfRoads=stoi(words[1]);
    const int numofThieves=stoi(words[2]);
    const int numOfJews=stoi(words[3]);
    //loop to take information about Jewelers
    for(int i=0;i<numOfJews;i++){
        getline(infile, line);
        vector<string> words2;
        split1(line,words2);
        for(int k=2;k<stoi(words2[1])+2;k++) {
            myGraph.coins[stoi(words2[0])].push_back(stoi(words2[k]));
        }
    }
    //loop to take information about Roads
    for(int i=0;i<numOfRoads;i++){
        getline(infile,line);
        vector<string> words3;
        split1(line,words3);
        Road r(stoi(words3[2]),stoi(words3[3]));
        for(int k=4;k<stoi(words3[3])+4;k++){
            r.thieves.push_back(stoi(words3[k]));
        }
        myGraph.addUndirectedEdge(stoi(words3[0]),stoi(words3[1]),r);
    }

    cout<<"myGraph: "<<endl;
    myGraph.shortestPath(1,argv[2]);


    return 0;
}