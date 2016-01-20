/*
 * main.cpp
 *
 *  Created on: 27 sie 2015
 *      Author: xxpowdaw
 */


#include <iostream>
#include <memory>
#include <shape.h>
#include <test.h>
#include <triangle.h>

#ifdef WINDOWS
#include <windows.h>
#endif

using namespace std;

int main()
{
#ifdef WINDOWS
    // this prevents annoying error message boxes popping up
    // when assert is called in your program code
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
#endif

    unique_ptr<Shape> triangle(SingleFactory::getInstance().createObject(ShapeId::triangle));
    unique_ptr<Shape> square(SingleFactory::getInstance().createObject(ShapeId::square));


    Test::Test<Triangle,100> test1("run1.txt");

    test1.execute();

    return 0;
}

