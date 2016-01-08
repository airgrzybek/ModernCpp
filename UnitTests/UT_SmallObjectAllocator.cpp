/*
 * UT_SmallObjectAllocator.cpp
 *
 *  Created on: 7 sty 2016
 *      Author: xxpowdaw
 */



#include <limits.h>
#include "gtest/gtest.h"
#include <vector>
#include "SmallObjectAllocator.h"


const std::size_t blockSize = 255;
const std::size_t maxObjSize = 64;

class SmallObjAllocTest : public testing::TestWithParam<std::size_t>
{
public:
    SmallObjAllocTest():
        allocator(blockSize,maxObjSize)
    {

    }
    ~SmallObjAllocTest()
    {

    }

    void SetUp()
    {
    }

    void TearDown()
    {
    }

    Memory::SmallObjectAllocator allocator;
};


TEST_P(SmallObjAllocTest, Allocate_Deallocate)
{
    void * p = nullptr;
    p = allocator.Allocate(GetParam());
    EXPECT_TRUE(p);
    allocator.Deallocate(p,GetParam());
}

INSTANTIATE_TEST_CASE_P(InstantiationName,
                        SmallObjAllocTest,
                        ::testing::Range((std::size_t)1,(std::size_t)128,(std::size_t)1));
