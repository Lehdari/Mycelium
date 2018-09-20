//
// Created by Lehdari on 20.9.2018.
//
// This file specifies a CIE 1931 color handling system
//

#ifndef MYCELIUM_CIE1931_HPP
#define MYCELIUM_CIE1931_HPP


#include "Spectrum.hpp"
#include "MathTypes.hpp"


namespace mm {


    class CIE1931 {
    public:
        CIE1931(const Spectrum& spectrum);

        Vec3f getRGB() const;

    private:
        float   _intensity[39];
        float   _X;
        float   _Y;
        float   _Z;
        float   _x;
        float   _y;
        Mat3f   _m; // XYZ to RGB conversion matrix

        // Response functions for CIE standard observer
        static const float  so_x[39];
        static const float  so_y[39];
        static const float  so_z[39];

        // XYZ to sRGB D65 matrix
        static const float  srgb_d65[9];

        // D65 white point
        static const float  d65_x;
        static const float  d65_y;
    };


}


#endif // MYCELIUM_CIE1931_HPP
