//
// Created by yaweh on 3/26/2021.
//

#ifndef CS415PROJECT2_LINKEDQUEUE_HPP
#define CS415PROJECT2_LINKEDQUEUE_HPP
#include "adjNode.hpp"

class LinkedQueue {
public:

    LinkedQueue();
    LinkedQueue(int size);

    bool enqueue(adjNode *it);
    adjNode *dequeue();

    adjNode *frontValue();

    int length(){return _size;}

    bool isEmpty(){return _size==0;}


private:
    adjNode *_front;
    adjNode *_rear;
    int _size;
};


#endif //CS415PROJECT2_LINKEDQUEUE_HPP
