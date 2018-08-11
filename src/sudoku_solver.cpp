#include <iostream>
#include <assert.h>
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
    std::cout << *field;
    for (short i = 0; i < 4; i++)
    {
        bool found = false;

        switch (i)
        {
        case 0:
            std::cout << "Check single opts" << std::endl;
            found |= this->findSingleOptions(field, tipField);
            break;
        case 1:
            std::cout << "Check rows" << std::endl;
            found |= this->findSingleOptionsForRows(field, tipField);
            break;
        case 2:
            std::cout << "Check columns" << std::endl;
            found |= this->findSingleOptionsForColumns(field, tipField);
            break;
        case 3:
            std::cout << "Check blocks" << std::endl;
            found |= this->findSingleOptionsForBlocks(field, tipField);
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
    bool ret = false;
    for (short i = 0; i < 9; i++)
    {
        ret |= this->findSingleOptionsForColumn(sudokuField, tipField, i);
    }
    return ret;
}
bool SudokuSolver::findSingleOptionsForRows(SudokuField *sudokuField, SudokuTipField *tipField)
{
    bool ret = false;
    for (short i = 0; i < 9; i++)
    {
        ret |= this->findSingleOptionsForRow(sudokuField, tipField, i);
    }
    return ret;
}
bool SudokuSolver::findSingleOptionsForBlocks(SudokuField *sudokuField, SudokuTipField *tipField)
{
    bool ret = false;
    for (short i = 0; i < 9; i++)
    {
        //std::cout << "Row " << i << std::endl;
        ret |= this->findSingleOptionsForBlock(sudokuField, tipField, i);
    }
    return ret;
}
bool SudokuSolver::findSingleOptionsForColumn(SudokuField *sudokuField, SudokuTipField *tipField, short column)
{
    short opts = 0;
    short lastOp = 0;
    for (short value = 1; value <= 9; value++)
    {
        opts = 0;
        lastOp = 0;
        //std::cout << "Check value " << value << std::endl;
        if (tipField->columnContains(column, value))
        {
            //std::cout << "Column " << column << " contains " << value << std::endl;
            continue;
        }
        for (short row = 0; row < 9; row++)
        {
            if (!tipField->rowContains(row, value))
            {
                opts += 1;
                lastOp = row;
            }
        }
        if (opts == 1)
        {
            sudokuField->set(column, lastOp, value);
            return true;
        }
    }
    return false;
}
bool SudokuSolver::findSingleOptionsForRow(SudokuField *sudokuField, SudokuTipField *tipField, short row)
{
    std::cout << "Checking row: " << row << std::endl;
    short opts = 0;
    short lastOp = 0;
    for (short value = 1; value <= 9; value++)
    {
        std::cout << "Check value: " << value << std::endl;
        opts = 0;
        lastOp = 0;
        //std::cout << "Check value " << value << std::endl;
        if (tipField->rowContains(row, value))
        {
            //std::cout << "== Row contains " << value << std::endl;
            //std::cout << "Column " << column << " contains " << value << std::endl;
            continue;
        }
        std::cout << "== Row does not contain " << value << std::endl;
        for (short column = 0; column < 9; column++)
        {
            if (!tipField->columnContains(column, value))
            {
                opts += 1;
                lastOp = column;
                std::cout << "== Column " << column << " does not contain " << value << std::endl;
            }
            else
            {

                //std::cout << "== Column " << column << " contains " << value << std::endl;
            }
        }
        if (opts == 1)
        {
            std::cout << "set " << lastOp << "|" << row << " value: " << value << std::endl;
            sudokuField->set(lastOp, row, value);
            return true;
        }
        else
        {
            std::cout << "== Options found " << opts << std::endl;
        }
    }
    return false;
}
bool SudokuSolver::findSingleOptionsForBlock(SudokuField *sudokuField, SudokuTipField *tipField, short block)
{
    const short minX = (block % 3) * 3;
    const short minY = (block / 3) * 3;
    const short maxX = minX + 3;
    const short maxY = minY + 3;
    short opts = 0;
    short lastX = 0;
    short lastY = 0;
    for (short value = 1; value <= 9; value++)
    {
        opts = 0;
        lastX = 0;
        lastY = 0;
        if (tipField->blockContains(block % 3, block / 3, value))
        {
            continue;
        }
        for (short x = minX; x < maxX; x++)
        {
            for (short y = minY; y < maxY; y++)
            {
                if (tipField->rowContains(y, value) || tipField->columnContains(x, value))
                {
                    continue;
                }
                opts += 1;
                lastX = x;
                lastY = y;
            }
        }
        if (opts == 1)
        {
            sudokuField->set(lastX, lastY, value);
            return true;
        }
    }
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
                for (short value = 1; value <= 9; value++)
                {
                    if (info.get(value) == false)
                    {
                        //std::cout << "Value set" << x << "," << y << " " << z << std::endl;
                        std::cout << "set " << x << "|" << y << " value: " << value << std::endl;
                        sudokuField->set(x, y, value);
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