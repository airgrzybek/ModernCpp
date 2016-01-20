/*
 * test.h
 *
 *  Created on: 11 sty 2016
 *      Author: xxpowdaw
 */

#ifndef INC_TEST_H_
#define INC_TEST_H_

#include <cstdlib>
#include<fstream>
#include <iostream>
#include <chrono>

namespace Test
{

typedef std::chrono::high_resolution_clock Clock;

enum class Order
{
    Forward,
    Reverse,
    Random
};

template
<
    class T,
    std::size_t count
>
class Test
{
public:
    Test():
        elements()
    {

    }

    Test(const std::string & filename) :
        elements()
    {
        file.open(filename.c_str(), std::ofstream::out | std::ofstream::app);
    }

    ~Test()
    {
        file.close();

        for(std::size_t i = 0 ; i < count; ++i)
        {
            delete elements[i];
            elements[i] = nullptr;
        }
    }

    bool execute()
    {
        bool result = false;
        if (file.is_open())
        {
            std::cout << "Test start" << std::endl;
            Allocate();
            Deallocate();
            result = true;
        }
        else
        {
            std::cout << "File is not open" << std::endl;
        }

        return result;
    }

private:
    void Allocate()
    {
        file << "Allocation" << std::endl;

        if(Clock::is_steady)
            std::cout << "is steady" << std::endl;

        for(std::size_t i = 0; i < count ; ++i)
        {
            auto start = Clock::now();

            elements[i] = new T;

            auto finish = Clock::now();

            std::cout << i << "," << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << std::endl;
        }
    }

    void Deallocate()
    {
        file << "Deallocation" << std::endl;

        for(std::size_t i = 0; i < count ; ++i)
        {
            clock_t time = clock();

            delete elements[i];

            time = clock() - time;

            file << i << "," << ((float)time)/CLOCKS_PER_SEC << std::endl;
        }
    }

    T* elements[count];
    std::ofstream file;
};

class TestManager
{
public:
    TestManager(std::size_t runs);
    ~TestManager();

    bool executeTests();
private:
    std::size_t runNumber;
};

} // Test
#endif /* INC_TEST_H_ */
