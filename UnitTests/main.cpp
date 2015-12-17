#include <windows.h>
#include "gtest/gtest.h"

int main (int argc, char** argv)
{
    // this prevents annoying error message boxes popping up
    // when assert is called in your program code
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
