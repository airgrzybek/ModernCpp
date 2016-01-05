/*
 * SmallObjectAllocator.h
 *
 *  Created on: 28 paü 2015
 *      Author: xxpowdaw
 */

#ifndef SMALLOBJECTALLOCATION_SMALLOBJECTALLOCATOR_H_
#define SMALLOBJECTALLOCATION_SMALLOBJECTALLOCATOR_H_

#include "FixedAllocator.h"

namespace Memory
{


class SmallObjectAllocator
{
public:
    SmallObjectAllocator(std::size_t chunkSize, std::size_t maxObjectSize);
    ~SmallObjectAllocator();
    void * Allocate(std::size_t numBytes);
    void Deallocate(void * p, std::size_t size);

    // singleton
    SmallObjectAllocator() = delete;
    SmallObjectAllocator(const SmallObjectAllocator & other) = delete;
    SmallObjectAllocator & operator = (const SmallObjectAllocator & other) = delete;
private:
    typedef std::vector<FixedAllocator*> FixedAllocators;

    FixedAllocators pool;
    std::size_t maxObjectSize;
};

} // Memory


#endif /* SMALLOBJECTALLOCATION_SMALLOBJECTALLOCATOR_H_ */
