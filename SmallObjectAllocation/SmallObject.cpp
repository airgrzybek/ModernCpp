/*
 * SmallObject.cpp
 *
 *  Created on: 8 sty 2016
 *      Author: xxpowdaw
 */

#include "SmallOBject.h"
#include "SmallObjectAllocator.h"
#include <SingletonHolder.h>

namespace Memory
{

typedef SingletonHolder<SmallObjectAllocator> Allocator;

void * SmallObject::operator new(std::size_t size)
{
    return Allocator::getInstance().Allocate(size);
}

void SmallObject::operator delete(void * p, std::size_t size)
{
    Allocator::getInstance().Deallocate(p,size);
}

SmallObject::~SmallObject()
{

}

}// Memory


