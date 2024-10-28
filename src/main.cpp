#include <iostream>
#include "../src/variables/IntVar.h"
#include "../src/model.h"
#include "../src/utils/graphs.h"
// Include your class header
using namespace std;

int main()
{
    bool n_queens = false;
    bool coloration = true;
    if (n_queens)
    {

        Model model;
        int n = 4;
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
        model.AC3();
        bool solved = model.solve();
        cout << model.are_constraints_entailed() << std::endl;
        for (int i = 0; i < model.vars.size(); i++)
        {
            cout << "Row " << i << " -> Column " << model.vars[i].getValue() << endl;
        }
    }
    else
    {
        Graph graph("../data/coloration/myciel3.col");
        int numColors = 4;
        // graph.printGraph();
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
                { // Avoid duplicating constraints (since the graph is undirected)
                    IntVar *i = model.getVarbyName("V" + std::to_string(u));
                    IntVar *j = model.getVarbyName("V" + std::to_string(v));

                    model.add_binary_cstr(i, j);
                }
            }
        }
        //model.AC3();
        bool solved = model.solve();
        cout << model.are_constraints_entailed() << std::endl;

        for (IntVar &var : model.vars)
        {
            cout << var.name << " has color : " << var.getValue() << endl;
            ;
        }
    }

    return 0;
}