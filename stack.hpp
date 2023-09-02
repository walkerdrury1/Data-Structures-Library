#pragma once

#include "LinkedList.hpp"

template <typename T>
class Stack{

private:
    LinkedList<T> list;

public:
    bool empty(){
        return list.empty();
    }

    void push(T e){
        list.push_front(e);
    }

    T pop(){
        return list.pop_front();
    }

};