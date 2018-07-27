#include <iostream>
#include "models/sudoku_field.h"
#include "models/sudoku_tip_field.h"
#include "sudoku_solver.h"
int main()
{
    std::cout << "Hello World" << std::endl;

    SudokuField r;
    r.width = 10;
    r.height = 15;

    std::cout << r.area() << std::endl;
    //	`endl' - new line
    r.set(0, 0, 8);
    r.set(1, 0, 2);
    r.set(2, 0, 5);
    r.set(3, 0, 6);
    r.set(4, 0, 3);
    r.set(5, 0, 1);
    r.set(6, 0, 9);
    r.set(7, 0, 7);
    r.set(8, 0, 4);
    //
    r.set(1, 1, 6);
    r.set(2, 1, 7);
    r.set(4, 1, 2);
    r.set(5, 1, 4);
    r.set(8, 1, 8);
    //
    r.set(0, 2, 4);
    r.set(5, 2, 7);
    r.set(6, 2, 6);
    r.set(8, 2, 2);
    //
    r.set(1, 3, 5);
    r.set(2, 3, 9);
    r.set(4, 3, 4);
    r.set(5, 3, 8);
    r.set(6, 3, 2);
    r.set(7, 3, 6);
    r.set(8, 3, 1);
    //
    r.set(0, 4, 1);
    r.set(2, 4, 8);
    r.set(3, 4, 2);
    r.set(4, 4, 6);
    r.set(5, 4, 9);
    r.set(6, 4, 7);
    r.set(7, 4, 4);
    r.set(8, 4, 5);
    //
    r.set(1, 5, 4);
    r.set(3, 5, 1);
    r.set(4, 5, 7);
    r.set(5, 5, 5);
    r.set(7, 5, 8);
    //
    r.set(0, 6, 3);
    r.set(2, 6, 1);
    r.set(3, 6, 4);
    //
    r.set(0, 7, 5);
    r.set(5, 7, 3);
    r.set(6, 7, 4);
    //
    r.set(0, 8, 2);
    r.set(1, 8, 9);
    r.set(2, 8, 4);
    r.set(5, 8, 6);
    r.set(6, 8, 5);
    //
    r.print();
    std::cout << r.rowContains(2, 3) << std ::endl;
    std::cout << r.blockContains(2, 2, 3) << std ::endl;
    r.rowContains(0, 9);
    SudokuTipField tipField;
    tipField.parse(r);
    std::cout << std ::endl;
    std::cout << tipField.getTips(1, 2) << std ::endl;
    std::cout << tipField.getTips(0, 1) << std ::endl;
    std::cout << tipField.getTips(2, 2) << std ::endl;
    std::cout << tipField.getTips(0, 2) << std ::endl;
    SudokuSolver solver;
    SudokuField *r2;
    r2 = new SudokuField();
    solver.solve(r, r2);
    r2->print();
    TipInfo tip1;
    TipInfo tip2;
    tip1.set(2, true);
    tip2.set(3, true);
    tip2.set(8, true);
    TipInfo tip3 = tip1 | tip2;
    std::cout << tip1 << " | " << tip1.getNumOptions() << std::endl;
    std::cout << tip2 << " | " << tip2.getNumOptions() << std::endl;
    std::cout << tip3 << " | " << tip3.getNumOptions() << std::endl;
    std::cout << (tip1 == tip1) << " | " << (tip1 == tip2) << std::endl;
    return 0;
}