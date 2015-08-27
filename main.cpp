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

int main()
{
    typedef Shape* (*CreateShapeCallback)();
    AbstractFactory<Shape,int,CreateShapeCallback> factory;

    return 0;
}

