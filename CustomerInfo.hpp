//
// Created by yaweh on 3/22/2021.
//

#ifndef CS415PROJECT2_CUSTOMERINFO_HPP
#define CS415PROJECT2_CUSTOMERINFO_HPP

class CustomerInfo{
public:
    CustomerInfo(int custNumber, int startDate, int endDate, double weight);
    int startDate();
    int endDate();
    double weight();
    void print();
    int custNumber();

private:
    int _startDate;
    int _endDate;
    double _weight;
    int _custNumber;

};
#endif //CS415PROJECT2_CUSTOMERINFO_HPP
