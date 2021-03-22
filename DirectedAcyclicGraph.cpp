//
// Created by Guy Greenleaf on 3/21/21.
//

#include "DirectedAcyclicGraph.hpp"
#include "adjNode.hpp"

DirectedAcyclicGraph::DirectedAcyclicGraph(std::vector<std::vector<int>> inputVec) {
    std::vector<adjNode> nodeVector;

    int place = 1;
    //Make a vector of all adjacency nodes
    for (auto & i : inputVec){
        adjNode newNode(place, i.at(0),i.at(1), i.at(2));

        nodeVector.emplace_back(newNode);
        ++place;
    }

    //Make the adjacency matrix
    adjMatrix.resize(inputVec.size(), std::vector<adjNode>(inputVec.size()));

    for(int i = 0; i < adjMatrix.size(); i++){
        for(int j = i+1; j < adjMatrix.size(); j++){
            if (inputVec[i][1] <= inputVec[j][0]){
                    adjMatrix[i][j].setClientNumber(nodeVector[j].getClientNumber());
                    adjMatrix[i][j].setStartDate(nodeVector[j].getStartDate());
                    adjMatrix[i][j].setEndDate(nodeVector[j].getEndDate());
                    adjMatrix[i][j].setWeight(nodeVector[j].getWeight());
                    adjMatrix[i][j].setMarked();
            }
        }
    }
}


std::vector<std::vector<adjNode>> DirectedAcyclicGraph::getAdjList(){
    return adjMatrix;
}