
#ifdef WINDOWS
#include <windows.h>
#endif

#include "gtest/gtest.h"

int main (int argc, char** argv)
{
#ifdef WINDOWS
    // this prevents annoying error message boxes popping up
    // when assert is called in your program code
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
#endif

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
