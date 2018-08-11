#ifndef SUDOKU_FIELD_H
#define SUDOKU_FIELD_H

class SudokuField
{
  private:
    short field[9][9];

  public:
    SudokuField();
    ~SudokuField();

    void copy(SudokuField &field);
    void copy(SudokuField *field);
    void copy(const SudokuField &field);
    short get(short x, short y) const;
    void set(short x, short y, short value);
    bool rowContains(short row, short value);
    bool columnContains(short column, short value);
    bool blockContainsByBlock(short block_x, short block_y, short value);
    bool blockContains(short x, short y, short value);
    void clear();

    friend std::ostream &operator<<(std::ostream &out, const SudokuField &tipInfo);
};

#endif