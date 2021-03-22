#include <iostream>

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <list>

#include <map>
#include "DirectedAcyclicGraph.hpp"





// stores adjacency list items

// structure to store edges
struct graphEdge {
    int start_ver, end_ver, weight;

};






int main()
{



    std::ifstream input( "data2.txt" );
//    std::string line;
    std::vector< std::vector<int> > all_integers;

    std::vector<std::vector<int>> dagMatrix;

    int start, end, cost;


    while(input >> start >> end >> cost)
    {
        std::vector<int> toappend;
        toappend.push_back(start);
        toappend.push_back(end);
        toappend.push_back(cost);

        all_integers.push_back(toappend);

    }

//    std::vector<std::list<std::tuple<int, int, int>>> dagList(all_integers.size());

    dagMatrix.resize(all_integers.size(), std::vector<int>(all_integers.size()));

    std::cout << dagMatrix.size() << std::endl;
//    std::ifstream input2( "data2.txt" );
//
//    while(input2 >> start >> end >> cost) {
//
//        std::cout << start << " " << end << " " << cost << endl;
//    }
//        for (int i=0; i<all_integers.size()-1; i++){
//        cout << all_integers.at(i).at(0)  << " " <<  all_integers.at(i).at(1) << " " << all_integers.at(i).at(2) << endl;
//    }
//
//
//
//    int numVertices = all_integers.size();      // Number of vertices in the graph
//
//
//
    DirectedAcyclicGraph graph(all_integers);

    for(int i = 0; i < graph.getAdjList().size(); i++){
        for(int j = 0; j< graph.getAdjList().size(); j++){
            std::cout << graph.getAdjList().at(i).at(j).getMarked();
            if(j == 4){
                std::cout << std::endl;
            }
        }
    }
    return 0;
}

