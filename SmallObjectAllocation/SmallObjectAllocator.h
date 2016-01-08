/*
 * SmallObjectAllocator.h
 *
 *  Created on: 28 paü 2015
 *      Author: xxpowdaw
 */

#ifndef SMALLOBJECTALLOCATION_SMALLOBJECTALLOCATOR_H_
#define SMALLOBJECTALLOCATION_SMALLOBJECTALLOCATOR_H_

#include "FixedAllocator.h"
#include <SingletonHolder.h>

namespace Memory
{

const std::size_t MAX_SMALL_BOJECT_SIZE = 64;
const std::size_t CHUNK_SIZE = 4096;

class SmallObjectAllocator
{
public:
    SmallObjectAllocator(std::size_t chunkSize, std::size_t maxObjectSize);
    ~SmallObjectAllocator();
    void * Allocate(std::size_t numBytes);
    void Deallocate(void * p, std::size_t size);

    // singleton
    SmallObjectAllocator(const SmallObjectAllocator & other) = delete;
    SmallObjectAllocator & operator = (const SmallObjectAllocator & other) = delete;
private:
    typedef std::vector<FixedAllocator*> FixedAllocators;

    FixedAllocators pool;
    std::size_t maxObjectSize;
};

template
<
    template<class > class CreationPolicy = CreateUsingNew,
    template<class > class LifetimePolicy = DefaultLifetime,
    template<class > class ThreadingModel = SingleThreaded,
    std::size_t chunkSize = CHUNK_SIZE,
    std::size_t maxSmallObjectSize = MAX_SMALL_BOJECT_SIZE
>
class AllocatorSingleton : public SmallObjectAllocator
{
    // singleton
    AllocatorSingleton(const AllocatorSingleton & other) = delete;
    AllocatorSingleton & operator = (const AllocatorSingleton & other) = delete;
public:

    /// Defines type of allocator.
    typedef AllocatorSingleton< CreationPolicy, LifetimePolicy, ThreadingModel, chunkSize,
        maxSmallObjectSize > MyAllocator;

    /// Defines type for thread-safety locking mechanism.
    typedef ThreadingModel< MyAllocator > MyThreadingModel;

    /// Defines singleton made from allocator.
    typedef SingletonHolder< MyAllocator, CreateStatic,
        LifetimePolicy, ThreadingModel > MyAllocatorSingleton;


    /// Returns reference to the singleton.
    inline static AllocatorSingleton & getInstance( )
    {
        return MyAllocatorSingleton::getInstance();
    }

    /// The default constructor is not meant to be called directly.
    inline AllocatorSingleton() :
        SmallObjectAllocator( chunkSize, maxSmallObjectSize )
        {}

    /// The destructor is not meant to be called directly.
    inline ~AllocatorSingleton( void ) {}

};

} // Memory


#endif /* SMALLOBJECTALLOCATION_SMALLOBJECTALLOCATOR_H_ */
