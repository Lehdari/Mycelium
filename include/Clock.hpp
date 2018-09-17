//
// Created by Lehdari on 25.6.2018.
//

#ifndef MYCELIUM_CLOCK_HPP
#define MYCELIUM_CLOCK_HPP


#include <chrono>


namespace mm {

    class Clock {
    public:
        Clock();

        double operator()();

    private:
        std::chrono::steady_clock::time_point _t;
    };

}


#endif // MYCELIUM_CLOCK_HPP
