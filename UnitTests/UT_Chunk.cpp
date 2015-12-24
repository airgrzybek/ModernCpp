#include <limits.h>
#include "gtest/gtest.h"
#include <vector>
#include "Chunk.h"

const static unsigned char MAX_U8 = 255;

class ChunkTestParam : public testing::TestWithParam<std::size_t>
{
public:
    ChunkTestParam() :
        blockSize(0)
    {

    }
    ~ChunkTestParam()
    {

    }

    void SetUp()
    {
        blockSize = GetParam();
        chunk.Init(blockSize,MAX_U8);
    }

    void TearDown()
    {
        chunk.Release();
    }
    std::size_t blockSize;
    Memory::Chunk chunk;
};

TEST_P(ChunkTestParam, Init)
{
    unsigned char * data = chunk.pData;
    EXPECT_TRUE(data);

    for(unsigned char i = 1; i < MAX_U8; ++i, data += blockSize)
    {
        EXPECT_EQ(i,*data);
    }
}

TEST_P(ChunkTestParam, Allocate)
{
    void * p = chunk.Allocate(blockSize);
    EXPECT_TRUE(p);
    EXPECT_EQ(MAX_U8-1,chunk.blocksAvailable);
    EXPECT_EQ(1,chunk.firstAvailableBlock);
}

TEST_P(ChunkTestParam, Allocate_NULL)
{
    chunk.blocksAvailable=0;
    void * p = chunk.Allocate(blockSize);
    EXPECT_FALSE(p);
}

TEST_P(ChunkTestParam, Deallocate)
{
    void * p = chunk.Allocate(blockSize);
    EXPECT_TRUE(p);
    EXPECT_EQ(MAX_U8-1,chunk.blocksAvailable);
    EXPECT_EQ(1,chunk.firstAvailableBlock);

    chunk.Deallocate(p,blockSize);
    EXPECT_EQ(MAX_U8,chunk.blocksAvailable);
    EXPECT_EQ(0,chunk.firstAvailableBlock);
}

TEST_P(ChunkTestParam, Deallocate_Death)
{
    void * p = 0;
#ifdef WINDOWS
    ASSERT_DEATH(chunk.Deallocate(p,blockSize),"Assertion failed: .*Chunk.cpp");
#else
    ASSERT_DEATH(chunk.Deallocate(p,blockSize),".*Chunk.cpp:119.*");
#endif
}

TEST_P(ChunkTestParam, HasBlock)
{
    void * p = chunk.Allocate(blockSize);

    EXPECT_TRUE(chunk.HasBlock(p,blockSize));
}

TEST_P(ChunkTestParam,overflow)
{
    for(unsigned char i = 0; i < MAX_U8; ++i)
    {
        unsigned char * p = static_cast<unsigned char *>(chunk.Allocate(blockSize));
        *p = 0;
    }
    EXPECT_FALSE(chunk.Allocate(blockSize));
    EXPECT_EQ(0, chunk.blocksAvailable);
    EXPECT_EQ(255, chunk.firstAvailableBlock);
}

TEST_P(ChunkTestParam, Release)
{
    chunk.Release();

    EXPECT_FALSE(chunk.pData);
    EXPECT_EQ(0,chunk.blocksAvailable);
}

TEST_P(ChunkTestParam, HasAvailible)
{
    EXPECT_TRUE(chunk.HasAvailable(MAX_U8));
}

INSTANTIATE_TEST_CASE_P(InstantiationName,
                        ChunkTestParam,
                        ::testing::Values(1,2,4,9,48));
