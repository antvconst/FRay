#include "sampler.h"

Sampler::Sampler(int width, int height, int nsamples, Sampling::SamplingMethod method) :
    width(width-1), height(height-1), method(method) {
    cur_samples = 0;
    cur_i = 0;
    cur_j = 0;
    finished = false;

    if (method == Sampling::Stochastic)
        srand(time(NULL));
    grid_side = (int)round(sqrt(nsamples));
    this->nsamples = grid_side*grid_side;
}

void Sampler::increment() {
    cur_samples += 1;

    if (cur_samples == nsamples) {
        cur_samples = 0;

        if (cur_j == width) {
            if (cur_i == height)
                finished = true;
            else {
                cur_i += 1;
                cur_j = 0;
            }
        }
        else
            cur_j += 1;
    }
}

Sample Sampler::sample() {
    if (this->finished)
        return Vec2(-1.0, 0);

    double r1, r2;

    if (method == Sampling::Stochastic) {
        r1 = rand()/(double)RAND_MAX;
        r2 = rand()/(double)RAND_MAX;
    }
    else {
        r1 = 0.5;
        r2 = 0.5;
    }

    // subpixel coordinates
    int spx_i = cur_samples / grid_side;
    int spx_j = cur_samples % grid_side;

    double i = (double)cur_i + (spx_i+r1)/grid_side;
    double j = (double)cur_j + (spx_j+r2)/grid_side;

    this->increment();

    return Sample(i, j);
}
