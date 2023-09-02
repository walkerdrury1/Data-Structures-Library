#pragma once

#include <functional>

template <typename KEY, typename HASH = std::hash<KEY>,
          typename EQUALS = std::equal_to<KEY>>
class robin_hood_table{

private:

    std::vector<KEY> m_data;
    std::vector<short> m_psl;
    HASH m_hasher;
    EQUALS m_equals;

public:

    robin_hood_hash(const HASH &hf = HASH(), const EQUALS &eql = EQUALS())
      : m_data(5), m_valid_flag(5, 0) {
    m_hasher = hf;
    m_equals = eql;
  }

};