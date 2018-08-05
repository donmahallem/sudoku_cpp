#include <iostream>
#include "gtest/gtest.h"

#include "../src/models/sudoku_field.h"

// The fixture for testing class Project1. From google test primer.
class SudokuFieldTest : public ::testing::Test
{
  protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    SudokuFieldTest()
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
        p.clear();
    }

    // Objects declared here can be used by all tests in the test case for Project1.
    SudokuField p;
};

// Test case must be called the class above
// Also note: use TEST_F instead of TEST to access the test fixture (from google test primer)
TEST_F(SudokuFieldTest, set)
{
    for (short x = 0; x < 9; x++)
    {
        for (short y = 0; y < 9; y++)
        {
            p.set(x, y, ((x + y) % 9) + 1);
        }
    }
    for (short x = 0; x < 9; x++)
    {
        for (short y = 0; y < 9; y++)
        {
            EXPECT_EQ(p.get(x, y), ((x + y) % 9) + 1);
        }
    }
}
TEST_F(SudokuFieldTest, rowContains)
{
    for (short x = 0; x < 9; x++)
    {
        p.set(x, x, x + 1);
    }
    for (short x = 0; x < 9; x++)
    {
        for (short y = 1; y <= 9; y++)
        {
            EXPECT_EQ(p.rowContains(x, y), y == x + 1);
        }
    }
}
TEST_F(SudokuFieldTest, columnContains)
{
    for (short x = 0; x < 9; x++)
    {
        p.set(x, x, x + 1);
    }
    for (short x = 0; x < 9; x++)
    {
        for (short y = 1; y <= 9; y++)
        {
            EXPECT_EQ(p.columnContains(x, y), y == x + 1);
        }
    }
}
TEST_F(SudokuFieldTest, blockContainsByBlock)
{
    for (short x = 0; x < 9; x++)
    {
        p.set(x, x, x + 1);
    }
    for (short block = 0; block < 9; block++)
    {
        short x = block % 3;
        short y = block / 3;
        if (block % 4 == 0)
        {
            short startValue = (x * 3) + 1;
            short endValue = startValue + 2;
            for (short value = 1; value <= 9; value++)
            {

                EXPECT_EQ(p.blockContainsByBlock(x, y, value), value >= startValue && value <= endValue);
            }
        }
        else
        {
            for (short value = 1; value <= 9; value++)
            {
                EXPECT_EQ(p.blockContainsByBlock(x, y, value), false);
            }
        }
    }
}

// }  // namespace - could surround Project1Test in a namespace
