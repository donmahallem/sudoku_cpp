#include <iostream>
#include <assert.h>
#include "sudoku_field.h"

SudokuField::SudokuField() : taken(0)
{
    //field = new int[9][9];
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            field[x][y] = 0;
        }
    }
}
SudokuField::~SudokuField()
{
    //delete this->field;
    //std::cout << "SudoField.Destructor" << std::endl;
}

short SudokuField::get(short x, short y) const
{
    assert(x >= 0 && x <= 8);
    assert(y >= 0 && y <= 8);
    return this->field[x][y];
};
bool SudokuField::free(short x, short y) const
{
    assert(x >= 0 && x <= 8);
    assert(y >= 0 && y <= 8);
    return this->field[x][y] == 0;
};
short SudokuField::getTaken() const
{
    return this->taken;
};
void SudokuField::set(short x, short y, short value)
{
    assert(value >= 0 && value <= 9);
    assert(x >= 0 && x <= 8);
    assert(y >= 0 && y <= 8);
    if (value == 0)
    {
        this->taken -= 1;
    }
    else if (this->field[x][y] == 0 && value != 0)
    {
        this->taken += 1;
    }
    this->field[x][y] = value;
};
void SudokuField::copy(SudokuField &field)
{
    for (short x = 0; x < 9; x++)
    {
        for (short y = 0; y < 9; y++)
        {
            this->field[x][y] = field.get(x, y);
        }
    }
    this->taken = field.getTaken();
}
void SudokuField::copy(const SudokuField &field)
{
    for (short x = 0; x < 9; x++)
    {
        for (short y = 0; y < 9; y++)
        {
            this->field[x][y] = field.get(x, y);
        }
    }
    this->taken = field.getTaken();
}
void SudokuField::copy(SudokuField *field)
{
    for (short x = 0; x < 9; x++)
    {
        for (short y = 0; y < 9; y++)
        {
            this->field[x][y] = field->get(x, y);
        }
    }
    this->taken = field->getTaken();
}
bool SudokuField::rowContains(short row, short value)
{
    assert(value >= 0 && value <= 9);
    assert(row >= 0 && row <= 8);
    for (short x = 0; x < 9; x++)
    {
        if (this->field[x][row] == value)
        {
            return true;
        }
    }
    return false;
}
bool SudokuField::columnContains(short column, short value)
{
    assert(value >= 0 && value <= 9);
    assert(column >= 0 && column <= 8);
    for (short y = 0; y < 9; y++)
    {
        if (this->field[column][y] == value)
        {
            return true;
        }
    }
    return false;
}
bool SudokuField::blockContainsByBlock(const short &block_x, const short &block_y, const short &value)
{
    assert(block_x >= 0 && block_x <= 2);
    assert(block_y >= 0 && block_y <= 2);
    return this->blockContains(block_x * 3, block_y * 3, value);
}

bool SudokuField::blockContains(const short &x, const short &y, const short &value)
{
    assert(value >= 1 && value <= 9);
    assert(x >= 0 && x < 9);
    assert(y >= 0 && y < 9);
    const short startX = (x / 3) * 3;
    const short startY = (y / 3) * 3;
    for (short offset = 0; offset < 9; offset++)
    {
        if (this->field[startX + (offset % 3)][startY + (offset / 3)] == value)
        {
            return true;
        }
    }
    return false;
}
void SudokuField::clear()
{
    for (short x = 0; x < 9; x++)
    {
        for (short y = 0; y < 9; y++)
        {
            this->field[x][y] = 0;
        }
    }
    this->taken = 0;
};
bool SudokuField::isSolved()
{
    if (this->taken != 81)
    {
        return false;
    }
    return this->isValid();
}
bool SudokuField::isValid()
{
    short optsX = 0;
    short optsY = 0;
    short optsB = 0;
    for (short i = 0; i < 9; i++)
    {
        for (short value = 1; value <= 9; value++)
        {
            optsX = 0;
            optsY = 0;
            optsB = 0;
            short startBlockX = (i % 3) * 3;
            short startBlockY = (i / 3) * 3;
            for (short j = 0; j < 9; j++)
            {
                // Check column for duplicates
                if (this->field[i][j] == value)
                {
                    optsX += 1;
                }
                // Check row for duplicates
                if (this->field[j][i] == value)
                {
                    optsY += 1;
                }
                // Check block for duplicates
                if (this->field[startBlockX + (j % 3)][startBlockY + (j / 3)] == value)
                {
                    optsB += 1;
                }
            }
            if (optsX > 1 || optsY > 1 || optsB > 1)
            {
                //std::cout << optsX << "|" << optsY << "|" << optsB << std::endl;
                return false;
            }
        }
    }
    return true;
}

std::ostream &operator<<(std::ostream &out, const SudokuField &field)
{
    out << std::endl
        << "Field" << std::endl;
    for (short y = 0; y < 9; y++)
    {
        if (y > 0 && y % 3 == 0)
        {
            for (short j = 0; j < 11; j++)
            {
                out << "-";
            }
            out << std::endl;
        }
        for (short x = 0; x < 9; x++)
        {
            if (x > 0 && x % 3 == 0)
                out << "|";
            out << field.field[x][y];
        }
        out << std::endl;
    }
    return out;
}