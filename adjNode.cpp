//
// Created by Guy Greenleaf on 3/21/21.
//

#include "adjNode.hpp"


adjNode::adjNode(int client, int startDate, int endDate, int weight){
    _clientNumber = client;
    _startDate = startDate;
    _endDate = endDate;
    _weight = weight;
    _isMarked = false;
};

adjNode::adjNode() {
    _clientNumber = 0;
    _startDate = 0;
    _endDate = 0;
    _weight = 0;
    _isMarked = false;
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
int adjNode::getWeight(){return _weight;}
bool adjNode::getMarked(){return _isMarked;}