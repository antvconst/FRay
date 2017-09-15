#ifndef FRENDERER_H
#define FRENDERER_H

#include "fray.h"
#include "fmath.h"
#include <string>
#include <limits>
#include <thread>
#include <mutex>
#include <queue>
#include "pngwriter.h"

class FRenderer
{
public:
    void setScene(FRay::Scene* scene);
    void render();
    void writeImage(Vector3**& pixels);
    float imageHeight;
    float imageWidth;
    int maxRayDepth;
    FRay::Scene* scene;
    const float EPSILON = 0.001;
    std::mutex pixelsLock;
    std::mutex queueLock;
    std::mutex counterLock;
    std::mutex coutLock;
    int pixelsDone;
    int percentDone;
    int pixelsPerCent;

    std::string outputFile;
    FRenderer() {}
    FRay::Intersection traceRay(const FRay::Ray& ray);
    Vector3 shade(FRay::Intersection& intersection, int currentRecursionDepth);
    void workerFunction(std::queue<FRay::Ray>& rays, Vector3**& pixels);
    inline Vector3 attenuated(Vector3 color, float distance)
    {
        return Vector3(color/(this->scene->attenuation.x() +
                                this->scene->attenuation.y() * distance +
                                this->scene->attenuation.z() * distance * distance));
    }
    inline FRay::Ray biasedRay(Vector3& origin, Vector3& direction)
    {
        return FRay::Ray((origin + (direction * EPSILON)), direction);
    }
};

#endif // FRENDERER_H
