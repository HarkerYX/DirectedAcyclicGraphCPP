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



int main(int argc, char *argv[])
{

    //Put all customers info into a vector
    std::vector<CustomerInfo *> allCustomerInfo = createCustomerInfoVector(argc, argv);
    DirectedAcyclicGraph dagGraph(allCustomerInfo);

    std::cout << "testBuilt" << std::endl;

    std::cout << "Node Count: " <<  dagGraph.nodeCount() << std::endl;

    std::cout << "\n------------------\n\nAdjacency List:\n\n";
//
//    std::vector<adjNode *> neighborVector = dagGraph.neighbors(1);
//
//    std::cout << neighborVector.at(0)->getClientNumber() << std::endl;

//    for(int i = 0; i<dagGraph.nodeCount()+2; i++){
//        std::vector<adjNode *> neighbVec = dagGraph.neighbors(i);
//        for(auto & j : neighbVec){
//            std::cout << "[" << j->getStartDate() << ", " << j->getEndDate() << "]  " << "----> ";
//
//        }
//        std::cout << "|" << std::endl;
//    }

    std::cout << "TOP SORT!\n\n";

    topSort(dagGraph);

//    for(int i = 0; i < dagGraph.answer.size(); i++){
//        std::cout << dagGraph.answer.at(i) << std::endl;
//    }


    return 0;
}

