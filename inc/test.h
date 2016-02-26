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
#include <ctime>
#include <ratio>
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
        using namespace std::chrono;
        file << "Allocation" << std::endl;

        if(steady_clock::is_steady)
            std::cout << "is steady" << std::endl;

        for(std::size_t i = 0; i < count ; ++i)
        {
            steady_clock::time_point start = steady_clock::now();

            elements[i] = new T;

            steady_clock::time_point finish = steady_clock::now();
            milliseconds time_span = duration_cast<milliseconds>(finish - start);

            std::cout << i << "," << time_span.count() << " pointer="<< elements[i] << std::endl;
        }
    }

    void Deallocate()
    {
        file << "Deallocation" << std::endl;
        system("PAUSE");
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
