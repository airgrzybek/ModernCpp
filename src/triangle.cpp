/*
 * triangle.cpp
 *
 *  Created on: 27 sie 2015
 *      Author: xxpowdaw
 */

#include "triangle.h"
#include <iostream>

namespace
{
const bool created = SingleFactory::getInstance().registerObject(ShapeId::triangle,&Triangle::create);
}

Triangle::Triangle() : Shape()
{
    std::cout << "Triangle ctor" << std::endl;
}

Triangle::~Triangle()
{
    std::cout << "Triangle dtor" << std::endl;
}

void Triangle::Draw()
{
    std::cout << "Triangle Draw ()" << std::endl;
}
