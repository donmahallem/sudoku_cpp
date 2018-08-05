#include <iostream>
#include "gtest/gtest.h"

// }  // namespace - could surround Project1Test in a namespace

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}