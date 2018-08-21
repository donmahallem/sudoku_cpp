#ifndef SUDOKU_FIELD_H
#define SUDOKU_FIELD_H

class SudokuField
{
  private:
    short field[9][9];
    short taken;

  public:
    SudokuField();
    ~SudokuField();

    void copy(SudokuField &field);
    void copy(SudokuField *field);
    void copy(const SudokuField &field);
    bool free(short x, short y) const;
    short get(short x, short y) const;
    short getTaken() const;
    void set(short x, short y, short value);
    bool rowContains(short row, short value);
    bool columnContains(short column, short value);
    bool blockContainsByBlock(const short &block_x, const short &block_y, const short &value);
    bool blockContains(const short &x, const short &y, const short &value);
    void clear();
    bool isValid();
    bool isSolved();

    friend std::ostream &operator<<(std::ostream &out, const SudokuField &tipInfo);
};

#endif