#ifndef FTRANSFORMS_H
#define FTRANSFORMS_H

#include "fmath.h"
#include <vector>
#include <fstream>
#include <stack>

namespace FRay
{

class Ray;
class Intersection;
class Camera;
class Object;
class Sphere;
class Triangle;
class Light;
class Scene;

class Ray
{
public:
    Ray() {}
    Ray(const Vector3& origin, const Vector3& direction);
    Vector3 origin;
    Vector3 direction;
    int i=0;
    int j=0;
};

class Intersection
{
public:
    bool exists;
    Vector3 point;
    Vector3 normal;
    const Object* object;
    Ray ray;

    Intersection(bool exists); // doesn't exist
    Intersection(bool exists, const Vector3& point, const Vector3& normal, const Object* object, const Ray& ray);
};

class Camera
{
public:
    Vector3 lookFrom;
    Vector3 lookAt;
    Vector3 up;
    float fovy;
    float fovx;
    float tan_half_fovy;
    float tan_half_fovx;
    Vector3 w;
    Vector3 v;
    Vector3 u;

    Camera() {}
    Camera(const FRay::Scene& scene, const Vector3& lookFrom, const Vector3& lookAt, const Vector3& up, float fovy);
};

class Object
{
public:
    Object() {}
    virtual FRay::Intersection testIntersection(const Ray& ray) {}
    Vector3 ambient;
    Vector3 diffuse;
    Vector3 specular;
    float shininess;
    Vector3 emission;
    Matrix4 transform;
    int objId;
};

class Sphere : public Object
{
public:
    Sphere(Vector3 location, float radius);
    Vector3 location;
    FRay::Intersection testIntersection(const Ray& ray);
    float radius;
};

class Triangle : public Object
{
public:
    Triangle(Vector4* vert1, Vector4* vert2, Vector4* vert3);
    Vector4 vert1;
    Vector4 vert2;
    Vector4 vert3;
    Vector3 normal;
    Vector3 unnormal;
    bool transformPerformed;
    FRay::Intersection testIntersection(const Ray& ray);
};

class Light
{
public:
    Vector4 position; // w indicates if it's directional or point light
    Vector3 color;
};

class Scene
{
private:
    bool parseScene(char* filePath);

public:
    // rendering settings
    float IMAGE_HEIGHT;
    float IMAGE_WIDTH;
    int MAX_RAY_DEPTH;
    std::string outputFile;

    Scene(char* filePath);
    FRay::Camera camera;
    Vector3 attenuation;
    std::vector<Object*> objects;
    std::vector<Light*> lights;
    std::vector<Vector4*> vertices;
};

inline std::vector<std::string> splitString(const std::string &str, const std::string &delim = " ")
{
    std::vector<std::string> tokens;
    if (str.size() > 0)
    {
        if (delim.size() > 0)
        {
            std::string::size_type currPos = 0, prevPos = 0;
            while ((currPos = str.find(delim, prevPos)) != std::string::npos)
            {
                std::string item = str.substr(prevPos, currPos - prevPos);
                if (item.size() > 0)
                {
                    tokens.push_back(item);
                }
                prevPos = currPos + 1;
            }
            tokens.push_back(str.substr(prevPos));
        }
        else
        {
            tokens.push_back(str);
        }
    }
    return tokens;
}
}

#endif // FTRANSFORMS_H
