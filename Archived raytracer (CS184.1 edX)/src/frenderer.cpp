#include "frenderer.h"

void FRenderer::setScene(FRay::Scene* scene) {
    this->imageWidth = scene->IMAGE_WIDTH;
    this->imageHeight = scene->IMAGE_HEIGHT;
    this->outputFile = scene->outputFile;
    this->maxRayDepth = scene->MAX_RAY_DEPTH;
    this->scene = scene;
}

void FRenderer::workerFunction(std::queue<FRay::Ray>& rays, Vector3**& pixels)
{

    while (!rays.empty())
    {
        queueLock.lock();
        FRay::Ray ray = rays.front();
        rays.pop();
        queueLock.unlock();

        FRay::Intersection intersect = traceRay(ray);

        if (intersect.exists)
        {
            Vector3 color = shade(intersect, 0);

            pixelsLock.lock();
            pixels[ray.i][ray.j] = color;
            pixelsLock.unlock();
        }
        counterLock.lock();
        pixelsDone++;
        if (pixelsDone % pixelsPerCent == 0)
            std::cout << ++percentDone << "% DONE." << std::endl;
        counterLock.unlock();
    }
}

void FRenderer::render() {
    Vector3** pixels = new Vector3*[(int)imageHeight];
    for(int i = 0; i < imageHeight; ++i)
        pixels[i] = new Vector3[(int)imageWidth];

    std::queue<FRay::Ray> rays;

    for (int i=0; i<imageHeight; i++)
        for (int j=0; j<imageWidth; j++)
        {
            Vector3 origin(scene->camera.lookFrom);

            float a = (j-0.5)-(imageWidth/2);
            float b = (imageHeight/2) - (i-0.5);

            Vector3 u_component = scene->camera.u * (scene->camera.tan_half_fovx * (a/(imageWidth/2)));
            Vector3 v_component = scene->camera.v * (scene->camera.tan_half_fovy * (b/(imageHeight/2)));

            Vector3 direction = -(-scene->camera.w + u_component + v_component);
            direction.normalize();

            FRay::Ray ray(origin, direction);
            ray.i = i;
            ray.j = j;

            rays.push(ray);
        }
    int MAX_THREADS = 4;
    int pixelsOverall = imageHeight*imageWidth;
    std::vector<std::thread*> threads;

    this->pixelsPerCent = (int)floor((float)pixelsOverall / 100);
    this->pixelsDone = 0;
    this->percentDone = 0;

    for (int i=0; i<MAX_THREADS; i++)
    {
        thread* t = new thread(&FRenderer::workerFunction, this, std::ref(rays), std::ref(pixels));
        threads.push_back(t);
    }

    for (int i=0; i<MAX_THREADS; i++)
        threads[i]->join();

    this->writeImage(pixels);
}

FRay::Intersection FRenderer::traceRay(const FRay::Ray& ray) {
    float mindist = std::numeric_limits<float>::infinity();
    FRay::Intersection closestIntersection(false);

    for (FRay::Object* obj : scene->objects)
    {
        FRay::Intersection intersection = obj->testIntersection(ray);
        if (intersection.exists)
        {
            float distance = (intersection.point - ray.origin).magnitude();

            if (distance < mindist)
            {
                mindist = distance;
                closestIntersection = intersection;
            }
        }
    }
    return closestIntersection;
}

Vector3 FRenderer::shade(FRay::Intersection& intersection, int currentRecursionDepth) {
    return intersection.normal;

    if (currentRecursionDepth == maxRayDepth)
        return Vector3(0, 0, 0);

    Vector3 ambientTerm = intersection.object->ambient;
    Vector3 emissiveTerm = intersection.object->emission;
    Vector3 diffuseTerm;
    Vector3 specularTerm;
    Vector3 reflectedTerm;

    for (FRay::Light* light : this->scene->lights)
    {
        Vector3 directionToLight;
        float distanceToLight;

        if (light->position.w() == 1) {
            directionToLight = light->position.xyz() - intersection.point;
            distanceToLight = directionToLight.magnitude();
        }
        else {
            directionToLight = light->position.xyz();
        }

        directionToLight.normalize();

        FRay::Ray shadowRay = biasedRay(intersection.point, directionToLight);

        FRay::Intersection shadowIntersection = traceRay(shadowRay);
        if (shadowIntersection.exists)
        {
            float shadowIntersectionDistance = (shadowIntersection.point - intersection.point).magnitude();
            if (shadowIntersectionDistance < EPSILON)
                continue;

            if (light->position.w() == 1)
            {
                if (shadowIntersectionDistance < distanceToLight)
                    continue;
            }
        }
        //if (!shadowIntersection.exists)
        //{
            float lightDirDotNorm = directionToLight.dot(intersection.normal);
            float diffuseCoeff = max(lightDirDotNorm, 0.0f);
            Vector3 lightIntensity = (light->position.w() == 1) ? attenuated(light->color, distanceToLight) : light->color;
            Vector3 diffuseColor = intersection.object->diffuse;
            Vector3 specularColor = intersection.object->specular;
            float shininess = intersection.object->shininess;
            Vector3 halfVec = (directionToLight - intersection.ray.direction).normalized();
            float halfVecDotNorm = halfVec.dot(intersection.normal);
            float specularCoeff = pow(max(halfVecDotNorm, 0.0f), shininess);

            diffuseTerm = diffuseTerm + (diffuseColor * lightIntensity * diffuseCoeff);
            specularTerm = specularTerm + (specularColor * lightIntensity * specularCoeff);
       // }
    }

    Vector3 reflectedRayDir = computeReflectedDirection(intersection.ray.direction, intersection.normal);
    FRay::Ray reflectedRay = biasedRay(intersection.point, reflectedRayDir);
    FRay::Intersection reflectIntersection = traceRay(reflectedRay);
    if (reflectIntersection.exists)
        reflectedTerm = intersection.object->specular * shade(reflectIntersection, currentRecursionDepth+1);

    Vector3 finalColor = ambientTerm + emissiveTerm + diffuseTerm + specularTerm + reflectedTerm;

    return finalColor;
}

void FRenderer::writeImage(Vector3**& pixels)
{
    pngwriter png(this->imageWidth,this->imageHeight,0, outputFile.c_str());
    for (int i=0; i<imageHeight; i++)
        for (int j=0; j<imageWidth; j++)
            png.plot(j, i, pixels[i][j].x(), pixels[i][j].y(), pixels[i][j].z());
    png.close();
}
