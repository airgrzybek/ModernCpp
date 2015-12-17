/*
 * Chunk.cpp
 *
 *  Created on: 15 gru 2015
 *      Author: xxpowdaw
 */

#include "Chunk.h"
#include <cassert>

namespace Memory
{

void Chunk::Init(std::size_t blockSize, unsigned char blocks)
{
    pData = new unsigned char[blockSize * blocks];
    firstAvailableBlock = 0;
    blocksAvailable = blocks;
    unsigned char i = 0;
    unsigned char* p = pData;
    for (; i != blocks; p += blockSize)
    {
        *p = ++i;
    }
}

void Chunk::Release()
{
    delete [] pData;
    pData = 0;
    blocksAvailable = 0;
    firstAvailableBlock = 0;
}

void Chunk::Reset(std::size_t blockSize, unsigned char blocks )
{
    assert(blockSize > 0);
    assert(blocks > 0);
    // Overflow check
    assert((blockSize * blocks) / blockSize == blocks);

    firstAvailableBlock = 0;
    blocksAvailable = blocks;
    unsigned char i = 0;
    unsigned char* p = pData;
    for (; i != blocks; p += blockSize)
    {
        *p = ++i;
    }
}

bool Chunk::IsBlockAvailable( void * p, unsigned char numBlocks, std::size_t blockSize ) const
{
    if(IsFilled())
    {
        return false;
    }
    else
    {
        unsigned char * place = static_cast<unsigned char *>(p);
        // Alignment check
        assert( ( place - pData ) % blockSize == 0 );

        unsigned char blockIndex = ((place - pData)/blockSize);
        unsigned char index = firstAvailableBlock;

        if(index == blockIndex)
        {
            return true;
        }
        else
        {
            unsigned char * nextBlock = 0;
            for(unsigned char i = 0; ;)
            {
                nextBlock = pData + (index * blockSize); // get next free block address
                ++i;

                if(i >= blocksAvailable)
                {
                    break;
                }

                index = *nextBlock; // get index of next free block
                if(index == blockIndex)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void* Chunk::Allocate(std::size_t blockSize)
{
    if (!blocksAvailable)
    {
        return 0;
    }

    unsigned char* pResult = pData + (firstAvailableBlock * blockSize);
    // Update firstAvailableBlock_ to point to the next block
    firstAvailableBlock = *pResult;
    --blocksAvailable;
    return pResult;
}

void Chunk::Deallocate(void* p, std::size_t blockSize)
{
    assert(p >= pData);
    unsigned char* toRelease = static_cast<unsigned char*>(p);
    // Alignment check
    assert((toRelease - pData) % blockSize == 0);
    *toRelease = firstAvailableBlock;
    firstAvailableBlock = static_cast<unsigned char>((toRelease - pData) / blockSize);
    // Truncation check
    assert(firstAvailableBlock == (toRelease - pData) / blockSize);
    ++blocksAvailable;
}

} /* Memory */


