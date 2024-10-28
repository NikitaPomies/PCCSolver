#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include <stdexcept>
#include <unordered_map>

class Graph
{
public:
    // Variables for vertices and edges
    int numVertices;
    int numEdges;
    std::unordered_map<int, std::set<int>> adjacencyList;

    // Constructor that loads and parses the graph from the .col file
    Graph(const std::string &filename)
    {
        loadFromFile(filename);
    }

    // Parse the .col file
    void loadFromFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Could not open file: " + filename);
        }

        std::string line;
        while (std::getline(file, line))
        {
            // Skip comments
            if (line.empty() || line[0] == 'c')
            {
                continue;
            }

            // Parse graph parameters
            if (line[0] == 'p')
            {
                std::istringstream iss(line);
                std::string dummy;
                iss >> dummy >> dummy >> numVertices >> numEdges;
                adjacencyList.clear();
            }
            // Parse edges
            else if (line[0] == 'e')
            {
                std::istringstream iss(line);
                char e;
                int u, v;
                iss >> e >> u >> v;
                adjacencyList[u].insert(v);
                adjacencyList[v].insert(u); // Since it's an undirected graph
            }
        }
        file.close();
    }

    // Print the graph's adjacency list (for debugging purposes)
    void printGraph() const
    {
        for (const auto &vertex : adjacencyList)
        {
            std::cout << "Vertex " << vertex.first << " is connected to: ";
            for (const int neighbor : vertex.second)
            {
                std::cout << neighbor << " ";
            }
            std::cout << "\n";
        }
    }
};