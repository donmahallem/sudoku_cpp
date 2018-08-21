#ifndef SUDOKU_GENERATOR_H
#define SUDOKU_GENERATOR_H
#include <iostream>
#include "models/sudoku_field.h"
#include "sudoku_solver.h"
class SudokuGenerator
{
  public:
    static void generate(const short missing, SudokuField *output);

  private:
    SudokuGenerator();
    ~SudokuGenerator();
    static SudokuSolver solver;
};
#endif