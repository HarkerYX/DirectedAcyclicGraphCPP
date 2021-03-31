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

//unsigned long long findOptimalPath(std::vector<adjNode *> topSortedVec){
//    std::vector<int> endingNodes;
//    std::map<int, unsigned long long> visitedMap;
//    std::map<int, std::vector<int>> tryThis;
//    std::map<double, int> calculatedClients;
//
//    std::map<double, int> clientsUsed;
//
//    std::vector<int> pathway;
//    for(int i = 0; i < topSortedVec.size(); i++){
//        clientsUsed[topSortedVec.at(i)->getWeight()] = topSortedVec.at(i)->getClientNumber();
//    }
//
//
//
//    std::vector<unsigned long long> weightsOfPath;
//
//    //Weights of path added to a vector.
//
//    for(int i = 0; i < topSortedVec.size(); i++){
//        adjNode *tempNode = topSortedVec.at(i);
//        adjNode *tempNodePlace = topSortedVec.at(i);
//
//        std::vector<int> pathFromNode;
//
//
//        if(topSortedVec.at(i)->next() == nullptr ){
//
//            weightsOfPath.emplace_back(topSortedVec.at(i)->getWeight());
//            visitedMap[topSortedVec.at(i)->getClientNumber()] = topSortedVec.at(i)->getWeight();
//            endingNodes.emplace_back(topSortedVec.at(i)->getClientNumber());
//
//            tryThis[topSortedVec.at(i)->getClientNumber()].emplace_back(topSortedVec.at(i)->getClientNumber());
//
//
//        }
//
//        else{
//            std::vector<unsigned long long> takeMaxOf;
//            double addToMax = tempNode->getWeight();
//
//            double bigCurr = tempNode->getWeight();
//            int currBig = tempNode->next()->getClientNumber();
//            pathFromNode.emplace_back(tempNodePlace->getClientNumber());
//
//            while(tempNode != nullptr){
//                tempNode = tempNode->next();
//                if(tempNode != nullptr) {
//                    takeMaxOf.emplace_back(visitedMap[tempNode->getClientNumber()]);
//                    if(tempNode->getWeight() > bigCurr){
//                        currBig = tempNode->getClientNumber();
//                    }
//                }
//
//            }
//            tryThis[topSortedVec.at(i)->getClientNumber()].emplace_back(currBig);
//
//
//            double max = *std::max_element(takeMaxOf.begin(), takeMaxOf.end());
////            calculatedClients[max] = tempNodePlace->getClientNumber();
//            addToMax = addToMax + max;
//            visitedMap[tempNodePlace->getClientNumber()] = addToMax;
//
//            weightsOfPath.emplace_back(addToMax);
//        }
//
//    }
//
//    int idxOfMax = std::distance(weightsOfPath.begin(), std::max_element(weightsOfPath.begin(), weightsOfPath.end()));
//    pathway.emplace_back(-1);
//    while( idxOfMax < topSortedVec.size() && topSortedVec.at(idxOfMax)->getClientNumber() != pathway.back() && !(std::find(pathway.begin(), pathway.end(), topSortedVec.at(idxOfMax)->getClientNumber()) != pathway.end()) ) {
//
//        pathway.emplace_back(topSortedVec.at(idxOfMax)->getClientNumber());
//
//        idxOfMax = tryThis[topSortedVec.at(idxOfMax)->getClientNumber()].at(0);
//
//    }
//    if(idxOfMax >= topSortedVec.size() && pathway.back() != idxOfMax){
//        pathway.emplace_back(idxOfMax);
//    };
//    std::cout << "The clients contributing to this revenue are: ";
//    for(int i = 1; i < pathway.size(); i++){
//        std::cout << pathway.at(i) << " ";
//        if(i != pathway.size()-1){std::cout << ", ";}
//    }
//    unsigned long long maxProfit = *std::max_element(weightsOfPath.begin(), weightsOfPath.end());
//    std::cout << "Max profit is: " << maxProfit << std::endl;
//    return maxProfit;
//}


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
//    for(int i = 0; i < clientList.size(); i++){
//        if(clientList.at(i).front() == idxOfMax){
            startClient = clientList.at(idxOfMax).front();
            contribClients.push_back(startClient);
            startHere = idxOfMax;
//        }
//    }
//    while(idxOfMax < clientList.size() && clientList.at(idxOfMax).size() != 1){
//        int goTo = clientList.at(idxOfMax).back();
//        contribClients.push_back(goTo);
//        idxOfMax = goTo;
//    }
//    contribClients.push_back(clientList.at(idxOfMax-1).front());

bool tortuga = true;

    while( tortuga){

        for(int i = 0; i < clientList.size(); i++){
            if(clientList.at(i).front() == startClient && clientList.at(i).size() == 1){
                tortuga = false;
                break;
            }
            else if(clientList.at(i).front() == startClient){

                startClient = clientList.at(i).back();
                contribClients.push_back(startClient);
            }

        }


//        int goTo = clientList.at(idxOfMax).back();
//        contribClients.push_back(goTo);
//        idxOfMax = goTo;
    }


//    contribClients.push_back(clientList.at(idxOfMax-1).front());

    for(int i=0; i<contribClients.size(); i++){
        std::cout << contribClients.at(i);
        if(i != contribClients.size()-1){
            std::cout << ",";
        }
    }

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

//    std::cout << "\n\nTOPOLOGICALLY SORTED:\n\n";

    topSortDFS(dagGraph, topSorted);

    std::cout << "\n";

//    std::cout << "Max profit: " << findOptimalPath(topSorted) << std::endl;

    findOptimalPath(topSorted);




    return 0;
}

