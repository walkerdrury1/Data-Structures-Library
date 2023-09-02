#pragma once

#include "LinkedList.hpp"

template <typename T>
class Queue{

private:
    LinkedList<T> list;

public:
    bool empty(){
        return list.empty();
    }

    void push(T e){
        list.push_back(e);
    }

    T pop(){
        return list.pop_front();
    }


};