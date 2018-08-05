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
        EXPECT_EQ(p.rowContains(i, i + 1), true);
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
// }  // namespace - could surround Project1Test in a namespace
