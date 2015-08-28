/*
 * SingletonHolder.cpp
 *
 *  Created on: 28 sie 2015
 *      Author: xxpowdaw
 */



#include "SingletonHolder.h"


template<class T, template<class > class CreationPolicy,
        template<class > class LifetimePolicy,
        template<class > class ThreadingModel>
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
                LifetimePolicy < T > ::OnDeadReference();
                destroyed = false;
            }
            instance = CreationPolicy < T > ::create();
            LifetimePolicy < T > ::ScheduleDestruction(&destroySingleton);
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
