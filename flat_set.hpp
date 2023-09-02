#pragma once

#include <vector>

template <typename T>
class Set{

private:

    std::vector<T> data;

public:

    
    size_t size() const{
        return data.size();
    }

    void insert(T val){

        std::cout << "Inserting " << val << std::endl;

        auto pos = std::lower_bound(data.begin(), data.end(), val);
        if(pos == data.end()){
            std::cout << "hi\n";
            data.push_back(val);
            return;
        }
        std::cout << "hey\n";

        if(*pos == val)
            return;
        data.insert(pos, val);

        std::cout <<"yo\n";


    }

    void erase(T val){

        auto pos = std::lower_bound(data.begin(), data.end(), val);
        if(pos == data.end()) return;

        if(*pos == val)
            data.erase(pos);

    }

    bool contains(T val){

        auto pos = std::lower_bound(data.begin(), data.end(), val);
        if( pos == data.end) return false;
        return *pos == val;

    }

    template<typename Function>
    void for_each(Function fn){
        for(T& x: data){
            fn(x);
        }
    }

};