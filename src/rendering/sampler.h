#ifndef SAMPLER_H
#define SAMPLER_H

#include "math/math.h"
#include <random>
#include <time.h>

class Sampler
{
private:
    int width, height, nsamples, cur_samples, cur_i, cur_j;
    bool finished;

public:
    Sample sample();
    Sampler(int width, int height, int nsamples);
};

#endif // SAMPLER_H
