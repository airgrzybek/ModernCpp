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
#include<SingletonHolder.h>

template<class IdentifierType, class ProductType>
class DefaultFactoryError
{
public:
    class Exception : public std::exception
    {
    public:
        Exception(const IdentifierType& unknownId)
        : unknownId_(unknownId)
        {
        }
        virtual const char* what()
        {
            return "Unknown object type passed to Factory.";
        }
        const IdentifierType GetId()
        {
            return unknownId_;
        };
    private:
        IdentifierType unknownId_;
    };
protected:
    ProductType * onUnknownType(const IdentifierType& id)
    {
        throw Exception(id);
    }
};

template<
    class AbstractProduct,
    typename IdentifierType,
    typename ProductCreator,
    template<typename,class> class FactoryErrorPolicy>
class AbstractFactory: public FactoryErrorPolicy<IdentifierType,AbstractProduct>
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
        return this->onUnknownType(id);
    }

private:
    typedef std::map<IdentifierType, ProductCreator> AssocMap;
    typedef std::pair<IdentifierType,ProductCreator> AssocItem;
    AssocMap associations_;
};

typedef Shape* (*CreateShapeCallback)();
typedef SingletonHolder<AbstractFactory<Shape,int,CreateShapeCallback,DefaultFactoryError>> singleFactory;

#endif /* ABSTRACTFACTORY_ABSTRACTFACTORY_H_ */
