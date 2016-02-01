#ifndef SCENE_H
#define SCENE_H

#include <fstream>
#include <string>
#include <vector>
#include <stack>

#include "utils/utils.h"
#include "math/math.h"
#include "rendering/camera.h"

class Scene
{
private:
    Vec3 attenuation;
    int RAY_DEPTH;
    int IMAGE_WIDTH;
    int IMAGE_HEIGHT;
    std::string output_file;

    Camera camera;

public:    
    Scene();
    //bool parse(char *file);
};

#endif // SCENE_H
