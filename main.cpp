#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include "CustomerInfo.hpp"
#include "DirectedAcyclicGraph.hpp"

//Creates the vector of customer info.
std::vector<CustomerInfo *>createCustomerInfoVector(const std::string& input){

    std::vector<CustomerInfo *> custInfo;
    int startDate, endDate;
    double weight;

    int custNumber = 1;

    std::ifstream  inputFile;

    inputFile.open(input, std::ios::in);

    if( ! inputFile.is_open()) {
        std::cout << "Unable top open input file..." << "Terminating...";

        exit(2);
    }
//    if(inputFile.fail()){
//        std::cout << "File does not exist or is not in the 'data' directory...terminating...";
//        exit(1);
//    }

    while(inputFile >> startDate && inputFile >> endDate && inputFile >> weight){
        auto *customersInfo = new CustomerInfo(custNumber, startDate, endDate, weight);
        custNumber += 1;
        custInfo.push_back(customersInfo);
    }
    inputFile.close();
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
std::vector<int> findOptimalPath(std::vector<adjNode *> topSortedVec, int &rev){
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
//
//    rev = maxNeighborForClients.at(idxOfMax);

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
    return contribClients;
}


int main(int argc, char *argv[]) {


    //Check to make sure a file has been passed in as an argument
    if( argc != 2 ) {
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile" << std::endl;
        exit(1);
    }

    std::string userInput(argv[1]);

    //Strip file extension and format output file name
    size_t lastIdx = userInput.find_last_of('.');
    userInput = userInput.substr(0, lastIdx);
    std::string outputName = userInput + "Output.txt";
    userInput += ".txt";

    int revenue;
    std::vector<adjNode *> topSorted;

    //Put all customers info into a vector
    std::vector<CustomerInfo *> allCustomerInfo= createCustomerInfoVector(argv[1]);


    //Make the DAG -- ADJACENCY LIST REPRESENTATION
    DirectedAcyclicGraph dagGraph(allCustomerInfo);
    std::cout << std::endl;


    std::cout << "Input read from: " << userInput << "\n" <<  std::endl;
    std::cout << "There are " << dagGraph.numClients() << " clients in this file." << std::endl;
    topSortDFS(dagGraph, topSorted);

    std::cout << "\n";
    std::vector<int> result = findOptimalPath(topSorted, revenue);
        for(int i=0; i<result.size(); i++){
        std::cout << result.at(i);
        if(i != result.size()-1){
            std::cout << ",";
        }
    }

//        int revRev=0;
//        for(int i=0; i < result.size(); i++){
//            revRev += allCustomerInfo.at(result.at(i)-1)->weight();
//        }
//        std::cout << "\nOptimal Revenue Earned From Clients: " << revRev;

    std::ofstream userOutput;
    userOutput.open(outputName);
    userOutput << "Input read from: " << userInput << "\n" <<  std::endl;
    userOutput << "There are " << dagGraph.numClients() << " clients in this file." << std::endl;
    userOutput << "Optimal revenue: " << revenue << std::endl;
    userOutput << "Clients contributing to the optimal revenue: ";

    for(int i=0; i<result.size(); i++){
        userOutput << result.at(i);
        if(i != result.size()-1){
            userOutput << ",";
        }
    }

    userOutput.close();

    //Ask user if they want to output the adjacency list representation in a txt file
    std::cout << "\n=============================================================" << std::endl;

    std::string userGraph;
    std::cout << "\nWould you like to output the adjacency list representation to a text file?\n1.yes\n2.no" << std::endl;
    std::cin >> userGraph;
    if(userGraph == "1") {
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
                graphWriter << "[" << dagGraph.getAdjList().at(j)->getClientNumber() << ", "
                            << dagGraph.getAdjList().at(j)->getStartDate() << ", "
                            << dagGraph.getAdjList().at(j)->getEndDate() << ", " <<
                            dagGraph.getAdjList().at(j)->getWeight() << "]  " << "----> ";

            }
            graphWriter << "|" << std::endl;
        }

        graphWriter.close();
    }

    else{
        std::cout << "Terminating...";
    }


    return 0;
}




