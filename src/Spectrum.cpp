//
// Created by Lehdari on 20.9.2018.
//

#include "Spectrum.hpp"


using namespace mm;


Spectrum::Spectrum(const Spectrum::Settings& settings) :
    _settings   (settings),
    _nBins      ((int64_t)((_settings.maxLambda - _settings.minLambda) / _settings.dLambda) + 1),
    _lScale     (1.0f / _settings.dLambda),
    _spectrum   (_nBins, 0.0f)
{
}

void Spectrum::addLight(float lambda, float intensity)
{
    auto binId = (int64_t)((lambda - _settings.minLambda) * _lScale);

    if (binId < 0 || binId >= _nBins)
        return;

    _spectrum[binId] += intensity;
}

float Spectrum::sample(float lambda) const
{
    // sample with linear interpolation
    float lambda2 = lambda - _settings.minLambda;
    auto binId = (int64_t)(lambda2 * _lScale);

    if (binId < 0 || binId >= _nBins)
        return 0.0f;

    auto binId2 = binId+1;
    if (binId2 >= _nBins) binId2 = _nBins-1;

    float t = (lambda2 - binId * _settings.dLambda) * _lScale;
    float a = _spectrum[binId];
    float b = _spectrum[binId2];

    return a + t * (b - a);
}

const Vector<float>& Spectrum::getVector() const
{
    return _spectrum;
}
