/*
 * SmallObjectAllocator.cpp
 *
 *  Created on: 5 sty 2016
 *      Author: xxpowdaw
 */

#include "SmallObjectAllocator.h"
#include <cassert>

namespace Memory
{

SmallObjectAllocator::SmallObjectAllocator(std::size_t chunkSize, std::size_t maxObjectSize) :
        maxObjectSize(maxObjectSize)
{
    pool.resize(maxObjectSize);

    for(std::size_t i = 0; i < maxObjectSize; ++i)
    {
        pool[i] = new FixedAllocator(i+1,chunkSize);
    }
}

SmallObjectAllocator::~SmallObjectAllocator()
{
    for(auto iter(pool.begin()), end(pool.end()); iter != end; ++iter)
    {
        delete (*iter);
        (*iter) = nullptr;
    }
}

void * SmallObjectAllocator::Allocate(std::size_t numbytes)
{
    if(numbytes > maxObjectSize)
    {
        return operator new( numbytes );
    }
    else
    {
        return pool[numbytes]->Allocate();
    }
}


void SmallObjectAllocator::Deallocate(void * p, std::size_t size)
{
    if(size > maxObjectSize)
    {
        operator delete (p);
    }
    else
    {
        bool result = pool[size]->Deallocate(p);
        assert(result);
    }
}

}


