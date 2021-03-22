//
// Created by Guy Greenleaf on 3/21/21.
//

#ifndef CS415PROJECT2_DIRECTEDACYCLICGRAPH_HPP
#define CS415PROJECT2_DIRECTEDACYCLICGRAPH_HPP


#include <vector>
#include "adjNode.hpp"


class DirectedAcyclicGraph{
    public:

        DirectedAcyclicGraph(std::vector<std::vector<int>> inputVec);

        std::vector<std::vector<adjNode>> getAdjList();

    private:
        std::vector<std::vector<adjNode>> adjMatrix;
        std::vector<std::vector<int>> edgeMatrix;
    };


#endif //CS415PROJECT2_DIRECTEDACYCLICGRAPH_HPP
