//
// Created by Guy Greenleaf on 3/21/21.
//

#include "adjNode.hpp"


adjNode::adjNode(int client, int startDate, int endDate, double weight){
    _clientNumber = client;
    _startDate = startDate;
    _endDate = endDate;
    _weight = weight;
    _isMarked = false;
    _next = nullptr;
};



void adjNode::setStartNode(){
    _clientNumber = 0;
    _startDate = 0;
    _endDate = 0;
    _weight = 0;
    _isMarked = false;
};

void adjNode::setEndNode(){

};

void adjNode::next (adjNode *node){_next = node;};
adjNode *adjNode::next(){
    return _next;
}

adjNode::adjNode() {
    _clientNumber = 0;
    _startDate = 0;
    _endDate = 0;
    _weight = 0;
    _isMarked = false;
    _next = nullptr;
}

void adjNode::setMarked() {
    bool currmarked = _isMarked;
    _isMarked = !currmarked;
}


void adjNode::setClientNumber(int client){_clientNumber=client;}
void adjNode::setStartDate(int startDate){_startDate=startDate;}
void adjNode::setEndDate(int endDate){_endDate=endDate;}
void adjNode::setWeight(int weight){_weight = weight;}

int adjNode::getClientNumber(){return _clientNumber;}
int adjNode::getStartDate(){return _startDate;}
int adjNode::getEndDate(){return _endDate;}
double adjNode::getWeight(){return _weight;}
bool adjNode::getMarked(){return _isMarked;}