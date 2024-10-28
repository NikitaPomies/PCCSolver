#pragma once
#include "../model.h"

#include "../utils/graphs.h"

Model buildColorationModel(const std::string &graphFilePath, int numColors)
{
    Graph graph(graphFilePath);

    Model model;

    for (const auto &vertex : graph.adjacencyList)
    {
        int vertexID = vertex.first;
        model.add_var("V" + std::to_string(vertexID), 0, numColors - 1);
    }

    for (const auto &vertex : graph.adjacencyList)
    {
        int u = vertex.first;
        for (int v : vertex.second)
        {
            if (u < v)
            {
                IntVar *i = model.getVarbyName("V" + std::to_string(u));
                IntVar *j = model.getVarbyName("V" + std::to_string(v));

                model.add_binary_cstr(i, j);
            }
        }
    }

    return model;
}

Model buildNQueens(int n)
{
    Model model;

    // Step 1: Create variables for each row, each having domain 0 to n-1 (columns)
    for (int i = 0; i < n; i++)
    {
        // model.vars.emplace_back("Q" + std::to_string(i), 0, n - 1);
        model.add_var("Q" + std::to_string(i), 0, n - 1);
    }

    // Step 2: Add constraints: no two queens in the same column or on the same diagonal
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            // Column constraint: Q[i] != Q[j]
            model.add_binary_cstr(&model.vars[i], &model.vars[j]);

            // Diagonal constraints: Q[i] != Q[j] + (j - i)
            model.add_binary_cstr2(&model.vars[i], &model.vars[j], j - i);    // Forward diagonal
            model.add_binary_cstr2(&model.vars[i], &model.vars[j], -(j - i)); // Backward diagonal
        }
    }
    return model;
}