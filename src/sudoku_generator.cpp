#include <iostream>
#include <assert.h>
#include "sudoku_generator.h"
#include "sudoku_solver.h"
#include <algorithm>
SudokuGenerator::SudokuGenerator()
{
}
SudokuGenerator::~SudokuGenerator()
{
    //delete this->field;
    //std::cout << "destruct";
}
SudokuSolver SudokuGenerator::solver;
void SudokuGenerator::generate(const short missing, SudokuField *output)
{
    assert(missing >= 0 && missing <= 81);
    SudokuField *field = new SudokuField();
    short items[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (short i = 0; i < 3; i++)
    {
        std::random_shuffle(std::begin(items), std::end(items));
        for (short x = 0; x < 3; x++)
        {
            for (short y = 0; y < 3; y++)
            {
                field->set(i * 3 + x, i * 3 + y, items[y * 3 + x]);
            }
        }
    }
    short indixes[81];
    for (short i = 0; i < 81; i++)
    {
        indixes[i] = i;
    }
    std::random_shuffle(std::begin(indixes), std::end(indixes));
    //std::cout << "shuffle rnadoms";
    SudokuGenerator::solver.solve(*field, output);
    for (short i = 0; i < missing; i++)
    {
        //std::cout << "Shuffle out " << indixes[i] % 9 << " | " << indixes[i] / 9 << std::endl;
        output->set(indixes[i] % 9, indixes[i] / 9, 0);
    }
    delete field;
    //std::cout << "Done";
}