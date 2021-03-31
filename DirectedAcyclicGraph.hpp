//
// Created by Guy Greenleaf on 3/21/21.
//

#ifndef CS415PROJECT2_DIRECTEDACYCLICGRAPH_HPP
#define CS415PROJECT2_DIRECTEDACYCLICGRAPH_HPP


#include <vector>
#include "adjNode.hpp"
#include <list>
#include "CustomerInfo.hpp"

class DirectedAcyclicGraph{
    public:

        explicit DirectedAcyclicGraph(std::vector<CustomerInfo *> inputVec);

        unsigned long long nodeCount();

        std::vector<int> neighbors(int clientNum);

        std::vector<int> startVec;
        bool getValue(int n);
        void setValue(int n);

        unsigned long long numClients(){return adjList.size()-2;};

        std::vector<adjNode *> getAdjList();

        int getNodeType(int v);

    private:
        std::vector<adjNode *> adjList;

    };


#endif //CS415PROJECT2_DIRECTEDACYCLICGRAPH_HPP
