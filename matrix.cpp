#include "matrix.hpp"

size_v Matrix::GetKeyIndex(const size_t& KEY)
{
    // Get index of key in matrix
    return std::distance(Matrix::_dataEdges.begin(), Matrix::_dataEdges.find(KEY)); 
} 

edges Matrix::CreatePath(const std::vector<float>& PATH, const size_t& END)
{
    size_v e_index = Matrix::GetKeyIndex(END); // Index of end vertex
    edges shortestPath; // Will be used to hold shortest path 
    shortestPath.push_back(END); // Update with first known vertex

    while(!std::isnan(PATH[e_index]))  // While path element is not NAN
    {
        shortestPath.push_back(PATH[e_index]); // Update path with Edge 
        e_index = Matrix::GetKeyIndex(PATH[e_index]); // Get edge used before 
    }
    return shortestPath.size() == 1 ? edges() : shortestPath; // Vector with shortest path from end to start
}  

void Matrix::PrintHeader(std::vector<size_t>& keys, const std::string& TABLE_TYPE)              
{                
    for(const auto & CONTENTS : Matrix::_dataEdges) // Fill vector with keys from Adjacency Matrix
        keys.push_back(CONTENTS.first);     

    std::cout<<"MATRIX "<< TABLE_TYPE <<" TABLE\nVERTICES";
    sort(keys.begin(),keys.end());          

    for(const auto & KEY : keys) // Print keys as a header 
        std::cout<<"\t"<<KEY;  
    std::cout<<"\n";                        
}  

void Matrix::PrintBody(const std::vector<size_t>& KEYS, const bool DISPLAY_CONNECTIONS) // DISPLAY_CONNECTIONS -> Optional: true
{
    for(const auto & KEY : KEYS) // Using KEY as key for Adjacency Matrix
    {
        edges edgesList = _dataEdges[KEY]; // Edges connected to vertex
        std::sort(edgesList.begin(), edgesList.end());                                  

        if(edgesList.size() == 0) // When vector is empty fill with 0 to prevent segmentation fault 
            edgesList.push_back(0);

        std::cout<<KEY<<"\t"; // 1 column with vertex     
        // As Adjacency Matrix doesn`t contain bool values but only connected verticies in matrix, we need to
        // "convert" them to "1" and fill missing values with "0"
        for(size_v vertex = 0, edge = 0; vertex < KEYS.size(); ++vertex)  
        {
            if(edgesList[edge] == KEYS[vertex]) // When equal, it means that they are connected, thus we print 1
            {
                if(DISPLAY_CONNECTIONS)
                    std::cout<<"\t1";
                else
                    std::cout<<'\t'<<Matrix::_dataWeights[std::make_pair(edgesList[edge],KEY)];
                
                edge++; // Move to the next edge in vector
            }

            else // As we are missing not connected edges in Adjacency Matrix we fill this "gap" with "-"                
                std::cout<<"\t-";           
        }
        std::cout<<"\n";                    
    }
} 

bool Matrix::InMatrix(const size_t& KEY)
{
    return Matrix::_dataEdges.find(KEY) != Matrix::_dataEdges.end(); // Key is not present
}   

Matrix::Matrix(const size_t& VERTICES) // Default param: 0
{         
    if(VERTICES < 1) return; // Matrix needs to have at least 1 vertex 
    // Fill Adjacency Matrix with verticies from 1 to VERTICIES number
    for(size_t i = 1; i < VERTICES + 1; ++i)
    {
        Matrix::_dataEdges[i] = edges();   
    }      
}  

void Matrix::Add(const size_t& VERTEX_KEY)
{
    // Insert vertex as a KEY, with edges in vector
    Matrix::_dataEdges.insert(std::make_pair(VERTEX_KEY,edges()));
}  

void Matrix::Add(const size_t& KEY, const size_t& EDGE, const float& WEIGHT)
{
    if( !(Matrix::InMatrix(KEY) && Matrix::InMatrix(EDGE)) ) // Check if key and vertex is in matrix
        return;
    Matrix::_dataEdges[KEY].push_back(EDGE); // Insert requested edge in Adjacency Matrix  
    Matrix::_dataEdges[EDGE].push_back(KEY); // Add connection from another edge in Adjacency Matrix 
    Matrix::_dataWeights[std::make_pair(KEY,EDGE)] = WEIGHT; // Insert requested edge in Adjacency Matrix  
    Matrix::_dataWeights[std::make_pair(EDGE,KEY)] = WEIGHT; // Add connection from another edge in Adjacency Matrix  
}

edges Matrix::ShortestPath(const size_t& START, const size_t& END) 
{ 
    weight_queue Q; // priority queue using weight:(vertex:edge) relationship and sorted based on weight value
    // Fill vectors with NANs
    std::vector<float> distances(Matrix::_dataEdges.size(), NAN); 
    std::vector<float> path(Matrix::_dataEdges.size(), NAN); 

    const int S_INDEX = Matrix::GetKeyIndex(START); // Get index of staarting point
    distances[S_INDEX] = 0.0f; // Starting with cost 0       
    Q.push(std::make_pair(0.0f,START)); // Update queue with first path stop

    // While a queue is not empty
    while(!Q.empty())        
    {
        const size_t U_NODE = Q.top().second; // Get minimum distance from starting vertex
        const size_v U_INDEX = Matrix::GetKeyIndex(U_NODE); // Get index of vertex with minimum distance                           
        Q.pop(); // Remove current distance

        if(std::isnan(distances[U_INDEX])) // Shortest path is not able to found (i.e.: vertices are not connected)
            break;                                      
        else if (U_NODE == END) // Shortest path found
            break;  
            
        // Iterate through all edges connected to vertex 
        for(const auto & EDGE : _dataEdges[U_NODE])
        {
            const size_v E_INDEX = Matrix::GetKeyIndex(EDGE); // Index of current edge              
            const float WEIGHT = _dataWeights[std::make_pair(EDGE,U_NODE)]; // Weight between vertex and edge
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
    return Matrix::CreatePath(path, END); // Return shortest path taken
}

void Matrix::Print(const std::string& type)
{
    bool flag = type == "CONNECTIONS";
    std::vector<size_t> keys;
    keys.reserve(Matrix::_dataEdges.size()); // Reserving space to prevent unnecessary mem alloc
    Matrix::PrintHeader(keys, type); // Print Header of table and update keys
    Matrix::PrintBody(keys,flag); // Print body of table
    std::cout<<std::endl; // Flush
}

void Matrix::PrintMatrix()
{
    Matrix::Print("CONNECTIONS");
}

void Matrix::PrintWeights()
{
    Matrix::Print("WEIGHTS");
}
