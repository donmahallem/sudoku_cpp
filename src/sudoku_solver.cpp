#include <iostream>
#include <assert.h>
#include "models/tip_info.h"
#include "models/sudoku_field.h"
#include "models/sudoku_tip_field.h"
#include "sudoku_solver.h"

SudokuSolver::SudokuSolver()
{
}
SudokuSolver::~SudokuSolver()
{
    //delete this->field;
    //std::cout << "destruct";
}

void SudokuSolver::solve(const SudokuField &input, SudokuField *output)
{
    assert(output != NULL);
    output->copy(input);
    SudokuTipField *tipField;
    tipField = new SudokuTipField();
    tipField->parse(*output);
    this->solveInternal(output, tipField);
}
void SudokuSolver::solveInternal(SudokuField *field, SudokuTipField *tipField)
{
    for (short i = 0; i < 3; i++)
    {
        bool found = false;
        switch (i)
        {
        case 0:
            found |= this->findSingleOptions(field, tipField);
            break;
        case 1:
            found |= this->findSingleOptionsForRows(field, tipField);
            break;
        case 2:
            found |= this->findSingleOptionsForColumns(field, tipField);
            break;
        }
        if (found)
        {
            tipField->parse(*field);
            this->solveInternal(field, tipField);
            break;
        }
    }
}

bool SudokuSolver::findSingleOptionsForColumns(SudokuField *sudokuField, SudokuTipField *tipField)
{
    return false;
}
bool SudokuSolver::findSingleOptionsForRows(SudokuField *sudokuField, SudokuTipField *tipField)
{
    return false;
}
bool SudokuSolver::findSingleOptions(SudokuField *sudokuField, SudokuTipField *tipField)
{
    int foundOptions = 0;
    for (short x = 0; x < 9; x++)
    {
        for (short y = 0; y < 9; y++)
        {
            //std::cout << x << "," << y << " - " << sudokuField.get(x, y) << std ::endl;

            if (sudokuField->get(x, y) != 0)
            {
                continue;
            }
            const TipInfo info = tipField->getTips(x, y);
            //std::cout << "Options " << x << "," << y << " " << info.getNumOptions() << std::endl;
            if (info.getNumOptions() == 1)
            {
                for (short z = 1; z <= 9; z++)
                {
                    if (info.get(z) == false)
                    {
                        std::cout << "Value set" << x << "," << y << " " << z << std::endl;
                        sudokuField->set(x, y, z);
                        foundOptions++;
                        break;
                    }
                }
            }
        }
    }
    bool result = (foundOptions > 0);
    return result;
}
bool SudokuSolver::singleRow(SudokuField *sudokuField, SudokuTipField *tipField, short row)
{
    return false;
}
bool SudokuSolver::singleColumn(SudokuField *sudokuField, SudokuTipField *tipField, short column)
{
    return false;
}