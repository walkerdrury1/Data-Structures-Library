#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

template <typename KEY, typename HASH = std::hash<KEY>,
          typename EQUALS = std::equal_to<KEY>>
class set {

private:

    HASH m_hasher;
    EQUALS m_equals;
    
    size_t m_size = 0;
    double threshold = .9;

    void priv_insert(const KEY& k){
        size_t hash = m_hasher(k);
        m_data[hash % m_data.size()].push_back(k);
        ++m_size;
    }

public:
    std::vector<std::list<KEY>> m_data;
    
    set(const HASH &hf = HASH(), const EQUALS &eql = EQUALS())
      : m_data(5){
    m_hasher = hf;
    m_equals = eql;
    }

    size_t size() const{ return m_size; }

    void set_threshold(double val) { threshold = val; }

    void insert(const KEY &k){

        if (m_size > double(m_data.capacity()) * threshold) {
            //resize
            std::vector<std::list<KEY>> old_data(m_data.capacity() * 2);
            old_data.swap(m_data);
            
            m_size = 0;

            for (size_t i = 0; i < old_data.size(); ++i) {
                for(const KEY& key: old_data[i]){
                    priv_insert(key);
                }
            }
        }
        priv_insert(k);
    }

    bool contains(const KEY& k) const{
        size_t hash = m_hasher(k);
        for(const KEY& e : m_data[hash % m_data.capacity()]){
            if(m_equals(k,e))
                return true;
            
        }
        return false;
    }

    void erase(const KEY& k){
        size_t hash = m_hasher(k);
        std::list<KEY>* list = &(m_data[hash % m_data.capacity()]);
        
        auto itr = std::find((*list).begin(), (*list).end(), k);
        if(itr == (*list).end()) return;
        (*list).erase(itr);
        --m_size;

    }

    template<typename Function>
    void for_each(Function fn){
        for(int i=0; i<m_data.capacity(); i++){
            for(auto itr = m_data[i].begin(); itr!= m_data[i].end(); ++itr){
                fn(*itr);
            }
        }
    }



};
