/*
 * main.cpp
 *
 *  Created on: 27 sie 2015
 *      Author: xxpowdaw
 */


#include <iostream>
#include <memory>
#include "triangle.h"
#include "square.h"
#include "AbstractFactory.h"

using namespace std;

int main()
{
    typedef Shape* (*CreateShapeCallback)();
    AbstractFactory<Shape,int,CreateShapeCallback> factory;

    factory.registerObject(0,&Triangle::create);
    factory.registerObject(1,&Square::create);

    auto_ptr<Shape> triangle(factory.createObject(0));
    auto_ptr<Shape> square(factory.createObject(1));

    return 0;
}

