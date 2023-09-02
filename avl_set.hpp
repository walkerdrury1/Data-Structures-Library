#pragma once

#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>

template <typename T>
class set{

private:
    
    struct Node{
        T value;
        Node* left=nullptr;
        Node* right=nullptr;
        size_t height = 1;
    };

    size_t m_size=0;
    Node* root = nullptr;
    
    ///////////////////////////////    Small helpers
    void updateHeight(Node* node){
        if(node->left == nullptr && node->right == nullptr)
            node->height = 1;
        else if(node->left && node->right)
            node->height = 1+ std::max(node->left->height, node->right->height);
        else if(node->left == nullptr){
            node->height = 1 + node->right->height;
        } else 
            node-> height = 1 + node->left->height;
    }

    int difference(Node* node){
        int left, right;
        if(node->left)
            left = node->left->height;
        else 
            left = 0;
        if(node->right)
            right = node->right->height;
        else
            right = 0;
        return right-left;
    }

    ///////////////////////////////     Rotations
    void left_rotation(Node* parent, Node* x){
        std::cout <<"left rotation\n";
        Node* y = x->right;
        std::cout <<"hi\n";
        x->right = y->left;

        if(!parent){
            root = y;
        } else if(parent->left == x){
            parent->left = y;
        } else{
            parent->right = y;
        }
        y->left = x;
        updateHeight(x);
    }

    void right_rotation(Node* parent, Node*y){
        std::cout << "right rotation\n";
        Node*x  = y->left;
        y->left = x->right;
        if(!parent)
            root = x;
        else if(parent->right == y)
            parent->right = x;
        else 
            parent->left =x;
        x->right = y;
        updateHeight(y);
    }

    void leftRight_rotation(Node* parent, Node* z){
        left_rotation(z, z->left);
        right_rotation(parent, z);
    }

    void rightLeft_rotation(Node* parent, Node* z){
        right_rotation(z,z->right);
        left_rotation(parent,z);
    }

    void balance (){
        ;
    }
 ///////////////////////////////////////////////////////
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

        std::stack<Node*> nodes;

        while(true){
            nodes.push(curNode);
            if(val < curNode->value){
                if(curNode->left){
                    curNode = curNode->left;
                    continue;
                }
                curNode->left = new Node();
                curNode->left->value = val;
                m_size++;
                break;
            }
            if(curNode->value < val){
                if(curNode->right){
                    curNode = curNode->right;
                    continue;
                }
                curNode->right = new Node();
                curNode->right->value = val;
                m_size++;
                break;
            }
            return;
        }
        ///////////
        Node* cur;
        while(!nodes.empty()){
            cur = nodes.top();
            std::cout << "inserting " << val << " node: " << cur->value << std::endl;
            nodes.pop();
            updateHeight(cur);
            std::cout << cur->height << std::endl;
            int dif = difference(cur);

            std::cout << dif <<std::endl;
            if(dif > 1){
                Node* parent = nullptr;
                if(!nodes.empty())
                    parent = nodes.top();
                if(difference(cur->right) >= 0)
                    left_rotation(parent, cur);
                else
                    rightLeft_rotation(parent, cur);
            } else if(dif < -1){
                Node* parent = nullptr;
                if(!nodes.empty())
                    parent = nodes.top();
                if(difference(cur->left) <= 0)
                    right_rotation(parent, cur);
                else
                    leftRight_rotation(parent,cur);
            }

                
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
    ////////////////////////////////////////////////////
    void erase(T val){
        Node * curNode = root;
        Node * parent = nullptr;

        std::stack<Node*> nodes;

        while(curNode != nullptr){
            nodes.push(curNode);
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
                    m_size=0;
                    return;
                }
                if(parent->left == curNode)
                    parent->left = nullptr;
                else 
                    parent->right = nullptr;
                //std::cout << "parent " << parent->value << std::endl;
                //std::cout << "curNode " << curNode->value << std::endl;
                delete curNode;
                --m_size;
                break;
            } // Case 3 
            else if(curNode->left && curNode->right){
                Node * tempNode = curNode->left;
                while(tempNode->right){
                    tempNode = tempNode->right;
                }
                T tempVal = tempNode->value;
                erase(tempVal);
                curNode->value = tempVal;
            } else // Case 2
            {
                if(parent == nullptr){
                    if(curNode->right) 
                        root = curNode->right;
                    else
                        root = curNode->left;
                    delete curNode;
                    m_size--;
                    return;
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
                --m_size;
            }
            break;
            
        }

        Node* cur;
        while(!nodes.empty()){
            cur = nodes.top();
            std::cout << "inserting " << val << " node: " << cur->value << std::endl;
            nodes.pop();
            updateHeight(cur);
            std::cout << cur->height << std::endl;
            int dif = difference(cur);

            std::cout << dif <<std::endl;
            if(dif > 1){
                Node* parent = nullptr;
                if(!nodes.empty())
                    parent = nodes.top();
                if(difference(cur->right) >= 0)
                    left_rotation(parent, cur);
                else
                    rightLeft_rotation(parent, cur);
            } else if(dif < -1){
                Node* parent = nullptr;
                if(!nodes.empty())
                    parent = nodes.top();
                if(difference(cur->left) <= 0)
                    right_rotation(parent, cur);
                else
                    leftRight_rotation(parent,cur);
            }      
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
        if(cur->left){
            std::cout << "going left\n";
            h_preorder(fn,cur->left);
        } else std::cout << "No left\n";
        if(cur->right){
            std::cout << "going right\n";
            h_preorder(fn,cur->right);
        } else std::cout << "No right\n";
    }

    template<typename Function>
    void postorder(Function fn){
        h_postorder(fn,root);
    }

    template<typename Function>
    void h_postorder(Function fn, Node*cur){
        if(cur->left)
            h_postorder(fn,cur->left);
        if(cur->right)
            h_postorder(fn,cur->right);
        fn(cur->value);
    }
    

};