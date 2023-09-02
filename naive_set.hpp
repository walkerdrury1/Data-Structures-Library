#pragma once

#include <iostream>
#include <stack>
#include <queue>

template <typename T>
class set{

private:
    
    struct Node{
        T value;
        Node* left=nullptr;
        Node* right=nullptr;
    };

    size_t m_size=0;
    Node* root = nullptr;

    void destruct_helper(Node * curNode){
        if(curNode->left)
            destruct_helper(curNode->left);
        if(curNode->right)
            destruct_helper(curNode->right);
        delete curNode;
    }

public:

    const size_t size(){
        return m_size;
    }

    void insert(T val){
        
        if(root == nullptr){
            root = new Node();
            root->value = val;
            m_size++;
            return;
        }
        Node * curNode = root;

        while(true){
            if(val < curNode->value){
                if(curNode->left){
                    curNode = curNode->left;
                    continue;
                }
                curNode->left = new Node();
                curNode->left->value = val;
                m_size++;
                return;
            }
            if(curNode->value < val){
                if(curNode->right){
                    curNode = curNode->right;
                    continue;
                }
                curNode->right = new Node();
                curNode->right->value = val;
                m_size++;
                return;
            }
            return;
        }
   
    }

    const bool contains(T val){
        Node * curNode = root;

        while(curNode != nullptr){
            if(val < curNode->value){
                curNode = curNode->left;
                continue;
            }
            if(curNode->value < val){
                curNode = curNode->right;
                continue;
            }
            return true;
        }
        return false;
    }

    template <typename Function>
    void for_each(Function fn){

        std::stack<Node*> nodes;
        Node * curNode = root;

        while(!(nodes.empty()) || curNode){
            //std::cout << "in loop\n";
            if(curNode == nullptr){
                curNode = nodes.top();
                nodes.pop();
                //std::cout << "in function " << curNode->value << std::endl;
                fn(curNode->value);
                curNode = curNode->right;
            }
            else{
                nodes.push(curNode);
                curNode = curNode->left;
            }
        }  
    } 

    void erase(T val){
        Node * curNode = root;
        Node * parent = nullptr;

        while(curNode != nullptr){
            if(val < curNode->value){
                parent = curNode;
                curNode = curNode->left;
                continue;
            }
            if(curNode->value < val){
                parent = curNode;
                curNode = curNode->right;
                continue;
            }
            //Case 1
            if(curNode->left == nullptr && curNode->right == nullptr){
                if(parent == nullptr){
                    root = nullptr;
                    delete root;
                    return;
                }
                if(parent->left == curNode)
                    parent->left = nullptr;
                else 
                    parent->right = nullptr;
                //std::cout << "parent " << parent->value << std::endl;
                //std::cout << "curNode " << curNode->value << std::endl;
                delete curNode;
                return;

            } // Case 3 
            else if(curNode->left && curNode->right){
                Node * tempNode = curNode->left;
                while(tempNode->right){
                    tempNode = tempNode->right;
                }
                T tempVal = tempNode->value;
                erase(tempVal);
                curNode->value = tempVal;
                return;

            } else // Case 2
            {
                if(parent == nullptr){
                    if(curNode->right) 
                        root = curNode->right;
                    else
                        root = curNode->left;
                    return;
                    delete root;
                }
                if(parent-> left == curNode){
                    if(curNode->right)
                        parent->left = curNode->right;
                    else
                        parent->left = curNode->left;
                } else {
                    if(curNode->right)
                        parent->right = curNode->right;
                    else
                        parent->right = curNode->left;
                }
                delete curNode;
            }
            return;
            
        }
    } 


    ~set(){
        if (root == nullptr) {
            return;
        }
        std::queue<Node*> nodes;
        nodes.push(root);
    
        Node* curNode = nullptr;
    
        while (!nodes.empty())
        {
            curNode = nodes.front();
            nodes.pop();
    
            if (curNode->left) {
                nodes.push(curNode->left);
            }
    
            if (curNode->right) {
                nodes.push(curNode->right);
            }

            delete curNode;
        }
    
        root = nullptr;
    }


    /// Testers

    template<typename Function>
    void preorder(Function fn){
        h_preorder(fn,root);
    }

    template<typename Function>
    void h_preorder(Function fn, Node*cur){
        fn(cur->value);
        if(cur->left) 
            h_preorder(fn,cur->left);
        if(cur->right)
            h_preorder(fn,cur->right);
    }
    

};