#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include "CustomerInfo.hpp"
#include "DirectedAcyclicGraph.hpp"

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

//Topological Sort Helper
void topHelp(DirectedAcyclicGraph graph, int v, std::vector<adjNode *> &someVec){
    graph.setValue(v);
    std::vector<int> neighborList = graph.neighbors(v);

    for(int i : neighborList){
        if(!graph.getValue(i)){
            topHelp(graph, i, someVec);
        }
    }
    someVec.emplace_back(graph.getAdjList().at(v));
//    std::cout << graph.getAdjList().at(v)->getStartDate() << " " << graph.getAdjList().at(v)->getEndDate()  << " , ";
}

//Top Sort DFS
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

//Optimal Path Finder
void findOptimalPath(std::vector<adjNode *> topSortedVec){
    std::vector<adjNode *> copyOf = topSortedVec;

    std::vector<int> contributorsIndex;

    std::map<int, int> calculatedSoFar;

    std::vector<int> maxNeighborForClients(topSortedVec.size(), 0);

    std::vector<std::list<int>> clientList;

    for(auto & i : topSortedVec){
        std::list<int> appToVec(1, i->getClientNumber());
        clientList.emplace_back(appToVec);
    }

    for(int i=0; i< topSortedVec.size(); i++){

        if(topSortedVec.at(i)->next() == nullptr){
            calculatedSoFar[topSortedVec.at(i)->getClientNumber()] = topSortedVec.at(i)->getWeight();
            maxNeighborForClients[i]=topSortedVec.at(i)->getWeight();
        }
        else{
            std::vector<int> currNeighbors;
            std::vector<adjNode *> neighborVector;
            adjNode *currPlace = topSortedVec.at(i)->next();
            double weightCheck = currPlace->getWeight();
            int maxNeighbor = currPlace->getClientNumber();

            while(currPlace != nullptr){
               currNeighbors.emplace_back(calculatedSoFar[currPlace->getClientNumber()]);
               neighborVector.emplace_back(currPlace);
               if(weightCheck < calculatedSoFar[currPlace->getClientNumber()]){
                   weightCheck = currPlace->getWeight();
                   maxNeighbor = currPlace->getClientNumber();
               }

                currPlace = currPlace->next();
            }
            clientList.at(i).emplace_back(maxNeighbor);

            int maxOfNeighbors = *std::max_element(currNeighbors.begin(), currNeighbors.end());
            calculatedSoFar[topSortedVec.at(i)->getClientNumber()] = maxOfNeighbors + topSortedVec.at(i)->getWeight();
            maxNeighborForClients[i]=maxOfNeighbors + topSortedVec.at(i)->getWeight();
            currNeighbors.clear();

        }

    }
    int idxOfMax = std::distance(maxNeighborForClients.begin(), std::max_element(maxNeighborForClients.begin(), maxNeighborForClients.end()));


    std::cout << "Optimal revenue earned is " << maxNeighborForClients.at(idxOfMax) << std::endl;

    std::cout << "Clients contributing to this optimal revenue: ";

    std::vector<int> contribClients;
    int startClient;
    int startHere;
    startClient = clientList.at(idxOfMax).front();
    contribClients.push_back(startClient);
    startHere = idxOfMax;

    bool keepGoing = true;

    while( keepGoing){

        for(auto & i : clientList){
            if(i.front() == startClient && i.size() == 1){
                keepGoing = false;
                break;
            }
            else if(i.front() == startClient){

                startClient = i.back();
                contribClients.push_back(startClient);
            }
        }
    }

    for(int i=0; i<contribClients.size(); i++){
        std::cout << contribClients.at(i);
        if(i != contribClients.size()-1){
            std::cout << ",";
        }
    }

}


int main(int argc, char *argv[]) {
    std::vector<adjNode *> topSorted;

    //Put all customers info into a vector
    std::vector<CustomerInfo *> allCustomerInfo = createCustomerInfoVector(argc, argv);
    //Make the DAG -- ADJACENCY LIST REPRESENTATION
    DirectedAcyclicGraph dagGraph(allCustomerInfo);


    // UNCOMMENT BELOW THIS LINE TO OUTPUT THE ADJACENCY LIST REPRESENTATION TO A FILE
//    std::cout << "\n------------------\n\nAdjacency List:\n\n";
//    std::ofstream graphWriter;
//    graphWriter.open("Graph.txt");
//    for (int i = 0; i < dagGraph.nodeCount() + 2; i++) {
//        std::vector<int> neighbVec = dagGraph.neighbors(i);
//        if (dagGraph.getAdjList().at(i)->getType() == 2) {
//            graphWriter << "[" << dagGraph.getAdjList().at(i)->getStartDate() << ", "
//                      << dagGraph.getAdjList().at(i)->getEndDate() << "]" << " Neighbors: ";
//        } else if (dagGraph.getAdjList().at(i)->getType() == 1) {
//            graphWriter << "[" << "START" << "]" << " Neighbors: ";
//        } else {
//            graphWriter << "[" << "END" << "]" << " Neighbors: ";
//
//        }
//        for (int j : neighbVec) {
//            graphWriter << "[" << dagGraph.getAdjList().at(j)->getClientNumber() << ", " << dagGraph.getAdjList().at(j)->getStartDate() << ", "
//                      << dagGraph.getAdjList().at(j)->getEndDate() << ", " <<
//                      dagGraph.getAdjList().at(j)->getWeight() << "]  " << "----> ";
//
//        }
//        graphWriter << "|" << std::endl;
//    }
//
//    graphWriter.close();

    std::cout << "There are " << dagGraph.numClients() << " clients in this file." << std::endl;
    topSortDFS(dagGraph, topSorted);
    std::cout << "\n";
    findOptimalPath(topSorted);
    return 0;
}

