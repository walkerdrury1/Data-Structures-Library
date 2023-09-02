#ifndef LINKED 
#define LINKED

#include <cassert>

template <typename T>
struct Node{
    T val;
    Node<T>* next = nullptr;
    Node<T>* prev = nullptr;
};

template <typename T>
class LinkedList{

private:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;

public:
    bool empty(){
        return head == nullptr;
    }

    void push_back(T val){
        if(head == nullptr){
            head = new Node<T>();
            head->val = val;
            tail = head;
            return;
        }

        Node<T>* tmp = tail;
        tail = new Node<T>();
        tail->val = val;
        tail->prev = tmp;
        tmp->next = tail;

    }

    void push_front(T val){
        if(head == nullptr){
            head = new Node<T>();
            head->val = val;
            tail = head;
            return;
        }

        Node<T> * tmp = head;
        head = new Node<T>();
        head->val = val;
        head->next = tmp;
        tmp->prev = head;

    }

    T pop_front(){
        assert(head != nullptr);

        T to_return;
        if(head == tail){
            to_return = head->val;
            delete head;
            head = nullptr;
            tail = nullptr;
            return to_return;
        }

        Node<T>* tmp = head;
        head = head->next;
        head->prev = nullptr;

        to_return = tmp->val;
        delete tmp;
        return to_return;

    }

    T pop_back(){
        assert(head != nullptr);

        T to_return;
        if(head == tail){
            to_return = head->val;
            delete head;
            head = nullptr;
            tail = nullptr;
            return to_return;
        }

        Node<T>* tmp = tail;
        tail = tail->prev;
        tail->next = nullptr;

        to_return = tmp->val;
        delete tmp;
        return to_return;
    }

    ~LinkedList(){

        if(head == nullptr) return;

        Node<T>* tmp = head;
        while(tmp != tail){
            delete head;
            tmp = head;
        }
        delete head;

    }

};

#endif