#include <iostream>
#include <assert.h>
#include "sudoku_tip_field.h"

SudokuTipField::SudokuTipField()
{
    this->reset();
};
SudokuTipField::~SudokuTipField(){
    //delete this->field;
    //std::cout << "destruct";
};

void SudokuTipField::print()
{
    std::cout << "Field" << std::endl;
};
void SudokuTipField::parse(SudokuField &field)
{
    this->reset();
    for (short value = 1; value <= 9; value++)
    {
        //this->checkBlocks(field, value);
        //this->checkColumns(field, value);
        //std::cout << "Parse check value " << value << std::endl;
        //std::cout << "SudokuTipField->parse()->before" << std::endl;
        this->checkRows(field, value);
        //std::cout << "SudokuTipField->parse()->rows" << std::endl;
        this->checkColumns(field, value);
        //std::cout << "SudokuTipField->parse()->columns" << std::endl;
        this->checkBlocks(field, value);
        //std::cout << "SudokuTipField->parse()->blocks" << std::endl;
    }
};

const TipInfo &SudokuTipField::getTipsForColumn(const short column) const
{
    assert(column >= 0 && column < 9);
    return this->columns[column];
}
const TipInfo &SudokuTipField::getTipsForRow(const short row) const
{
    assert(row >= 0 && row < 9);
    return this->rows[row];
}

void SudokuTipField::checkRows(SudokuField &field, short value)
{
    for (short row = 0; row < 9; row++)
    {
        //std::cout << "Row " << row << " contains: ";
        if (field.rowContains(row, value))
        {
            //std::cout << "set row contains" << row << " val " << value << std::endl;
            //std::cout << value << std::endl;
            this->setRowContains(row, value);
            continue;
        }
        //std::cout << std::endl;
    }
};

void SudokuTipField::checkColumns(SudokuField &field, short value)
{
    for (short column = 0; column < 9; column++)
    {
        if (field.columnContains(column, value))
        {
            this->setColumnContains(column, value);
            continue;
        }
    }
};

void SudokuTipField::checkBlocks(SudokuField &field, short value)
{
    for (short x = 0; x < 9; x++)
    {
        if (field.blockContainsByBlock(x % 3, x / 3, value))
        {
            this->setBlockContains(x % 3, x / 3, value);
            continue;
        }
    }
};

void SudokuTipField::setBlockContains(short block_x, short block_y, short value)
{
    assert(block_x >= 0 && block_x < 3);
    assert(block_y >= 0 && block_y < 3);
    assert(value >= 1 && value <= 9);
    this->blocks[block_x + (block_y * 3)].set(value, true);
};
void SudokuTipField::setRowContains(short row, short value)
{
    assert(row >= 0 && row < 9);
    assert(value >= 1 && value <= 9);
    this->rows[row].set(value, true);
};
void SudokuTipField::setColumnContains(short column, short value)
{
    assert(column >= 0 && column < 9);
    assert(value >= 1 && value <= 9);
    this->columns[column].set(value, true);
};

bool SudokuTipField::rowContains(short row, short value)
{
    assert(row >= 0 && row < 9);
    assert(value >= 1 && value <= 9);
    return this->rows[row].get(value);
}
void SudokuTipField::reset()
{
    for (short x = 0; x < this->SIZE; x++)
    {
        this->rows[0].reset();
        this->blocks[0].reset();
        this->columns[0].reset();
    }
};

bool SudokuTipField::isValueBlocked(short x, short y, short value)
{
    return this->rows[y].get(value) | this->columns[x].get(value) | this->blocks[x / 3 + ((y / 3) * 3)].get(value);
}
TipInfo SudokuTipField::getTips(short x, short y)
{
    return this->rows[y] | this->columns[x] | this->blocks[x / 3 + ((y / 3) * 3)];
}