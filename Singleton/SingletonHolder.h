/*
 * SingletonHolder.h
 *
 *  Created on: 28 sie 2015
 *      Author: xxpowdaw
 */

#ifndef SINGLETON_SINGLETONHOLDER_H_
#define SINGLETON_SINGLETONHOLDER_H_

#include<assert.h>

template<class T>
class CreateUsingNew
{
public:
    static T * create()
    {
        return new T;
    }

    static void destroy(T * ptr)
    {
        delete ptr;
    }
};

template<class T>
class DefaultLifetime
{
public:
    typedef void (*pDestructionFunction)();
    static void ScheduleDestruction(pDestructionFunction){}
    static void OnDeadReference(){}
};

template<class T> class SingleThreaded
{
public:
    class Lock
    {
    public:
        Lock(){}
        ~Lock(){}
    };

    typedef T VolatileType;
};

template<class T, template<class > class CreationPolicy = CreateUsingNew,
        template<class > class LifetimePolicy = DefaultLifetime,
        template<class > class ThreadingModel = SingleThreaded>
class SingletonHolder
{
public:
    static T & getInstance();
private:
// Helpers
    static void destroySingleton();
// Protection
    SingletonHolder();
// Data
    typedef typename ThreadingModel<T>::VolatileType InstanceType;
    static InstanceType* instance;
    static bool destroyed;
};

#endif /* SINGLETON_SINGLETONHOLDER_H_ */
