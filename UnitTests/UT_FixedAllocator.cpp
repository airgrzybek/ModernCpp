/*
 * UT_FixedAllocator.cpp
 *
 *  Created on: 18 gru 2015
 *      Author: xxpowdaw
 */

#include <limits.h>
#include "gtest/gtest.h"
#include <vector>
#include "FixedAllocator.h"

const static std::size_t PAGE_SIZE = 4096;

class FixedAllocatorTest : public testing::TestWithParam<std::size_t>
{
public:
    FixedAllocatorTest() :
        blockSize(0),
        fixedAllocator(GetParam(),PAGE_SIZE)
    {

    }
    ~FixedAllocatorTest()
    {

    }

    void SetUp()
    {
        blockSize = GetParam();
    }

    void TearDown()
    {
    }
    std::size_t blockSize;
    Memory::FixedAllocator fixedAllocator;
};


TEST_P(FixedAllocatorTest,Init)
{
    EXPECT_EQ(blockSize,fixedAllocator.BlockSize());
}

TEST_P(FixedAllocatorTest,HasBlock_NULL)
{
    EXPECT_FALSE(fixedAllocator.HasBlock(nullptr));
}

TEST_P(FixedAllocatorTest, Allocate)
{
    void * p = fixedAllocator.Allocate();
    EXPECT_TRUE(p);
    EXPECT_TRUE(fixedAllocator.HasBlock(p));
    EXPECT_TRUE(fixedAllocator.Deallocate(p));
}

TEST_P(FixedAllocatorTest, Deallocate_Assertion1)
{
    void * p = nullptr;
    EXPECT_DEATH(fixedAllocator.Deallocate(p),"Assertion failed: .*FixedAllocator.cpp");
}

TEST_P(FixedAllocatorTest, Deallocate_Assertion2)
{
    void * p = fixedAllocator.Allocate();
    EXPECT_DEATH(fixedAllocator.Deallocate(nullptr),"Assertion failed: .*FixedAllocator.cpp");
    EXPECT_TRUE(fixedAllocator.Deallocate(p));
}

INSTANTIATE_TEST_CASE_P(InstantiationName,
                        FixedAllocatorTest,
                        ::testing::Values(1,2,4,9,48));
