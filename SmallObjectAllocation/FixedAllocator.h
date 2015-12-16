/*
 * FixedAllocator.h
 *
 *  Created on: 28 paü 2015
 *      Author: xxpowdaw
 */

#ifndef SMALLOBJECTALLOCATION_FIXEDALLOCATOR_H_
#define SMALLOBJECTALLOCATION_FIXEDALLOCATOR_H_

#include "Chunk.h"
#include <vector>

namespace Memory
{

class FixedAllocator
{
public:
    FixedAllocator();
    FixedAllocator(std::size_t blockSize, std::size_t pageSize);
    ~FixedAllocator();

    FixedAllocator(const FixedAllocator&) = delete;
    FixedAllocator & operator = (const FixedAllocator &) = delete;

    void* Allocate();
    bool Deallocate(void * p);

    std::size_t BlockSize() const;
    const Chunk * HasBlock(void * p) const;
    bool IsCorrupt( void ) const;
    bool TrimChunkList( void );
private:

    /// Fewest # of objects managed by a Chunk.
    static unsigned char MinObjectsPerChunk;

    /// Most # of objects managed by a Chunk - never exceeds UCHAR_MAX.
    static unsigned char MaxObjectsPerChunk;

    std::size_t blockSize;
    unsigned char numBlocks;
    typedef std::vector<Chunk> Chunks;
    Chunks chunks;
    Chunk* allocChunk;
    Chunk* deallocChunk;
    Chunk* emptyChunk;
};


} /* Memory */



#endif /* SMALLOBJECTALLOCATION_FIXEDALLOCATOR_H_ */
