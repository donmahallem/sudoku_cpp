#include <iostream>
#include "models/sudoku_field.h"
#include "models/sudoku_tip_field.h"
#include "sudoku_solver.h"
#include "sudoku_generator.h"

inline short parseInputChar(char inp)
{
    if (inp < 48 || inp > 57)
    {
        throw 21;
    }
    return inp - 48;
}
inline SudokuField *parseInput(char *inp)
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
    std::cout << *f;
    if (!f->isValid())
    {
        std::cout << "Error not valid" << std::endl;
        return 1;
    }
    SudokuTipField tipField;
    tipField.parse(*f);
    SudokuSolver solver;
    SudokuField *r2;
    r2 = new SudokuField();
    solver.solve(*f, r2);
    std::cout << *r2;

    SudokuGenerator::generate(40, f);
    std::cout << *f;
    std::cout << *r2;
    return 0;
}