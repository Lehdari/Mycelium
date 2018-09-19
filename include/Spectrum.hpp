//
// Created by Lehdari on 19.9.2018.
//
// This file specifies Spectrum class, which contains functionality for
// handling spectra of (visible) light.
//

#ifndef MYCELIUM_SPECTRUM_HPP
#define MYCELIUM_SPECTRUM_HPP


#include "TypeUtils.hpp"


namespace mm {

    class Spectrum {
    public:

        /// Struct for setting up Spectrum
        struct Settings {
            float minLambda;    /// minimum wavelength
            float maxLambda;    /// maximum wavelength
            float dLambda;      /// resolution

            Settings(
                float minLambda = 375.0f,
                float maxLambda = 765.0f,
                float dLambda = 10.0f) :
                minLambda   (minLambda),
                maxLambda   (maxLambda),
                dLambda     (dLambda)
            {}
        };

        Spectrum(const Settings& settings = Settings());

        /// Add light to the spectrum
        /// lambda: wavelength
        /// intensity: intensity
        /// In case wavelength is outside of the spectrum specifications
        /// nothing happens
        void addLight(float lambda, float intensity);

        /// Sample the spectrum on specific wavelength
        /// return: interpolated intensity on requested wavelength
        float sample(float lambda) const;

        /// Get const reference to underlying vector
        /// return: const reference to vector of stored spectrum
        const Vector<float>& getVector() const;

    private:
        Settings        _settings;
        int64_t         _nBins; // number of bins in the spectrum
        float           _lScale; // scaling factor for adding light

        Vector<float>   _spectrum;
    };

}


#endif // MYCELIUM_SPECTRUM_HPP
