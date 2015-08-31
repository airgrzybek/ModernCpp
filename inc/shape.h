/*
 * shape.h
 *
 *  Created on: 27 sie 2015
 *      Author: xxpowdaw
 */

#ifndef INC_SHAPE_H_
#define INC_SHAPE_H_

#include<SingletonHolder.h>
#include<AbstractFactory.h>

enum class ShapeId
{
    triangle,
    square
};

class Shape
{
public:
    virtual ~Shape(){};
    virtual void Draw() = 0;
};

typedef Shape* (*CreateShapeCallback)();
typedef SingletonHolder<AbstractFactory<Shape,ShapeId,CreateShapeCallback,DefaultFactoryError>,CreateStatic> SingleFactory;

#endif /* INC_SHAPE_H_ */
