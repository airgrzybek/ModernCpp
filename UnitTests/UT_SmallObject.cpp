/*
 * UT_SmallObject.cpp
 *
 *  Created on: 8 sty 2016
 *      Author: xxpowdaw
 */

#include <limits.h>
#include "gtest/gtest.h"
#include <vector>
#include "SmallObject.h"


class SmallClass : public Memory::SmallObject
{
public:
    SmallClass() :
        SmallObject(),
        a(0)
    {

    }

    ~SmallClass()
    {}

    unsigned int a;
};

class BigClass : public Memory::SmallObject
{
public:
    BigClass() :
        SmallObject(),
        a()
    {

    }

    ~BigClass()
    {}

    unsigned int a[128];
};

class SmallObjTest : public testing::Test
{
public:
    SmallObjTest() :
        small(nullptr),
        big(nullptr)
    {

    }
    ~SmallObjTest()
    {

    }

    void SetUp()
    {
    }

    void TearDown()
    {
    }

    SmallClass * small;
    BigClass * big;
};

TEST_F(SmallObjTest, Allocate_Deallocate)
{
    small = new SmallClass;
    big = new BigClass;

    EXPECT_TRUE(small);
    EXPECT_TRUE(big);

    delete small;
    delete big;
}
