//
// Created by yaweh on 3/22/2021.
//

#include "CustomerInfo.hpp"
#include <iostream>

CustomerInfo::CustomerInfo(int custNumber, int startDate, int endDate, double weight) {
    _custNumber = custNumber;
    _startDate = startDate;
    _endDate = endDate;
    _weight = weight;
}

int CustomerInfo::startDate(){return _startDate;}
int CustomerInfo::endDate(){return _endDate;}
double CustomerInfo::weight(){return _weight;}

int CustomerInfo::custNumber() {return _custNumber;}
void CustomerInfo::print(){
    std::cout << startDate() << " " << endDate() << " " << weight() << std::endl;
}
