//
// Created by Lehdari on 25.6.2018.
//

#include "Clock.hpp"


using namespace mm;


Clock::Clock() :
    _t(std::chrono::steady_clock::now())
{
}

double Clock::operator()()
{
    auto t = std::chrono::steady_clock::now();
    double out = std::chrono::duration_cast<std::chrono::duration<double>>(t-_t).count();
    _t = t;
    return out;
}
