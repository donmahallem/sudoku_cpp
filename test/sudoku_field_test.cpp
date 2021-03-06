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
TEST_F(SudokuFieldTest, copyPointer)
{
    for (short x = 0; x < 9; x++)
    {
        for (short y = 0; y < 9; y++)
        {
            p.set(x, y, (x + y) % 10);
        }
    }
    SudokuField p2;
    p2.copy(&p);
    //EXPECT_EQ(p == p2, true);
    for (short x = 0; x < 9; x++)
    {
        for (short y = 0; y < 9; y++)
        {
            EXPECT_EQ(p.get(x, y), p2.get(x, y));
        }
    }
}

TEST_F(SudokuFieldTest, copyDirect)
{
    for (short x = 0; x < 9; x++)
    {
        for (short y = 0; y < 9; y++)
        {
            p.set(x, y, (x + y) % 10);
        }
    }
    SudokuField p2;
    p2.copy(p);
    //EXPECT_EQ(p == p2, true);
    for (short x = 0; x < 9; x++)
    {
        for (short y = 0; y < 9; y++)
        {
            EXPECT_EQ(p.get(x, y), p2.get(x, y));
        }
    }
}
TEST_F(SudokuFieldTest, outOperator)
{
    for (short x = 0; x < 9; x++)
    {
        for (short y = 0; y < 9; y++)
        {
            p.set(x, y, (x + y) % 10);
        }
    }
    std::stringstream out;
    out << p;
    std::string s = out.str();
    EXPECT_STREQ(s.c_str(), "\nField\n012|345|678\n123|456|789\n234|567|890\n-----------\n345|678|901\n456|789|012\n567|890|123\n-----------\n678|901|234\n789|012|345\n890|123|456\n");
}
TEST_F(SudokuFieldTest, isValid)
{
    for (short x = 0; x < 8; x++)
    {
        p.clear();
        p.set(x, 0, x + 1);
        p.set(x + 1, 0, x + 1);
        EXPECT_EQ(p.isValid(), false) << x << "row should have duplicate";
        p.clear();
        p.set(0, x, x + 1);
        p.set(0, x + 1, x + 1);
        EXPECT_EQ(p.isValid(), false) << x << "column should have duplicate";
    }
    p.clear();
    EXPECT_EQ(p.isValid(), true) << "Empty field should be valid";
}

// }  // namespace - could surround Project1Test in a namespace
