#include "sampler.h"

Sampler::Sampler(int width, int height, int nsamples) :
    width(width-1), height(height-1), nsamples(nsamples) {
    this->cur_samples = 0;
    this->cur_i = 0;
    this->cur_j = 0;
    this->finished = false;
    srand(time(NULL));
}

Vec2 Sampler::sample() {
    if (finished)
        return Vec2(-1.0, 0);

    // making some random shifts for anti-aliasing
    double sh_i = (rand()/(double)RAND_MAX);
    double sh_j = (rand()/(double)RAND_MAX);

    // pivoting around the center of the pixel
    if (sh_i > 0.5)
        sh_i = 0.5 -  sh_i;

    if (sh_j > 0.5)
        sh_j = 0.5 - sh_j;

    Vec2 s((double)cur_i + 0.5 + sh_i, (double)cur_j + 0.5 + sh_j);
    cur_samples += 1;

    if (cur_samples == nsamples) {
        cur_samples = 0;

        if (cur_j == width) {
            if (cur_i == height) {
                finished = true;
            }
            else {
                cur_i += 1;
                cur_j = 0;
            }
        }
        else
            cur_j += 1;
    }

    return s;
}
