#include <iostream>
#include "models/sudoku_field.h"
#include "models/sudoku_tip_field.h"
#include "sudoku_solver.h"

short parseInputChar(char inp)
{
    if (inp < 48 || inp > 57)
    {
        throw 21;
    }
    return inp - 48;
}
SudokuField *parseInput(char *inp)
{
    SudokuField *field = new SudokuField();
    for (short i = 0; i < 9 * 9; i++)
    {
        short x = i % 9;
        short y = i / 9;
        field->set(x, y, parseInputChar(inp[i]));
    }
    return field;
}
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Not the correct number of args " << argc << std::endl;
        return 1;
    }
    std::cout << argv[1] << std::endl;
    SudokuField *f = parseInput(argv[1]);
    f->print();
    std::cout << "Hello World" << std::endl;

    SudokuTipField tipField;
    tipField.parse(*f);
    std::cout << std ::endl;
    std::cout << tipField.getTips(1, 2) << std ::endl;
    std::cout << tipField.getTips(0, 1) << std ::endl;
    std::cout << tipField.getTips(2, 2) << std ::endl;
    std::cout << tipField.getTips(0, 2) << std ::endl;
    SudokuSolver solver;
    SudokuField *r2;
    r2 = new SudokuField();
    solver.solve(*f, r2);
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