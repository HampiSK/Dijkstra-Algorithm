#pragma once

#include "pch.hpp"

/**
 * Implementation of a weighted adjacency matrix structure
 **/
class Matrix
{
    public:
        /**
         * Optional:
         * @param [int] {VERTICES} - Number of vertices to init, min = 1
         **/        
        Matrix(const size_t& VERTICES = 0);

        /**
         * - Adding a vertex into the matrix
         * @param [int] {VERTEX_KEY} - Vertex to add
         **/             
        void Add(const size_t& VERTEX_KEY);
        /**
         * - Adding an edge to the matrix
         * @param [unsigned int] {KEY} - Vertex to connect
         * @param [unsigned int] {EDGE} - Edge to connect 
         * @param [float] {WEIGHT} - Weight cost between edge and vertex
         **/           
        void Add(const size_t& KEY, const size_t& EDGE, const float& WEIGHT);
        /** 
         * - Using dijkstra algorithm to find shortest path from start node to end node
         * @param [unsigned int] {START} - Starting vertex
         * @param [unsigned int] {END} - Ending vertex
         * @return [std::vector<unsigned int>] - Shortest path between nodes from end to start.
         **/
        edges ShortestPath(const size_t& START, const size_t& END);
        /**
         * - Printing the matrix table
         **/      
        void PrintMatrix();
        /**
         * - Printing the weights of a matrix
         **/      
        void PrintWeights();

    private:
        matrix _dataEdges;      // adjacency list
        weightrix _dataWeights; // weights between nodes
        /** 
         * Get key index
         * @param [unsigned int] {KEY} - key in matrix
         * @return [unsigned int] - Index of key in matrix
         **/        
        size_v GetKeyIndex(const size_t& KEY);
        /** 
         * Construct shortest path taken from all paths taken 
         * @param [std::vector<float>] {PATH} - All paths taken 
         * @param [unsigned int] {END} - End point vertex
         * @return [std::vector<unsigned int>] {shortestPath}- Shortest path taken, from end to start
         **/         
        edges CreatePath(const std::vector<float>& PATH, const size_t& END);
        /**
         * - Print table
         * @param [std::string] {tableType} - table type
         **/
        void Print(const std::string& TYPE);
        /**
         * - Sub-method for Print() which handles printing header and updating vector with keys
         * @param [std::vector<int>] {keys} - vector to be updated with keys
         * @param [std::string] {tableType} - table type
         **/
        void PrintHeader(std::vector<size_t>& keys, const std::string& TABLE_TYPE);
        /**
         * - Sub-method for Print() which handles printing body of table
         * @param [std::vector<int>] {keys} - Sorted keys vector
         * @param [bool] {displayConnections} - table type
         **/        
        void PrintBody(const std::vector<size_t>& KEYS, const bool DISPLAY_CONNECTIONS = true);
        /**
         * - Check if key is in matrix
         * @param [unsigned int] {KEY} - Key to check
         * @return [bool] - is key in matrix ? 
         **/
        bool InMatrix(const size_t& KEY);             
};
