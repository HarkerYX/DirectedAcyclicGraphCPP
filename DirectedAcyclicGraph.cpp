//
// Created by Guy Greenleaf on 3/21/21.
//

#include "DirectedAcyclicGraph.hpp"


DirectedAcyclicGraph::DirectedAcyclicGraph(std::vector<CustomerInfo *> inputVec) {
    std::vector<adjNode *> nodeVector;

        auto *startNode = new adjNode(0, 0, 0, 0, 1);
        adjList.emplace_back(startNode);

    int place = 1;
    auto *endNode = new adjNode(0,0,0,0, 3);
    //Make a vector of all adjacency nodes
    for (auto & i : inputVec){
        auto *newNode = new adjNode(i->custNumber(), i->startDate(), i->endDate(), i->weight(), 2);
        adjList.emplace_back(newNode);

    }
    //Put the end node on
    adjList.emplace_back(endNode);
    //Build the list
    for(int i = 0; i<inputVec.size(); i++){


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

//    std::cout << "Initial adjacency list built...\nBuilding End...\n";

    //populate end
    auto *currentPlaceInEndList = adjList.at(adjList.size()-1);

    for(int i = 1; i < adjList.size()-1; i++){
        if(adjList.at(i)->next() == nullptr){
            auto *newNode = new adjNode(adjList.at(i)->getClientNumber(), adjList.at(i)->getStartDate(), adjList.at(i)->getEndDate(), adjList.at(i)->getWeight(), 2);
            newNode->next(currentPlaceInEndList->next());
            currentPlaceInEndList->next(newNode);
        }
    }

//    std::cout << "End node built..\nBuilding Start node...\n";

    //populate start

    bool comp = false;
    for(int i = 1; i < adjList.size()-1; i++){
        comp = false;
        for(int j = 1; j<adjList.size()-1; j++){
            if(adjList.at(i)->getStartDate() >= adjList.at(j)->getEndDate()){
                comp = true;
            }
        }
        if(!comp){
            auto *newStart = new adjNode(adjList.at(i)->getClientNumber(), adjList.at(i)->getStartDate(), adjList.at(i)->getEndDate(), adjList.at(i)->getWeight(), 1);
            newStart->next(adjList.at(0)->next());
            adjList.at(0)->next(newStart);
        }
    }


}


unsigned long long DirectedAcyclicGraph::nodeCount() {return adjList.size()-2;}

std::vector<int> DirectedAcyclicGraph::neighbors(int clientNum){
    std::vector<int> result;
    adjNode *getNeighborsOf = adjList.at(clientNum)->next();

    while(getNeighborsOf != nullptr){
        result.emplace_back(getNeighborsOf->getClientNumber());
        getNeighborsOf = getNeighborsOf->next();
    }

    return result;

}

std::vector<adjNode *> DirectedAcyclicGraph::getAdjList(){
    return adjList;
}

bool DirectedAcyclicGraph::getValue(int n) {
    return adjList.at(n)->getMarked();
}

void DirectedAcyclicGraph::setValue(int n) {
    adjList.at(n)->setMarked();
}
