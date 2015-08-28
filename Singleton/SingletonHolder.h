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
    static InstanceType * instance;
    static bool destroyed;
};

template<class T, template<class > class CreationPolicy,
        template<class > class LifetimePolicy,
        template<class > class ThreadingModel>
//T * SingletonHolder<T,CreationPolicy,LifetimePolicy,ThreadingModel>::instance = 0;
typename SingletonHolder<T,CreationPolicy,LifetimePolicy,ThreadingModel>::InstanceType * SingletonHolder<T,CreationPolicy,LifetimePolicy,ThreadingModel>::instance = 0;

template<class T, template<class > class CreationPolicy,
        template<class > class LifetimePolicy,
        template<class > class ThreadingModel>
bool SingletonHolder<T,CreationPolicy,LifetimePolicy,ThreadingModel>::destroyed = false;


template<class T, template<class > class CreationPolicy,
        template<class > class LifetimePolicy,
        template<class > class ThreadingModel>
T & SingletonHolder<T,CreationPolicy,LifetimePolicy,ThreadingModel>::getInstance()
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
            instance = CreationPolicy < T > ::create();
            LifetimePolicy<T>::ScheduleDestruction(&destroySingleton);
        }
    }
    return *instance;
}


template<class T, template<class > class CreationPolicy,
        template<class > class LifetimePolicy,
        template<class > class ThreadingModel>
void SingletonHolder<T,CreationPolicy,LifetimePolicy,ThreadingModel>::destroySingleton()
{
    assert(!destroyed);
    CreationPolicy<T>::destroy(instance);
    instance = 0;
    destroyed = true;
}
#endif /* SINGLETON_SINGLETONHOLDER_H_ */
