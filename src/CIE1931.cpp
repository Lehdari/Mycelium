//
// Created by Lehdari on 20.9.2018.
//

#include "CIE1931.hpp"


using namespace mm;


const float CIE1931::so_x[39] = {
    0.00140f, 0.00420f, 0.01430f, 0.04350f, 0.13440f, 0.28390f,
    0.34830f, 0.33620f, 0.29080f, 0.19540f, 0.09560f, 0.03200f,
    0.00490f, 0.00930f, 0.06330f, 0.16550f, 0.29040f, 0.43440f,
    0.59450f, 0.76210f, 0.91630f, 1.02630f, 1.06220f, 1.00260f,
    0.85440f, 0.64240f, 0.44790f, 0.28350f, 0.16490f, 0.08740f,
    0.04680f, 0.02270f, 0.01140f, 0.00580f, 0.00290f, 0.00140f,
    0.00070f, 0.00030f, 0.00020f
};

const float CIE1931::so_y[39] = {
    0.00004f, 0.00012f, 0.00040f, 0.00120f, 0.00400f, 0.01160f,
    0.02300f, 0.03800f, 0.06000f, 0.09100f, 0.13900f, 0.20800f,
    0.32300f, 0.50300f, 0.71000f, 0.86200f, 0.95400f, 0.99500f,
    0.99500f, 0.95200f, 0.87000f, 0.75700f, 0.63100f, 0.50300f,
    0.38100f, 0.26500f, 0.17500f, 0.10700f, 0.06100f, 0.03200f,
    0.01700f, 0.00820f, 0.00410f, 0.00210f, 0.00105f, 0.00052f,
    0.00025f, 0.00012f, 0.00006f
};

const float CIE1931::so_z[39] = {
    0.00650f, 0.02010f, 0.06790f, 0.20740f, 0.64560f, 1.38560f,
    1.74710f, 1.77210f, 1.66920f, 1.28760f, 0.81300f, 0.46520f,
    0.27200f, 0.15820f, 0.07820f, 0.04220f, 0.02030f, 0.00870f,
    0.00390f, 0.00210f, 0.00170f, 0.00110f, 0.00080f, 0.00030f,
    0.00020f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f,
    0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f,
    0.00000f, 0.00000f, 0.00000f
};

const float CIE1931::srgb_d65[9] = {
    3.2404542f, -1.5371385f, -0.4985314f,
    -0.9692660f,  1.8760108f,  0.0415560f,
    0.0556434f, -0.2040259f,  1.0572252f
};

const float CIE1931::d65_x = 0.31271f;
const float CIE1931::d65_y = 0.32902f;


CIE1931::CIE1931(const Spectrum& spectrum) :
    _intensity  {0.0f},
    _X          (0.0f),
    _Y          (0.0f),
    _Z          (0.0f),
    _x          (0.0f),
    _y          (0.0f),
    _m          (srgb_d65)
{
    for (auto i=0u; i<39; ++i) {
        _intensity[i] = spectrum.sample(380.0f + i*10.0f);
        _X += _intensity[i] * so_x[i];
        _Y += _intensity[i] * so_y[i];
        _Z += _intensity[i] * so_z[i];
    }

    _x = _X / (_X + _Y + _Z);
    _y = _Y / (_X + _Y + _Z);

    _m.transposeInPlace();
}

Vec3f CIE1931::getRGB() const
{
    static Vec3f d65 = Vec3f(d65_x, d65_y, 1.0f-d65_x-d65_y);

    Vec3f c = Vec3f(_x, _y, 1.0f-_x-_y);

    // Correct luminosity
    c *= _Y;

    // Gamma correction
    c[0] = powf(c[0], 0.45454545f);
    c[1] = powf(c[1], 0.45454545f);
    c[2] = powf(c[2], 0.45454545f);

    Vec3f rgb = _m * c;

    // Constrain color to sRGB gamut
    float t = 0.0f;
    Vec3f d = d65-c;
    if (rgb[0] < 0.0f) {
        Vec3f r = _m.block<1, 3>(0, 0);
        float tt = -r.dot(c) / r.dot(d);
        if (tt > t) t = tt;
    }
    if (rgb[1] < 0.0f) {
        Vec3f r = _m.block<1, 3>(1, 0);
        float tt = -r.dot(c) / r.dot(d);
        if (tt > t) t = tt;
    }
    if (rgb[2] < 0.0f) {
        Vec3f r = _m.block<1, 3>(2, 0);
        float tt = -r.dot(c) / r.dot(d);
        if (tt > t) t = tt;
    }
    if (rgb[0] > 1.0f) {
        Vec3f r = _m.block<1, 3>(0, 0);
        float tt = (1.0f-r.dot(c)) / r.dot(d);
        if (tt > t) t = tt;
    }
    if (rgb[1] > 1.0f) {
        Vec3f r = _m.block<1, 3>(1, 0);
        float tt = (1.0f-r.dot(c)) / r.dot(d);
        if (tt > t) t = tt;
    }
    if (rgb[2] > 1.0f) {
        Vec3f r = _m.block<1, 3>(2, 0);
        float tt = (1.0f-r.dot(c)) / r.dot(d);
        if (tt > t) t = tt;
    }

    c = (1.0f-t)*c + t*d65;

    return _m * c;
}
