#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H
#include <iostream>
#include "models/sudoku_field.h"
#include "models/sudoku_tip_field.h"
class SudokuSolver
{
  public:
    SudokuSolver();
    ~SudokuSolver();
    void solve(const SudokuField &input, SudokuField *output);

  private:
    void solveInternal(SudokuField *field, SudokuTipField *tipField);
    bool findSingleOptions(SudokuField *sudokuField, SudokuTipField *tipField);
    bool findSingleOptionsForRows(SudokuField *sudokuField, SudokuTipField *tipField);
    bool findSingleOptionsForColumns(SudokuField *sudokuField, SudokuTipField *tipField);
    bool singleRow(SudokuField *field, SudokuTipField *tipField, short row);
    bool singleColumn(SudokuField *field, SudokuTipField *tipField, short row);
};

#endif