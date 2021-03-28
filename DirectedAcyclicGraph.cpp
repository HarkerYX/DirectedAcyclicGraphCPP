//
// Created by Guy Greenleaf on 3/21/21.
//

#include "DirectedAcyclicGraph.hpp"
#include "adjNode.hpp"
#include <iostream>

DirectedAcyclicGraph::DirectedAcyclicGraph(std::vector<CustomerInfo *> inputVec) {
    std::vector<adjNode *> nodeVector;

    // Need to do this and the endNode after list is built
        auto *startNode = new adjNode(0, 0, 0, 0, 1);
        adjList.emplace_back(startNode);

    int place = 1;
    auto *endNode = new adjNode(0,0,0,0, 3);
    //Make a vector of all adjacency nodes
    for (int i = 0; i < inputVec.size(); i++){
        auto *newNode = new adjNode(inputVec.at(i)->custNumber(), inputVec.at(i)->startDate(), inputVec.at(i)->endDate(), inputVec.at(i)->weight(), 2);
        adjList.emplace_back(newNode);

    }
    //Put the end node on
    adjList.emplace_back(endNode);
    //Build the list
    for(int i = 1; i<inputVec.size(); i++){


        for(int j = 1; j < adjList.size()-1; j++) {
            adjNode *currListPlace = adjList.at(j);
            std::vector<int> checker;

            //Use this to track start nodes
            startVec.resize(adjList.size() , 0);

            if (adjList.at(i)->getStartDate() < adjList.at(j)->getStartDate() && i != 0 && i != adjList.size()) {

                startVec.at(j)++; }

            if ((currListPlace->getEndDate() <= inputVec.at(i)->startDate()) &&
                (currListPlace->getClientNumber() != inputVec.at(i)->custNumber())) {
                auto *newNode = new adjNode(inputVec.at(i)->custNumber(), inputVec.at(i)->startDate(),
                                            inputVec.at(i)->endDate(), inputVec.at(i)->weight(), 2);
                newNode->next(currListPlace->next());
                currListPlace->next(newNode);
            }
        }
    }


    std::cout << "Initial adjacency list built...\nBuilding End...\n";

    //populate end
    auto *currentPlaceInEndList = adjList.at(adjList.size()-1);

    for(int i = 1; i < adjList.size()-1; i++){
        if(adjList.at(i)->next() == nullptr){
            auto *newNode = new adjNode(adjList.at(i)->getClientNumber(), adjList.at(i)->getStartDate(), adjList.at(i)->getEndDate(), adjList.at(i)->getWeight(), 2);
            newNode->next(currentPlaceInEndList->next());
            currentPlaceInEndList->next(newNode);
        }
    }

    std::cout << "End node built..\nBuilding Start node...\n";

    //populate start

    bool comp = false;
    for(int i = 1; i < adjList.size()-1; i++){
        comp = false;
        for(int j = 1; j<adjList.size()-1; j++){
            if(adjList.at(i)->getStartDate() > adjList.at(j)->getEndDate()){
                comp = true;
            }
        }
        if(!comp){
            auto *newStart = new adjNode(adjList.at(i)->getClientNumber(), adjList.at(i)->getStartDate(), adjList.at(i)->getEndDate(), adjList.at(i)->getWeight(), 1);
            newStart->next(adjList.at(0)->next());
            adjList.at(0)->next(newStart);
        }
    }

//    for(int i = 1; i < startVec.size()-1; i++) {
//        if(startVec.at(i)==0) {
//            adjNode *insertNew = new adjNode(adjList.at(i)->getClientNumber(), adjList.at(i)->getStartDate(), adjList.at(i)->getEndDate(), adjList.at(i)->getWeight(), 2);
//            insertNew->next(adjList.at(0)->next());
//            adjList.at(0)->next(insertNew);
//        }
//
//    }

//
//    auto *currentStartPlace = adjList.at(0);
//
//    bool isFound = false;
//
//    for(int i = 1; i <adjList.size()-1; i++){
//        auto *currPlace = adjList.at(i);
//
//        for(int j = 1; j < adjList.size()-1; j++ ){
////            auto *innerPlace = new adjNode(adjList.at(j)->getClientNumber(), adjList.at(j)->getStartDate(), adjList.at(j)->getEndDate(), adjList.at(j)->getWeight());
//            auto *innerPlace = adjList.at(j);
//            if(i != j){
//                while(innerPlace != nullptr){
//                    if(innerPlace->getClientNumber() == currPlace->getClientNumber()){
//                        isFound = true;
//                        innerPlace = innerPlace->next();
//                    }
//                    else {
//                        innerPlace = innerPlace->next();
//                    }
//                }
//            }
//        }
//
//        if(!isFound){
//            auto *newNode = new adjNode(adjList.at(i)->getClientNumber(), adjList.at(i)->getStartDate(), adjList.at(i)->getEndDate(), adjList.at(i)->getWeight(), 2);
//            newNode->next(adjList.at(0)->next());
//            adjList.at(0)->next(newNode);
//            isFound = false;
//        }
//        isFound = false;
//        std::cout << i << " scanned out of " << adjList.size() << std::endl;
//    }

}

//might need to change, have it -2 to account for start and ending nodes atm.

unsigned long long DirectedAcyclicGraph::nodeCount() {return adjList.size()-2;}

std::vector<int> DirectedAcyclicGraph::neighbors(int clientNum){
    std::vector<int> result;
    adjNode *getNeighborsOf = adjList.at(clientNum)->next();


    while(getNeighborsOf != nullptr){
        result.emplace_back(getNeighborsOf->getClientNumber());
        getNeighborsOf = getNeighborsOf->next();
    }

    return result;
//    std::vector<adjNode *> neighborVec;
//
//    adjNode *getNeighborsOf = adjList.at(clientNum);
//
//    while(getNeighborsOf != nullptr){
//        neighborVec.emplace_back(getNeighborsOf);
//        getNeighborsOf = getNeighborsOf->next();
//    }
//    return neighborVec;
}

std::vector<adjNode *> DirectedAcyclicGraph::getAdjList(){
    return adjList;
}

void DirectedAcyclicGraph::topSort(){
    unsigned long long n = adjList.size()-2;
    visited.assign(n, false);
    for(int i = 0; i < n; i++){
        if(!visited.at(i)){
            topSortUtil(i);
        }
    }

    for(int i : answer){
        std::cout << i << std::endl;
    }

}

void DirectedAcyclicGraph::topSortUtil(int v) {
    visited.at(v) = true;
    int i;
    for( i = 1; i < adjList.size()-2; i++){
        if(!visited[i]){
            topSortUtil(i);
        }
    }
    answer.push_back(adjList.at(i)->getClientNumber());
}

int DirectedAcyclicGraph::getNodeType(int v) {
    return adjList.at(v)->getType();
}

bool DirectedAcyclicGraph::getValue(int n) {
    return adjList.at(n)->getMarked();
}

void DirectedAcyclicGraph::setValue(int n) {
    adjList.at(n)->setMarked();
}
