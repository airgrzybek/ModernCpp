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
    AbstractFactory<Shape,ShapeId,CreateShapeCallback,DefaultFactoryError> factory;

    factory.registerObject(ShapeId::triangle,&Triangle::create);
    factory.registerObject(ShapeId::square,&Square::create);

    unique_ptr<Shape> triangle(factory.createObject(ShapeId::triangle));
    unique_ptr<Shape> square(factory.createObject(ShapeId::square));

    return 0;
}

