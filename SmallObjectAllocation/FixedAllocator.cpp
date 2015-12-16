/*
 * FixedAllocator.cpp
 *
 *  Created on: 15 gru 2015
 *      Author: xxpowdaw
 */

#include "FixedAllocator.h"
#include <cassert>

namespace Memory
{

unsigned char FixedAllocator::MinObjectsPerChunk= 8;
unsigned char FixedAllocator::MaxObjectsPerChunk = 255;

FixedAllocator::FixedAllocator() :
        blockSize(0),
        numBlocks(0),
        chunks(),
        allocChunk(0),
        deallocChunk(0),
        emptyChunk(0)
{

}

FixedAllocator::FixedAllocator(std::size_t blockSize, std::size_t pageSize) :
                blockSize(blockSize),
                numBlocks(0),
                chunks(),
                allocChunk(0),
                deallocChunk(0),
                emptyChunk(0)
{
    assert( blockSize > 0 );
    assert( pageSize >= blockSize );

    std::size_t numOfBlocks = pageSize / blockSize;
    if ( numOfBlocks > MaxObjectsPerChunk ) numOfBlocks = MaxObjectsPerChunk;
    else if ( numOfBlocks < MinObjectsPerChunk ) numOfBlocks = MinObjectsPerChunk;

    numBlocks = static_cast<unsigned char>(numOfBlocks);
    assert(numBlocks == numOfBlocks);
}

FixedAllocator::~FixedAllocator()
{

}


void* FixedAllocator::Allocate()
{
    return 0;
}

bool FixedAllocator::Deallocate(void * p)
{
    return false;
}

std::size_t FixedAllocator::BlockSize() const
{
    return blockSize;
}

const Chunk * FixedAllocator::HasBlock(void * p) const
{
    return 0;
}

bool FixedAllocator::IsCorrupt( void ) const
{
    return true;
}

bool FixedAllocator::TrimChunkList( void )
{
    return false;
}

} /* Memory */


