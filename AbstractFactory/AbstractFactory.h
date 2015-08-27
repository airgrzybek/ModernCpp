/*
 * AbstractFactory.h
 *
 *  Created on: 27 sie 2015
 *      Author: xxpowdaw
 */

#ifndef ABSTRACTFACTORY_ABSTRACTFACTORY_H_
#define ABSTRACTFACTORY_ABSTRACTFACTORY_H_

#include<map>
#include<iostream>

template<
    class AbstractProduct,
    typename IdentifierType,
    typename ProductCreator>
class AbstractFactory
{
public:
    AbstractFactory()
    {
        std::cout << "Abstract Factory ctor" << std::endl;
    }
    virtual ~AbstractFactory()
    {
        std::cout << "Abstract Factory dtor" << std::endl;
    }

    bool Register(const IdentifierType& id, ProductCreator creator)
    {
        return associations_.insert(AssocMap::value_type(id, creator)).second;
    }
    bool Unregister(const IdentifierType& id)
    {
        return associations_.erase(id) == 1;
    }

    AbstractProduct* CreateObject(const IdentifierType& id)
    {
        typename AssocMap::const_iterator i = associations_.find(id);
        if (i != associations_.end())
        {
            return (i->second)();
        }
        else
        {
            std::cout << "No identifier found return null" << std::endl;
            return nullptr;
        }
    }

private:
    typedef std::map<IdentifierType, AbstractProduct> AssocMap;
    AssocMap associations_;
};

#endif /* ABSTRACTFACTORY_ABSTRACTFACTORY_H_ */
