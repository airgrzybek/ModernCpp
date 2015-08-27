/*
 * main.cpp
 *
 *  Created on: 27 sie 2015
 *      Author: xxpowdaw
 */


#include <iostream>
#include <memory>
#include "triangle.h"


int main()
{
    std::auto_ptr<Shape> shape(new Triangle);

    return 0;
}

