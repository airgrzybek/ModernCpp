/*
 * SmallObject.h
 *
 *  Created on: 28 paü 2015
 *      Author: xxpowdaw
 */

#ifndef SMALLOBJECTALLOCATION_SMALLOBJECT_H_
#define SMALLOBJECTALLOCATION_SMALLOBJECT_H_

#include <cstdlib>
#include "SmallObjectAllocator.h"

namespace Memory
{

class SmallObject
{
public:
    // Instance of SmallObjectAllocator
    typedef AllocatorSingleton<> Allocator;

    static void * operator new(std::size_t size);
    static void operator delete(void * p, std::size_t size);
    virtual ~SmallObject();
};

}// Memory


#endif /* SMALLOBJECTALLOCATION_SMALLOBJECT_H_ */
