//
// Created by Lehdari on 26.6.2018.
//

#ifndef MYCELIUM_MORTON_HPP
#define MYCELIUM_MORTON_HPP


#include "MathTypes.hpp"


namespace mm {

    inline uint64_t expandBits(uint64_t v)
    {
        v = (v*0x0000000100000001u) & 0xFFFF00000000FFFFu;
        v = (v*0x0000000000010001u) & 0x00FF0000FF0000FFu;
        v = (v*0x0000000000000101u) & 0xF00F00F00F00F00Fu;
        v = (v*0x0000000000000011u) & 0x30C30C30C30C30C3u;
        v = (v*0x0000000000000005u) & 0x9249249249249249u;
        return v;
    }

    inline uint64_t toMorton(const Vec3f& p)
    {
        uint32_t x = (*(uint32_t *) (&p(0)) & 0x007fffff) >> 2;
        uint32_t y = (*(uint32_t *) (&p(1)) & 0x007fffff) >> 2;
        uint32_t z = (*(uint32_t *) (&p(2)) & 0x007fffff) >> 2;

        return expandBits(x) | expandBits(y)*2 | expandBits(z)*4;
    }

}


#endif // MYCELIUM_MORTON_HPP
