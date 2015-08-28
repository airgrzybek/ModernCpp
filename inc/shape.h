/*
 * shape.h
 *
 *  Created on: 27 sie 2015
 *      Author: xxpowdaw
 */

#ifndef INC_SHAPE_H_
#define INC_SHAPE_H_


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


#endif /* INC_SHAPE_H_ */
