#pragma once

/* This is PRE COMPILED HEADER with all files included.
 * To create precompiled file use command: g++ -std=c++11
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>      // std::pair, std::make_pair
#include <queue>        // std::priority_queue
#include <cmath>        //std::isnan(), NAN

// Custom hash which enables to store pair as a key. Note that key is in vertex:edge relation
// Important note:
// XOR as a hash combination used for simplicity. Possible collision values can be inserted:
// (x ^ x == y ^ y == 0, x ^ y == y ^ x)
// Reference: https://www.techiedelight.com/use-std-pair-key-std-unordered_map-cpp/
struct pairhash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> & CONNECTION) const
    {
        return std::hash<T1>()(CONNECTION.first) ^ std::hash<T2>()(CONNECTION.second);
    }
};

typedef std::unordered_map<size_t,std::vector<size_t>> matrix; // Adjacency Matrix
typedef std::vector<size_t> edges; // Vector of edges
typedef std::vector<size_t>::size_type size_v; // Using for vector iteration
typedef std::pair<size_t,size_t> connection; // Connection between vertex and edge
typedef std::unordered_map<connection,float,pairhash> weightrix; // Map with weights
typedef std::pair<float,size_t> weightpair;

// Using custom hash with paired and sorted elements using weight:vertex relation
// Sorting depends on weight values and it is sorted from smallest
typedef std::priority_queue<weightpair,std::vector<weightpair>,std::greater<weightpair>> weight_queue;

// Contains adjecency list with dijkstra implementation
#include "matrix.hpp"
