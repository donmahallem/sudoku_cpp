#include <iostream>
#include <assert.h>
#include "sudoku_field.h"

void assertRange(short value, short min, short max)
{
    assert(value >= min && value <= max); // && (std::to_string(min) + "<" + std::to_string(value) + "<" + std::to_string(max)));
}

SudokuField::SudokuField()
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
void SudokuField::set(short x, short y, short value)
{
    assert(value >= 0 && value <= 9);
    assert(x >= 0 && x <= 8);
    assert(y >= 0 && y <= 8);
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
}
bool SudokuField::rowContains(short row, short value)
{
    assertRange(value, 1, 9);
    assertRange(row, 0, 8);
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
    assertRange(value, 1, 9);
    assertRange(column, 0, 8);
    for (short y = 0; y < 9; y++)
    {
        if (this->field[column][y] == value)
        {
            return true;
        }
    }
    return false;
}
bool SudokuField::blockContainsByBlock(short block_x, short block_y, short value)
{
    assertRange(block_x, 0, 2);
    assertRange(block_y, 0, 2);
    return this->blockContains(block_x * 3, block_y * 3, value);
}
bool SudokuField::blockContains(short x, short y, short value)
{
    assertRange(value, 1, 9);
    assertRange(x, 0, 8);
    assertRange(y, 0, 8);
    short startX = (x / 3) * 3;
    short startY = (y / 3) * 3;
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
};
bool SudokuField::isValid()
{
    short optsX = 0;
    short optsY = 0;
    short optsB = 0;
    for (short i = 0; i < 9; i++)
    {
        optsX = 0;
        optsY = 0;
        optsB = 0;
        for (short value = 0; value < 9; value++)
        {
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
        }
        if (optsX > 1 || optsY > 1 || optsB > 1)
        {
            return false;
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