#include "pch.hpp"

int main()
{
    Graph GraphD; // Create Graph with empty matrix

    // Insert vertices
    // Note: Vertices are shown as chars, but in graphD are converted into unsigned int
    GraphD.Add('A');
    GraphD.Add('B');
    GraphD.Add('C');
    GraphD.Add('D');
    GraphD.Add('E');
    GraphD.Add('F');
    GraphD.Add('T');
    GraphD.Add('O');

    // Connect with edges and weight
    GraphD.Add('O', 'A', 2);
    GraphD.Add('O', 'B', 5);
    GraphD.Add('O', 'C', 4);
    GraphD.Add('A', 'B', 2);
    GraphD.Add('A', 'D', 7);
    GraphD.Add('A', 'F', 12);
    GraphD.Add('B', 'C', 1);
    GraphD.Add('B', 'D', 4);
    GraphD.Add('B', 'E', 3);
    GraphD.Add('C', 'E', 4);
    GraphD.Add('D', 'E', 1);
    GraphD.Add('D', 'T', 5);
    GraphD.Add('E', 'T', 7);
    GraphD.Add('F', 'T', 3);
    
    GraphD.Print();
    // Shortest path from end to start
    const auto PATH = GraphD.ShortestPath('O','T');

    std::cout<< "Shortest Path between 'O' node and 'T' node:\n";
    // Display shortest path from start to end
    for(int i = PATH.size() - 1; i >= 0; i--)
        std::cout<<(char)PATH[i]<<" "; // unsigned int are displayed as chars
    std::cout<<std::endl; // Flush
}
