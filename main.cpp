/*
 * main.cpp
 *
 *  Created on: 27 sie 2015
 *      Author: xxpowdaw
 */


#include <iostream>
#include <memory>
#include <triangle.h>
#include <square.h>
#include <AbstractFactory.h>
//#include <SingletonHolder.h>

using namespace std;

int main()
{
    unique_ptr<Shape> triangle(SingleFactory::getInstance().createObject(ShapeId::triangle));
    unique_ptr<Shape> square(SingleFactory::getInstance().createObject(ShapeId::square));

    return 0;
}

