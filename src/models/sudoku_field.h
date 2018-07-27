#ifndef SUDOKU_FIELD_H
#define SUDOKU_FIELD_H

class SudokuField
{
  private:
    short field[9][9];

  public:
    double x;
    double y;

  public:
    SudokuField();
    ~SudokuField();
    double width;
    double height;

    double area();

    void print();

    void copy(SudokuField &field);
    void copy(SudokuField *field);
    void copy(const SudokuField &field);
    short get(short x, short y) const;
    void set(short x, short y, short value);
    bool rowContains(short row, short value);
    bool columnContains(short column, short value);
    bool blockContainsByBlock(short block_x, short block_y, short value);
    bool blockContains(short x, short y, short value);
};

#endif