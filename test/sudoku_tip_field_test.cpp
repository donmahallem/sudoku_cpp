#include <iostream>
#include "gtest/gtest.h"

#include "../src/models/sudoku_tip_field.h"

// The fixture for testing class Project1. From google test primer.
class SudokuTipFieldTest : public ::testing::Test
{
  protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    SudokuTipFieldTest()
    {
        // You can do set-up work for each test here.
    }
    /*
    virtual ~TipInfo()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }*/

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    virtual void SetUp()
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown()
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
        p.reset();
    }

    // Objects declared here can be used by all tests in the test case for Project1.
    SudokuTipField p;
};

// Test case must be called the class above
// Also note: use TEST_F instead of TEST to access the test fixture (from google test primer)
TEST_F(SudokuTipFieldTest, setRowContains)
{
    for (short i = 0; i < 9; i++)
    {
        p.setRowContains(i, i + 1);
    }
    for (short i = 0; i < 9; i++)
    {
        short a = i + 1;
        EXPECT_EQ(p.rowContains(i, a), true);
    }
}

TEST_F(SudokuTipFieldTest, getTips)
{
    p.setRowContains(2, 1);
    p.setColumnContains(1, 2);
    p.setBlockContains(0, 0, 3);
    TipInfo tip = p.getTips(1, 2);
    for (short i = 1; i <= 9; i++)
    {
        EXPECT_EQ(tip.get(i), i <= 3) << "Expected " << i << " to be " << (i <= 3);
    }
}
TEST_F(SudokuTipFieldTest, parse)
{
    SudokuField field;
    for (short x = 0; x < 9; x++)
    {
        for (short y = 0; y < 9; y++)
        {
            field.set(x, y, (x > y ? x : y) + 1);
        }
    }
    p.parse(&field);
    for (short i = 0; i < 9; i++)
    {
        for (short j = 1; j <= 9; j++)
        {
            EXPECT_EQ(p.rowContains(i, j), i + 1 <= j) << "Expected row " << i << " to contain " << j;
            EXPECT_EQ(p.columnContains(i, j), i + 1 <= j) << "Expected column " << i << " to contain " << j;
            short x = i % 3;
            short y = i / 3;
            short minBlock = ((x > y ? x : y) * 3) + 1;
            short maxBlock = minBlock + 2;
            EXPECT_EQ(p.blockContains(x, y, j), j >= minBlock && j <= maxBlock) << "Expected block " << x << "," << y << " to contain " << j;
        }
    }
}

TEST_F(SudokuTipFieldTest, columnContains)
{
    SudokuField field;
    for (short x = 0; x < 9; x++)
    {
        for (short y = 0; y < 9; y++)
        {
            field.set(x, y, x + 1);
        }
    }
    p.parse(&field);
    for (short i = 0; i < 9; i++)
    {
        for (short value = 1; value <= 9; value++)
        {
            EXPECT_EQ(p.columnContains(i, value), i + 1 == value) << "Expected column " << i << " to contain " << value;
        }
    }
}

TEST_F(SudokuTipFieldTest, rowContains)
{
    SudokuField field;
    for (short x = 0; x < 9; x++)
    {
        for (short y = 0; y < 9; y++)
        {
            field.set(x, y, x + 1);
        }
    }
    p.parse(&field);
    for (short i = 0; i < 9; i++)
    {
        for (short value = 1; value <= 9; value++)
        {
            EXPECT_EQ(p.rowContains(i, value), true) << "Expected row " << i << " to contain " << value;
        }
    }
}
// }  // namespace - could surround Project1Test in a namespace