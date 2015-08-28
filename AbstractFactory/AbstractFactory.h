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

    bool registerObject(const IdentifierType& id, ProductCreator creator)
    {
        return associations_.insert(AssocItem(id, creator)).second;
    }

    bool unregisterObject(const IdentifierType& id)
    {
        return associations_.erase(id) == 1;
    }

    AbstractProduct* createObject(const IdentifierType& id)
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
    typedef std::map<IdentifierType, ProductCreator> AssocMap;
    typedef std::pair<IdentifierType,ProductCreator> AssocItem;
    AssocMap associations_;
};

#endif /* ABSTRACTFACTORY_ABSTRACTFACTORY_H_ */
