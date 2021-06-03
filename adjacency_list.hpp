#pragma once

#include "pch.hpp"

/**
 * Implementation of an unweighted and undirected graph structure as an adjacency list
 **/
class Graph
{
    private:
        matrix dataEdges;      // adjacency list
        weightrix dataWeights; // weights between nodes
        /** Private Method
         * Get key index
         * @param [unsigned int] {KEY} - key in matrix
         * @return [unsigned int] - Index of key in matrix
         **/        
        size_v GetKeyIndex(uint32_t KEY)
        {
            // Get index of key in matrix
            return std::distance(dataEdges.begin(),dataEdges.find(KEY)); 
        }
        /** Private Method
         * Construct shortest path taken from all paths taken 
         * @param [std::vector<float>] {PATH} - All paths taken 
         * @param [unsigned int] {END} - End point vertex
         * @return [std::vector<unsigned int>] {shortestPath}- Shortest path taken, from end to start
         **/         
        edges CreatePath(const std::vector<float> & PATH, const uint32_t & END)
        {
            size_v e_index = GetKeyIndex(END); // Index of end vertex
            edges shortestPath;                // Will be used to hold shortest path 
            shortestPath.push_back(END);       // Update with first known vertex

            while(!std::isnan(PATH[e_index]))  // While path element is not NAN
            {
                shortestPath.push_back(PATH[e_index]); // Update path with Edge 
                e_index = GetKeyIndex(PATH[e_index]);  // Get edge used before 
            }
            return shortestPath;  // Vestor with shortest path from end to start
        }   
        /**
         * Private Method
         * - Sub-method for Print() which handles prining header and updating vector with keys
         * @param [std::vector<int>] {keys} - vector to be updated with keys
         **/
        void PrintHeader(std::vector<int> & keys)              
        {                
            for(const auto & CONTENTS : dataEdges)       // Fill vector with keys from Adjacency Matrix
                keys.push_back(CONTENTS.first);     

            std::cout<<"MATRIX TABLE\nVERTICES";
            sort(keys.begin(),keys.end());          

            for(const auto & KEY : keys)            // Print keys as a header 
                std::cout<<"\t"<<(char)KEY;  
            std::cout<<"\n";                        
        }
        /**
         * Private Method
         * - Sub-method for Print() which handles prining body of table
         * @param [std::vector<int>] {keys} - Sorted keys vector
         **/        
        void PrintBody(const std::vector<int> & KEYS)
        {
            for(const auto & KEY : KEYS)                                          // Using KEY as key for Adjacency Matrix
            {
                edges edgesList = dataEdges[KEY];                          // Edges conected to vertex
                sort(edgesList.begin(),edgesList.end());                                  

                if(edgesList.size() == 0)     // When vector is empty fill with 0 to prevent segmentation fault 
                    edgesList.push_back(0);

                std::cout<<(char)KEY<<"\t";                                             // 1 collumn with vertex     
                // As Adjacency Matrix doesn`t contain bool values but only connected verticies in graph, we need to
                // "convert" them to "1" and fill missing values with "0"
                for(size_v vertex = 0, edge = 0; vertex < KEYS.size(); vertex++)  
                {
                    if(edgesList[edge] == KEYS[vertex]) // When equal, it means that they are connected, thus we print 1
                    {
                        std::cout<<"\t1";
                        edge++;                     // Move to the next edge in vector
                    }

                    else // As we are missing not conected edges in Adjacency Matrix we fill this "gap" with "0"                
                        std::cout<<"\t0";           
                }
                std::cout<<"\n";                    
            }
        }      
        /**
         * Private Method
         * - Check if key is in matrix
         * @param [unsigned int] {KEY} - Key to check
         * @return [bool] - is key in matrix ? 
         **/
        bool InMatrix(const uint32_t & KEY)
        {
            // Key is not present
            if (dataEdges.find(KEY) == dataEdges.end())
                return false;       
            return true;
        }               
    public:
        /**
         * Constructor
         * - Handles creating of graph
         * Optional:
         * @param [int] {VERTICES} - Number of vertices to init, min = 1
         **/        
        Graph(const int VERTICES = 0)                            // Optional param 
        {         
            if(VERTICES < 1) return;                             // Graph needs to have at least 1 vertex 
            // Fill Adjacency Matrix with verticies from 1 to VERTICIES number
            for(uint32_t i = 1; i < (uint32_t)VERTICES + 1; i++)
                dataEdges[i] = edges();         
        }   
        /**
         * Overloaded Public Method
         * - Adding a vertex into the graph
         * @param [int] {VERTEX_KEY} - Vertex to add
         **/             
        void Add(const int & VERTEX_KEY)
        {
            if(VERTEX_KEY < 1) return;                            // Add only positive intigers
            // Insert vertex as a KEY, with edges in vector
            dataEdges.insert(std::make_pair((uint32_t)VERTEX_KEY,edges()));
        }
        /**
         * Overloaded Public Method
         * - Adding an edge to the graph
         * @param [unsigned int] {KEY} - Vertex to connect
         * @param [unsigned int] {EDGE} - Edge to connect 
         * @param [float] {WEIGHT} - Weight cost between edge and vertex
         **/           
        void Add(const uint32_t & KEY, const uint32_t & EDGE, const float & WEIGHT)
        {
            if( !(InMatrix(KEY) && InMatrix(EDGE)) ) // Check if key and vertex is in matrix
                return;
            dataEdges[KEY].push_back(EDGE);   // Insert requested edge in Adjacency Matrix  
            dataEdges[EDGE].push_back(KEY);   // Add conection from another edge in Adjacency Matrix 
            dataWeights[std::make_pair(KEY,EDGE)] = WEIGHT;  // Insert requested edge in Adjacency Matrix  
            dataWeights[std::make_pair(EDGE,KEY)] = WEIGHT;  // Add conection from another edge in Adjacency Matrix  
        }
        /** Public Method
         * - Using dijkstra algorithm to find shortest path from start node to end node
         * @param [unsigned int] {START} - Starting vertex
         * @param [unsigned int] {END} - Ending vertex
         * @return [std::vector<unsigned int>] - Shortest path between nodes from end to start.
         **/
        edges ShortestPath(const uint32_t & START,const uint32_t & END) 
        { 
            weight_queue Q; // priority queue using weight:(vertex:edge) relationship and sorted based on weight value
            // Fill vectors with NANs
            std::vector<float> distances(dataEdges.size(), NAN); 
            std::vector<float> path(dataEdges.size(), NAN); 

            const int S_INDEX = GetKeyIndex(START); // Get index of staarting point
            distances[S_INDEX] = 0.0f;              // Starting with cost 0       
            Q.push(std::make_pair(0.0f,START));     // Update queue with first path stop

            // While a queue is not empty
            while(!Q.empty())        
            {
                const uint32_t U_NODE = Q.top().second;     // Get minimum distance from starting vertex
                const size_v U_INDEX = GetKeyIndex(U_NODE); // Get index of vertex with minimum distance                           
                Q.pop();                                    // Remove current distance

                if(std::isnan(distances[U_INDEX])) // Shortest path is not able to found (i.e.: vertices are not connected)
                    break;                                      
                else if (U_NODE == END)            // Shortest path found
                    break;  
                    
                // Iterate through all edges connected to vertex 
                for(const auto & EDGE : dataEdges[U_NODE])
                {
                    const size_v E_INDEX = GetKeyIndex(EDGE);  // Index of current edge              
                    const float WEIGHT = dataWeights[std::make_pair(EDGE,U_NODE)];   // Weight between vertex and edge
                    // Alternative path, when distance between current edge and vertex is nan set to weight, sum weight with distance otherwise   
                    const float ALT = std::isnan(distances[U_INDEX]) ? WEIGHT : distances[U_INDEX] + WEIGHT;
                    // When vertex distance is nan set it to higher value than alternative path (NAN is 0, but in this context needs to be higher),
                    // otherwise use edge distance
                    const float V_DIST = std::isnan(distances[E_INDEX]) ? ALT + 1 : distances[E_INDEX];
                    
                    if(V_DIST > ALT) // Compare if alternative path is lower
                    {
                        distances[E_INDEX] = ALT; // Update edge distance with new path cost
                        Q.push(std::make_pair(distances[E_INDEX],EDGE)); // Push new path into queue
                        path[E_INDEX] = U_NODE; // Update path taken
                    }
                }      
            }          
            return CreatePath(path, END); // Return shortest path taken
        }
        /**
         * Public Method
         * - Printing the graph as a matrix
         **/            
        void Print()
        {
            std::vector<int> keys;
            keys.reserve(dataEdges.size());     // Reserving space to prevent unnecessary mem alloc
            PrintHeader(keys);                  // Print Header of table and update keys
            PrintBody(keys);                    // Print body of table
            std::cout<<std::endl;               // Flush
        }

};
