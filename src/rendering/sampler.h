#ifndef SAMPLER_H
#define SAMPLER_H

#include "math/math.h"
#include <random>
#include <time.h>

namespace Sampling {
enum SamplingMethod {
    Stochastic,
    Uniform
};
}

class Sampler
{
public:
    Sample sample();
    Sampler(int width, int height, int nsamples, Sampling::SamplingMethod method);

private:
    int width, height, nsamples, cur_samples, cur_i, cur_j, grid_side;
    bool finished;
    Sampling::SamplingMethod method;
    void increment();
};
#endif // SAMPLER_H
