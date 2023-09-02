#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <typename KEY, typename HASH = std::hash<KEY>,
          typename EQUALS = std::equal_to<KEY>>
class set {
public:
  set(const HASH &hf = HASH(), const EQUALS &eql = EQUALS())
      : m_data(5), m_valid_flag(5, 0) {
    m_hasher = hf;
    m_equals = eql;
  }

  void insert(const KEY &k) {
    if (m_size > double(m_data.capacity()) * m_threshold) {

      std::vector<KEY> old_data(m_data.capacity() * 2);
      old_data.swap(m_data);
      std::vector<bool> old_flags(m_valid_flag.capacity() * 2);
      old_flags.swap(m_valid_flag);
      m_max_probe = 0;
      m_size = 0;

      for (size_t i = 0; i < old_data.size(); ++i) {
        if (old_flags[i]) {
          priv_insert(old_data[i]);
        }
      }
    }
    priv_insert(k);
  }

  bool erase(const KEY &k) {
    size_t hash = m_hasher(k);
    size_t probe = hash % m_data.size();

    for (size_t i = 0; i < m_max_probe; ++i) {
      size_t loc = (probe + i) % m_data.size();
      if (m_valid_flag[loc]) {
        if (m_equals(m_data[loc], k)) {
          // valid & equals case
          m_valid_flag[loc] = false;
          --m_size;
          return true;
        } else {
          // valid & NOT equal case
          // continue to next location
        }
      } else {
        // do nothing, must continue until max probe distance
      }
    }
    return false;
  }

  bool contains(const KEY& k) const{
      size_t hash = m_hasher(k);
      size_t probe = hash % m_data.capacity();
      for (size_t i = 0; i < m_max_probe; ++i) {
        size_t loc = (probe + i) % m_data.size();
        if (m_valid_flag[loc]) {
          if (m_equals(m_data[loc], k)) {
            return true;
          } else {

          }
        } else {
        
        }
    }
    return false;
  }

  size_t size() const { return m_size; }
  size_t capacity() const { return m_data.capacity(); }
  void set_threshold(double t) {m_threshold = t; }

  template <typename Function> void for_each(Function fn) {
    for (size_t i = 0; i < m_data.size(); ++i) {
      if (m_valid_flag[i]) {
        fn(m_data[i]);
      }
    }
  }

private:

  HASH m_hasher;
  EQUALS m_equals;
  std::vector<KEY> m_data;
  std::vector<bool> m_valid_flag;
  size_t m_max_probe = 0;
  size_t m_size = 0;
  double m_threshold = .9;

  void priv_insert(const KEY &k) {
    size_t hash = m_hasher(k);
    size_t probe = hash % m_data.size();
    for (size_t i = 0; i < m_data.size(); ++i) {
      size_t loc = (probe + i) % m_data.size();

      if (m_valid_flag[loc]) {
        if (m_equals(m_data[loc], k)) {
          return; // element already exists
        } else {
          // do nothing, increment to next location
        }
      } else {
        m_data[loc] = k;
        m_valid_flag[loc] = true;
        m_max_probe = std::max(m_max_probe, i + 1);
        ++m_size;

        // if(max_prove > big number) rehash
        return;
      }
    }
  }

};

