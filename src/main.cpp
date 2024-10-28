#include <iostream>
#include "../src/variables/IntVar.h"
#include "../src/model.h"
#include "../src/utils/graphs.h"
#include "../src/problems/problems.h"
// Include your class header
using namespace std;

int main()
{
    bool n_queens = true;
    bool coloration = false;;
    if (n_queens)
    {

        Model model = buildNQueens(500);

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

        Model model = buildColorationModel("../data/coloration/myciel3.col", 4);
        // model.AC3();
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