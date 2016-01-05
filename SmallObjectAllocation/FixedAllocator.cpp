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
    Initialize(blockSize,pageSize);
}

void FixedAllocator::Initialize(std::size_t blockSize, std::size_t pageSize)
{
    assert(blockSize > 0);
    assert(pageSize >= blockSize);

    std::size_t numOfBlocks = pageSize / blockSize;
    if (numOfBlocks > MaxObjectsPerChunk)
    {
        numOfBlocks = MaxObjectsPerChunk;
    }
    else if (numOfBlocks < MinObjectsPerChunk)
    {
        numOfBlocks = MinObjectsPerChunk;
    }

    numBlocks = static_cast<unsigned char>(numOfBlocks);
    assert(numBlocks == numOfBlocks);
}

FixedAllocator::~FixedAllocator()
{
    for(auto iter : chunks)
    {
        iter.Release();
    }
}


void* FixedAllocator::Allocate()
{
    if(nullptr == allocChunk || allocChunk->IsFilled())
    {
        //check empty chunk
        if(nullptr != emptyChunk)
        {
            allocChunk = emptyChunk;
            emptyChunk = nullptr;
        }
        else
        {
            // check all chunks
            for(auto iter(chunks.begin()), end(chunks.end()); ; ++iter)
            {
                if(end == iter)
                {
                    //make new chunk
                    Chunk newChunk;
                    newChunk.Init(blockSize,numBlocks);
                    chunks.push_back(newChunk);
                    allocChunk = &chunks.back();
                    deallocChunk = &chunks.front();
                    break;
                }
                else if(!iter->IsFilled())
                {
                    allocChunk = &(*iter);
                    break;
                }
            }
        }
    }

    assert(nullptr != allocChunk);
    assert(!allocChunk->IsFilled());
    return allocChunk->Allocate(blockSize);
}

bool FixedAllocator::Deallocate(void * p)
{
    assert(nullptr != deallocChunk);
    assert(nullptr != p);

    Chunk * deallocate = nullptr;
    bool result = false;
    const std::size_t chunkLength = numBlocks * blockSize;


    if (!deallocChunk->HasBlock(p, chunkLength))
    {
        //find chunk which contains address p
        for (auto iter = chunks.begin(), end = chunks.end(); iter != end; ++iter)
        {
            if (iter->HasBlock(p, chunkLength))
            {
                deallocate = &(*iter);
                break;
            }
        }
    }
    else
    {
        deallocate = deallocChunk;
    }

    if(nullptr != deallocate)
    {
        deallocate->Deallocate(p,blockSize);
        result = true;

        // set new dealloc chunk
        deallocChunk = deallocate;

        if(deallocChunk->HasAvailable(numBlocks))
        {
            if (nullptr != emptyChunk)
            {
                // If last Chunk is empty, just change what deallocChunk_
                // points to, and release the last.  Otherwise, swap an empty
                // Chunk with the last, and then release it.
                Chunk * lastChunk = &chunks.back();
                if (lastChunk == deallocChunk)
                {
                    deallocChunk = emptyChunk;
                }
                else if (lastChunk != emptyChunk)
                {
                    std::swap(*emptyChunk, *lastChunk);
                }
                assert(lastChunk->HasAvailable(numBlocks));
                lastChunk->Release();
                chunks.pop_back();
                if ((allocChunk == lastChunk) || allocChunk->IsFilled())
                {
                    allocChunk = deallocChunk;
                }
            }
            emptyChunk = deallocChunk;
        }
    }

    return result;
}

std::size_t FixedAllocator::BlockSize() const
{
    return blockSize;
}

const Chunk * FixedAllocator::HasBlock(void * p) const
{
    const std::size_t chunkLength = numBlocks * blockSize;
    for(auto iter(chunks.begin()), end(chunks.end()); iter != end; ++iter)
    {
        const Chunk & chunk = *iter;
        if(chunk.HasBlock(p,chunkLength))
        {
            return &chunk;
        }
    }

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


