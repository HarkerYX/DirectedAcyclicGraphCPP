#include <iostream>

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <queue>
#include "CustomerInfo.hpp"
#include "DirectedAcyclicGraph.hpp"

//I did a project similar to this in CS315. A lot of similar concepts are brought into this project.



//Creates the vector of customer info.
std::vector<CustomerInfo *>createCustomerInfoVector(int argc, char *argv[]){
    std::vector<CustomerInfo *> custInfo;
    int startDate, endDate;
    double weight;

    int custNumber = 1;
    if( argc != 2) {
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile\n";
        exit(1);
    }
    std::ifstream inputStream;
    inputStream.open(argv[1], std::ios::in);
    if( ! inputStream.is_open()) {
        std::cout << "Unable top open " << argv[1] << ". Terminating...";
        perror("Error when attempting to open the input file.");
        exit(1);
    }

    while(inputStream >> startDate && inputStream >> endDate && inputStream >> weight){
        auto *customersInfo = new CustomerInfo(custNumber, startDate, endDate, weight);
        custNumber += 1;
        custInfo.push_back(customersInfo);
    }
    return custInfo;
}

//just redo this shit tomorrow tbh.....
void topSort(DirectedAcyclicGraph graph){
    std::queue<adjNode *> adjQueue;
    //Might need to +2 on the nodeCount!
    std::vector<int> count (graph.nodeCount(), 0);
    std::vector<int> nList;
    int v;

    for(v=0; v<graph.nodeCount(); v++){count.at(v) = 0;}

    for(v=1; v<graph.nodeCount(); v++){
        nList = graph.neighbors(v);

        for(int i=0; i < nList.size(); i++){
            count.at(nList.at(i)-1)++;
        }
    }
    for(v = 0; v<graph.nodeCount(); v++){
        if(count.at(v) == 0){
            adjQueue.push(graph.getAdjList().at(v));
        }

    }
    while(adjQueue.size() > 0){
        auto *print = adjQueue.front();

        std::cout << "[" << print->getStartDate() << ", "<< print->getEndDate() << "]" << std::endl;
    std::cout << print->getWeight() << std::endl;
    std::cout << "----------------------\n";
        adjQueue.pop();
        nList = graph.neighbors(v);

        for(int i = 0; i< nList.size(); i++){
            count.at(nList.at(i))--;
            if(count.at(nList.at(i)) == 0){
                adjQueue.push(graph.getAdjList().at(nList.at(i)));
            }
        }
    }
}

void topHelp(DirectedAcyclicGraph graph, int v){
    graph.setValue(v);
    std::vector<int> neighborList = graph.neighbors(v);

    for(int i = 0; i < neighborList.size(); i++){
        if(!graph.getValue(neighborList.at(i))){
            topHelp(graph, neighborList.at(i));
        }
    }
    std::cout << graph.getAdjList().at(v)->getStartDate() << " " << graph.getAdjList().at(v)->getEndDate()  << " , ";
}

void topSortDFS(DirectedAcyclicGraph graph){
    int v;
    for(v=1; v<graph.nodeCount(); v++){
        if(!graph.getValue(v)){
            topHelp(graph, v);
        }
    }

}



int main(int argc, char *argv[]) {

    //Put all customers info into a vector
    std::vector<CustomerInfo *> allCustomerInfo = createCustomerInfoVector(argc, argv);
    DirectedAcyclicGraph dagGraph(allCustomerInfo);

    std::cout << "testBuilt" << std::endl;

    std::cout << "Node Count: " << dagGraph.nodeCount() << std::endl;

    std::cout << "\n------------------\n\nAdjacency List:\n\n";
//
//    std::vector<adjNode *> neighborVector = dagGraph.neighbors(1);
//
//    std::cout << neighborVector.at(0)->getClientNumber() << std::endl;

//Print out the adjacency list representation
    for (int i = 0; i < dagGraph.nodeCount() + 2; i++) {
        std::vector<int> neighbVec = dagGraph.neighbors(i);
        if (dagGraph.getAdjList().at(i)->getType() == 2) {
            std::cout << "[" << dagGraph.getAdjList().at(i)->getStartDate() << ", "
                      << dagGraph.getAdjList().at(i)->getEndDate() << "]" << " Neighbors: ";
        } else if (dagGraph.getAdjList().at(i)->getType() == 1) {
            std::cout << "[" << "START" << "]" << " Neighbors: ";
        } else {
            std::cout << "[" << "END" << "]" << " Neighbors: ";

        }
        for (int j : neighbVec) {
            std::cout << "[" << dagGraph.getAdjList().at(j)->getStartDate() << ", "
                      << dagGraph.getAdjList().at(j)->getEndDate() << "]  " << "----> ";

        }
        std::cout << "|" << std::endl;
    }

    std::cout << "\n\nTOP SORT:\n\n";

    topSortDFS(dagGraph);

    std::cout << "Neighbors:\n\n";
    auto neighbs = dagGraph.neighbors(1);
    for (auto j : neighbs) {
    std::cout << "Neighbors of index 1: " << j << std::endl;
}
//    for(int i = 0; i < dagGraph.answer.size(); i++){
//        std::cout << dagGraph.answer.at(i) << std::endl;
//    }


    return 0;
}

