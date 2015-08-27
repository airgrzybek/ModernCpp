/*
 * triangle.h
 *
 *  Created on: 27 sie 2015
 *      Author: xxpowdaw
 */

#ifndef INC_TRIANGLE_H_
#define INC_TRIANGLE_H_

#include "shape.h"

class Triangle: public Shape
{
public:
    Triangle();
    ~Triangle();

    virtual void Draw() override;
};

#endif /* INC_TRIANGLE_H_ */
