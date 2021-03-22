//
// Created by Guy Greenleaf on 3/21/21.
//

#ifndef CS415PROJECT2_ADJNODE_HPP
#define CS415PROJECT2_ADJNODE_HPP


class adjNode {
public:
    adjNode(int client, int startDate, int endDate, int weight);
    adjNode();

    void setMarked();

    int getClientNumber();
    int getStartDate();
    int getEndDate();
    int getWeight();
    bool getMarked();

    void setClientNumber(int client);
    void setStartDate(int startDate);
    void setEndDate(int endDate);
    void setWeight(int weight);



private:
    int _clientNumber;
    int _startDate;
    int _endDate;
    int _weight;
    bool _isMarked;
};

#endif //CS415PROJECT2_ADJNODE_HPP
