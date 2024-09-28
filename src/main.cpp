#include <iostream>
#include "../src/variables/IntVar.h"
#include "../src/model.h"
// Include your class header
using namespace std;

int main()
{

    cout << "test" << endl;

    IntVar var("Variable1", 1, 10);
    IntVar var2("Variable2", 6, 10);

    std::cout << "LB: " << var.getLB() << std::endl;
    std::cout << "UB: " << var.getUB() << std::endl;

    if (var.contains(5))
    {
        std::cout << "5 is within the bounds of the variable." << std::endl;
    }
    for (int i = 0; i < 9; ++i)
    {
    }

    var.removeValue(6);
    std::cout << var.toString() << endl;

    // Optionally instantiate and get the value
    try
    {
        var.getValue();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
    }

    Model m = Model();

    m.vars.push_back(var);
    m.vars.push_back(var2);
    for (int i = 0; i < m.vars.size(); ++i)
    {
        std::cout << m.vars[i].toString();
    }
    m.add_binary_cstr(&m.vars[0], &m.vars[1]);

    // m.vars[0].setUB(7);
    m.vars[0].instantiateTo(7);
    m.propagator_queue.back()->propagate();

    for (int i = 0; i < m.vars.size(); ++i)
    {
        std::cout << m.vars[i].toString();
    }

    Model model;
    int n = 23;
    // Step 1: Create variables for each row, each having domain 0 to n-1 (columns)
    for (int i = 0; i < n; i++)
    {
        model.vars.emplace_back("Q" + std::to_string(i), 0, n - 1);
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
    bool solved = model.solve();
    for (int i = 0; i < model.vars.size(); i++)
    {
        cout << "Row " << i << " -> Column " << model.vars[i].getValue() << endl;
    }



    return 0;
}