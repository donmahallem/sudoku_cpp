#ifndef SUDOKU_TIP_FIELD_H
#define SUDOKU_TIP_FIELD_H

#include "tip_info.h"
#include "sudoku_field.h"
#include "tip_info.h"

class SudokuTipField
{
  private:
    TipInfo rows[9];
    TipInfo columns[9];
    TipInfo blocks[9];
    short static const SIZE = 9;
    void checkRows(SudokuField &field, short value);
    void checkColumns(SudokuField &field, short value);
    void checkBlocks(SudokuField &field, short value);

  public:
    SudokuTipField();
    ~SudokuTipField();

    void print();
    void reset();
    void parse(SudokuField &field);
    const TipInfo &getTipsForRow(const short row) const;
    const TipInfo &getTipsForColumn(const short column) const;
    void setBlockContains(short x, short y, short value);
    void setRowContains(short row, short value);
    void setColumnContains(short column, short value);
    bool isValueBlocked(short x, short y, short value);
    TipInfo getTips(short x, short y);
};

#endif