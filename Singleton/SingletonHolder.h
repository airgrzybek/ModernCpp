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
    void ScheduleDestruction(pDestructionFunction);
    void OnDeadReference();
};

template<class T> class SingleThreaded
{
public:
    typedef T VolatileType;
};

template<class T, template<class > class CreationPolicy = CreateUsingNew,
        template<class > class LifetimePolicy = DefaultLifetime,
        template<class > class ThreadingModel = SingleThreaded>
class SingletonHolder
{
public:
    static T& getInstance()
    {
        if (!instance)
        {
            typename ThreadingModel<T>::Lock guard;
            if (!instance)
            {
                if (destroyed)
                {
                    LifetimePolicy<T>::OnDeadReference();
                    destroyed = false;
                }
                instance = CreationPolicy<T>::Create();
                LifetimePolicy<T>::ScheduleCall(&destroySingleton);
            }
        }
        return *instance;
    }
private:
// Helpers
    static void destroySingleton()
    {
        assert(!destroyed);
        CreationPolicy<T>::Destroy(instance);
        instance = 0;
        destroyed = true;
    }
// Protection
    SingletonHolder();
// Data
    typedef typename ThreadingModel<T>::VolatileType InstanceType;
    static InstanceType* instance;
    static bool destroyed;
};


#endif /* SINGLETON_SINGLETONHOLDER_H_ */
