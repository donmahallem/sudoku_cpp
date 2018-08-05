#include <iostream>
#include "gtest/gtest.h"

#include "../src/models/tip_info.h"

// The fixture for testing class Project1. From google test primer.
class TipInfoTest : public ::testing::Test
{
  protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    TipInfoTest()
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
    }

    // Objects declared here can be used by all tests in the test case for Project1.
    TipInfo p;
};

// Test case must be called the class above
// Also note: use TEST_F instead of TEST to access the test fixture (from google test primer)
TEST_F(TipInfoTest, testSetAndGet)
{
    int i = 1;
    p.set(i, true); // we have access to p, declared in the fixture
    EXPECT_EQ(p.get(i), true);
}

TEST_F(TipInfoTest, getNumOptions)
{
    for (short i = 1; i <= 9; i++)
    {
        p.set(i, true);
        EXPECT_EQ(p.getNumOptions(), 9 - i);
    }
}
TEST_F(TipInfoTest, equalOperator)
{
    TipInfo p1;
    TipInfo p2;
    p.set(2, true);
    p1.set(2, true);
    p2.set(2, true);
    EXPECT_EQ(p == p, true);
    EXPECT_EQ(p == p1, true);
    p2.set(5, true);
    EXPECT_EQ(p == p2, false);
}
TEST_F(TipInfoTest, unequalOperator)
{
    TipInfo p1;
    TipInfo p2;
    p.set(2, true);
    EXPECT_EQ(p != p, true);
    EXPECT_EQ(p != p1, true);
    p2.set(2, true);
    EXPECT_EQ(p != p2, false);
}