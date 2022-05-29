#include "pch.hpp"

int main(void)
{
    Matrix matrix; // Create matrix

    // Insert vertices
    matrix.Add('A');
    matrix.Add('B');
    matrix.Add('C');
    matrix.Add('D');
    matrix.Add('E');
    matrix.Add('F');
    matrix.Add('T');
    matrix.Add('O');

    // Connect with edges and weight
    matrix.Add('O', 'A', 2);
    matrix.Add('O', 'B', 5);
    matrix.Add('O', 'C', 4);
    matrix.Add('A', 'B', 2);
    matrix.Add('A', 'D', 7);
    matrix.Add('A', 'F', 12);
    matrix.Add('B', 'C', 1);
    matrix.Add('B', 'D', 4);
    matrix.Add('B', 'E', 3);
    matrix.Add('C', 'E', 4);
    matrix.Add('D', 'E', 1);
    matrix.Add('D', 'T', 5);
    matrix.Add('E', 'T', 7);
    matrix.Add('F', 'T', 3);
    
    matrix.PrintMatrix();
    matrix.PrintWeights();
    // Shortest path from end to start
    const auto PATH = matrix.ShortestPath('O','T');

    std::cout<< "Shortest Path between 'O' node and 'T' node:\n";
    // Display shortest path from start to end
    for(int i = PATH.size() - 1; i >= 0; i--)
        std::cout<<(char)PATH[i]<<' '; 
        
    std::cout<<std::endl; // Flush
