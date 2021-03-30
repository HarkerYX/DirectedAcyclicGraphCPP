#include <iostream>
#include <algorithm>
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

//I did a project similar to this in CS315. A lot of similar concepts and ideas are brought into this project.


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

void topHelp(DirectedAcyclicGraph graph, int v, std::vector<adjNode *> &someVec){
    graph.setValue(v);
    std::vector<int> neighborList = graph.neighbors(v);

    for(int i = 0; i < neighborList.size(); i++){
        if(!graph.getValue(neighborList.at(i))){
            topHelp(graph, neighborList.at(i), someVec);
        }
    }
    someVec.emplace_back(graph.getAdjList().at(v));
//    std::cout << graph.getAdjList().at(v)->getStartDate() << " " << graph.getAdjList().at(v)->getEndDate()  << " , ";
}

void topSortDFS(DirectedAcyclicGraph graph, std::vector<adjNode *> &sortVector){
    std::vector<adjNode *> returnVec;
    std::vector<int> optimalClients;

    int v;
    for(v=1; v<graph.nodeCount(); v++){
        if(!graph.getValue(v)){
            topHelp(graph, v, sortVector);
        }
    }

}

unsigned long long findOptimalPath(std::vector<adjNode *> topSortedVec){
    std::vector<int> endingNodes;
    std::map<int, unsigned long long> visitedMap;

    std::map<double, int> calculatedClients;

    std::map<double, int> clientsUsed;

    for(int i = 0; i < topSortedVec.size(); i++){
        clientsUsed[topSortedVec.at(i)->getWeight()] = topSortedVec.at(i)->getClientNumber();
    }



    std::vector<unsigned long long> weightsOfPath;

    //Weights of path added to a vector.

    for(int i = 0; i < topSortedVec.size(); i++){
        adjNode *tempNode = topSortedVec.at(i);
        adjNode *tempNodePlace = topSortedVec.at(i);

        std::vector<int> pathFromNode;


        if(topSortedVec.at(i)->next() == nullptr ){

            weightsOfPath.emplace_back(topSortedVec.at(i)->getWeight());
            visitedMap[topSortedVec.at(i)->getClientNumber()] = topSortedVec.at(i)->getWeight();
            endingNodes.emplace_back(topSortedVec.at(i)->getClientNumber());



        }

        else{
            std::vector<unsigned long long> takeMaxOf;
            double addToMax = tempNode->getWeight();

            pathFromNode.emplace_back(tempNodePlace->getClientNumber());

            while(tempNode != nullptr){
                tempNode = tempNode->next();
                if(tempNode != nullptr) {
                    takeMaxOf.emplace_back(visitedMap[tempNode->getClientNumber()]);

                }

            }


            double max = *std::max_element(takeMaxOf.begin(), takeMaxOf.end());
//            calculatedClients[max] = tempNodePlace->getClientNumber();
            addToMax = addToMax + max;
            visitedMap[tempNodePlace->getClientNumber()] = addToMax;

            weightsOfPath.emplace_back(addToMax);
        }

    }


    unsigned long long maxProfit = *std::max_element(weightsOfPath.begin(), weightsOfPath.end());

    return maxProfit;
}




//unsigned long long findOptimalPath(std::vector<adjNode *> topSortedVec){
//   int maxProfit = 0;
//   std::vector<adjNode *> clientVector = topSortedVec;
//   std::map<int, int> clientNumToIndex;
//   //     [  (cliNum, index), (cliNum, index), ...  ]
//
//   std::vector<int> storeWeights;
//
//   std::vector<int> endWeights;
//   std::map<int, int> holdEndWeights;
//
//   for(int i = 0; i < clientVector.size(); i++){
//       clientNumToIndex[clientVector.at(i)->getClientNumber()] = i;
//   }
//
//   for(int i = 0; i < clientVector.size(); i++){
//       if(clientVector.at(i)->next() == nullptr){
//           storeWeights.emplace_back(clientVector.at(i)->getWeight());
//           holdEndWeights[clientVector.at(i)->getClientNumber()] = clientVector.at(i)->getWeight();
//       }
//       else{
//
//       }
//   }
//    return maxProfit;
//}

int main(int argc, char *argv[]) {
    std::vector<adjNode *> topSorted;

    //Put all customers info into a vector
    std::vector<CustomerInfo *> allCustomerInfo = createCustomerInfoVector(argc, argv);
    //Make the DAG
    DirectedAcyclicGraph dagGraph(allCustomerInfo);


    // UNCOMMENT BELOW THIS LINE TO OUTPUT THE ADJACENCY LIST REPRESENTATION TO A FILE
    std::cout << "\n------------------\n\nAdjacency List:\n\n";
    std::ofstream graphWriter;
    graphWriter.open("Graph.txt");
    for (int i = 0; i < dagGraph.nodeCount() + 2; i++) {
        std::vector<int> neighbVec = dagGraph.neighbors(i);
        if (dagGraph.getAdjList().at(i)->getType() == 2) {
            graphWriter << "[" << dagGraph.getAdjList().at(i)->getStartDate() << ", "
                      << dagGraph.getAdjList().at(i)->getEndDate() << "]" << " Neighbors: ";
        } else if (dagGraph.getAdjList().at(i)->getType() == 1) {
            graphWriter << "[" << "START" << "]" << " Neighbors: ";
        } else {
            graphWriter << "[" << "END" << "]" << " Neighbors: ";

        }
        for (int j : neighbVec) {
            graphWriter << "[" << dagGraph.getAdjList().at(j)->getClientNumber() << ", " << dagGraph.getAdjList().at(j)->getStartDate() << ", "
                      << dagGraph.getAdjList().at(j)->getEndDate() << ", " <<
                      dagGraph.getAdjList().at(j)->getWeight() << "]  " << "----> ";

        }
        graphWriter << "|" << std::endl;
    }

    graphWriter.close();

    std::cout << "There are " << dagGraph.numClients() << " clients in this file." << std::endl;

//    std::cout << "\n\nTOPOLOGICALLY SORTED:\n\n";

    topSortDFS(dagGraph, topSorted);

    std::cout << "\n";

    std::cout << "Max profit: " << findOptimalPath(topSorted) << std::endl;




    return 0;
}

