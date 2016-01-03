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

const static std::size_t PAGE_SIZE = 256;

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
// caused valgrind errors
/*TEST_P(FixedAllocatorTest, Deallocate_Assertion1)
{
    void * p = nullptr;
#ifdef WINDOWS
    EXPECT_DEATH(fixedAllocator.Deallocate(p),"Assertion failed: .*FixedAllocator.cpp");
#else
    EXPECT_DEATH(fixedAllocator.Deallocate(p),".*FixedAllocator.cpp:*");
#endif
}

TEST_P(FixedAllocatorTest, Deallocate_Assertion2)
{
    void * p = fixedAllocator.Allocate();
#ifdef WINDOWS
    EXPECT_DEATH(fixedAllocator.Deallocate(nullptr),"Assertion failed: .*FixedAllocator.cpp");
#else
    EXPECT_DEATH(fixedAllocator.Deallocate(nullptr),".*FixedAllocator.cpp:*");
#endif
    EXPECT_TRUE(fixedAllocator.Deallocate(p));
}*/

TEST_P(FixedAllocatorTest, HasBlock_Failed)
{
    void * p = fixedAllocator.Allocate();
    unsigned char * pc = static_cast<unsigned char *>(p);
    pc = pc + (blockSize * 256);
    EXPECT_FALSE(fixedAllocator.HasBlock(static_cast<void *>(pc)));
}

TEST_P(FixedAllocatorTest, HasBlock_Failed2)
{
    const unsigned int size = 257;
    void * p[size] = {0};
    for(unsigned int i = 0; i < size; ++i)
    {
        p[i] = fixedAllocator.Allocate();
        EXPECT_TRUE(p[i]);
    }

    EXPECT_TRUE(fixedAllocator.HasBlock(static_cast<void *>(p[256])));
}

TEST_P(FixedAllocatorTest, Allocate8Chunks_ReverseDealloc)
{
    std::size_t size = (PAGE_SIZE / blockSize)*8;
    void * p[size];
    for(unsigned int i = 0; i < size; ++i)
    {
        p[i] = fixedAllocator.Allocate();
        EXPECT_TRUE(p[i]);
    }

    for (signed int i = size-1; i >= 0  ; --i)
    {
        EXPECT_TRUE(fixedAllocator.Deallocate(p[i]));
    }
}

TEST_P(FixedAllocatorTest, Allocate8Chunks)
{
    std::size_t size = (PAGE_SIZE / blockSize)*8;
    void * p[size];
    for(unsigned int i = 0; i < size; ++i)
    {
        p[i] = fixedAllocator.Allocate();
        EXPECT_TRUE(p[i]);
    }

    for (unsigned int i = 0; i < size  ; ++i)
    {
        EXPECT_TRUE(fixedAllocator.Deallocate(p[i]));
    }
}

TEST_P(FixedAllocatorTest, Allocate8Chunks_RandomDealloc)
{
    std::size_t size = (PAGE_SIZE / blockSize)*8;
    void * p[size];
    for(unsigned int i = 0; i < size; ++i)
    {
        p[i] = fixedAllocator.Allocate();
        EXPECT_TRUE(p[i]);
    }

    int index = rand() % size;

    EXPECT_TRUE(fixedAllocator.Deallocate(p[index]));
    p[index] = nullptr;
    p[index] = fixedAllocator.Allocate();
    EXPECT_TRUE(p[index]);

}

TEST_P(FixedAllocatorTest, Allocate8Chunks_OneEmptyChunk)
{
    std::size_t size = (PAGE_SIZE / blockSize)*8;
    void * p[size];
    for(unsigned int i = 0; i < size; ++i)
    {
        p[i] = fixedAllocator.Allocate();
        EXPECT_TRUE(p[i]);
    }

    unsigned int oneChunk = size/8;
    for (unsigned int i = 0; i < oneChunk  ; ++i)
    {
        EXPECT_TRUE(fixedAllocator.Deallocate(p[i]));
    }

    int index = rand() % oneChunk;
    p[index] = nullptr;
    p[index] = fixedAllocator.Allocate();
    EXPECT_TRUE(p[index]);
}


INSTANTIATE_TEST_CASE_P(InstantiationName,
                        FixedAllocatorTest,
                        ::testing::Values(4));
