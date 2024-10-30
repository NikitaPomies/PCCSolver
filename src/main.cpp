#include <iostream>
#include "../src/variables/IntVar.h"
#include "../src/model.h"
#include "../src/utils/graphs.h"
#include "../src/problems/problems.h"
// Include your class header
using namespace std;

int main()
{
    bool n_queens = false;
    bool coloration = true;
    ;
    if (n_queens)
    {

        Model model = buildNQueens(200);

        //model.AC3();
        bool solved = model.solve();
        cout << model.are_constraints_entailed() << std::endl;
        for (int i = 0; i < model.vars.size(); i++)
        {
            cout << "Row " << i << " -> Column " << model.vars[i].getValue() << endl;
        }
        model.stats.display();
    }
    else
    {

        Model model = buildColorationModel("../data/coloration/le450_15d.col", 15);
        model.AC3();
        bool solved = model.solve();
        cout << model.are_constraints_entailed() << std::endl;

        for (IntVar &var : model.vars)
        {
            cout << var.name << " has color : " << var.getValue() << endl;
            ;
        }
        model.stats.display();
    }

    return 0;
}