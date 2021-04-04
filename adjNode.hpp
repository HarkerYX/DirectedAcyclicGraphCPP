//
// Created by Guy Greenleaf on 3/21/21.
//

#ifndef CS415PROJECT2_ADJNODE_HPP
#define CS415PROJECT2_ADJNODE_HPP


class adjNode {
public:
    adjNode(int client, int startDate, int endDate, double weight, int nodeType);
    adjNode();

    void setMarked();

    int getClientNumber();
    int getStartDate();
    int getEndDate();
    double getWeight();
    bool getMarked();

    void setClientNumber(int client);
    void setStartDate(int startDate);
    void setEndDate(int endDate);
    void setWeight(int weight);

    void makeStart(){_isStart = true;};
    void makeEnd(){_isEnd = true;};
    void makeAdj(){_isAdj=true;};

    int getType() const{
        if(_isStart){return 1;}
        else if(_isAdj){return 2;}
        else return 3;
    }

    void setStartNode();


    adjNode *next();
    void next (adjNode *node);



private:
    int _clientNumber;
    int _startDate;
    int _endDate;
    double _weight;

    bool _isMarked;

    bool _isStart = false;

    bool _isEnd = false;

    bool _isAdj = false;

    adjNode *_next;

};

#endif //CS415PROJECT2_ADJNODE_HPP
