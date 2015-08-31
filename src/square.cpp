/*
 * square.cpp
 *
 *  Created on: 27 sie 2015
 *      Author: xxpowdaw
 */

#include "square.h"
#include <iostream>

using namespace std;

namespace
{
const bool created = SingleFactory::getInstance().registerObject(ShapeId::square,&Square::create);
}

Square::Square()
{
    // TODO Auto-generated constructor stub
    cout << "Square ctor" << endl;
}

Square::~Square()
{
    // TODO Auto-generated destructor stub
    cout << "Square dtor" << endl;
}

void Square::Draw()
{
    cout << "Square Draw()" << endl;
}

