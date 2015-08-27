/*
 * square.h
 *
 *  Created on: 27 sie 2015
 *      Author: xxpowdaw
 */

#ifndef INC_SQUARE_H_
#define INC_SQUARE_H_

#include "shape.h"

class Square: public Shape
{
public:
    Square();
    virtual ~Square();

    void Draw() override;

    static Shape * create()
    {
        return new Square;
    }
};

#endif /* INC_SQUARE_H_ */
