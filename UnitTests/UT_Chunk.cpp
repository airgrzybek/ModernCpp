#include <limits.h>
#include "gtest/gtest.h"
#include <vector>
#include "Chunk.h"

const static unsigned char MAX_U8 = 255;

class ChunkTest : public testing::Test
{
public:
    ChunkTest()
    {

    }
    ~ChunkTest()
    {

    }

    void SetUp()
    {
    }

    void TearDown()
    {
        chunk.Release();
    }

    Memory::Chunk chunk;
};

TEST_F(ChunkTest, Init)
{
    chunk.Init(4,255);

    unsigned char * data = chunk.pData;
    EXPECT_TRUE(data);


    for(unsigned char i = 1; i < MAX_U8; ++i, data +=4)
    {
        EXPECT_EQ(i,*data);
    }
}

class ChunkTestPAram : public testing::TestWithParam<std::size_t>
{
public:
    ChunkTestPAram() :
        blockSize(0)
    {

    }
    ~ChunkTestPAram()
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

TEST_P(ChunkTestPAram, Init)
{
    unsigned char * data = chunk.pData;
    EXPECT_TRUE(data);

    for(unsigned char i = 1; i < MAX_U8; ++i, data += blockSize)
    {
        EXPECT_EQ(i,*data);
    }
}

INSTANTIATE_TEST_CASE_P(InstantiationName,
                        ChunkTestPAram,
                        ::testing::Values(1,2,4,9,48));

TEST_P(ChunkTestPAram, Allocate)
{
    void * p = chunk.Allocate(blockSize);
    EXPECT_TRUE(p);
    EXPECT_EQ(MAX_U8-1,chunk.blocksAvailable);
    EXPECT_EQ(1,chunk.firstAvailableBlock);
}

TEST_P(ChunkTestPAram, Allocate_NULL)
{
    chunk.blocksAvailable=0;
    void * p = chunk.Allocate(blockSize);
    EXPECT_FALSE(p);
}

TEST_P(ChunkTestPAram, Deallocate)
{
    void * p = chunk.Allocate(blockSize);
    EXPECT_TRUE(p);
    EXPECT_EQ(MAX_U8-1,chunk.blocksAvailable);
    EXPECT_EQ(1,chunk.firstAvailableBlock);

    chunk.Deallocate(p,blockSize);
    EXPECT_EQ(MAX_U8,chunk.blocksAvailable);
    EXPECT_EQ(0,chunk.firstAvailableBlock);
}
