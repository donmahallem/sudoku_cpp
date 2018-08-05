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
TEST_F(SudokuFieldTest, setRowContains)
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

// }  // namespace - could surround Project1Test in a namespace
