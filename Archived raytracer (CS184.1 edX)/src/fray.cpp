#include "fray.h"

FRay::Scene::Scene(char* filePath) {
    this->parseScene(filePath);
}

bool FRay::Scene::parseScene(char* filePath) {
    std::ifstream sceneFile(filePath);
    if (!sceneFile.is_open())
    {
        std::cout << "Could not open scene file. Aborting." << std::endl;
        return false;
    }

    std::string current_line;

    std::stack<Matrix4> transformStack;
    this->attenuation = Vector3(1, 0, 0);
    this->MAX_RAY_DEPTH = 5;
    Vector3 ambient(0.2, 0.2, 0.2);
    Vector3 diffuse;
    Vector3 specular;
    float shininess;
    Vector3 emission;
    int objId = 0;

    transformStack.push(Matrix4::identity());

    while (!sceneFile.eof())
    {
        getline(sceneFile, current_line);
        auto tokens = splitString(current_line);

        if (tokens.empty())
            continue;

        // GENERAL
        if (tokens[0] == "size") {
            this->IMAGE_WIDTH = std::stof(tokens[1]);
            this->IMAGE_HEIGHT = std::stof(tokens[2]);
        }
        else if (tokens[0] == "maxdepth") {
            this->MAX_RAY_DEPTH = std::stoi(tokens[1]);
        }
        else if (tokens[0] == "output") {
            this->outputFile = tokens[1];
        }
        else if (tokens[0] == "camera") {
            Vector3 lookFrom;
            Vector3 lookAt;
            Vector3 up;
            float fovy;

            lookFrom.x() = std::stof(tokens[1]);
            lookFrom.y() = std::stof(tokens[2]);
            lookFrom.z() = std::stof(tokens[3]);

            lookAt.x() = std::stof(tokens[4]);
            lookAt.y() = std::stof(tokens[5]);
            lookAt.z() = std::stof(tokens[6]);

            up.x() = std::stof(tokens[7]);
            up.y() = std::stof(tokens[8]);
            up.z() = std::stof(tokens[9]);

            fovy = std::stof(tokens[10]);

            this->camera = FRay::Camera(*this, lookFrom, lookAt, up, fovy);
        }

        // OBJECTS
        else if (tokens[0] == "sphere") {
            Vector3 position;
            position.x() = std::stof(tokens[1]);
            position.y() = std::stof(tokens[2]);
            position.z() = std::stof(tokens[3]);

            float radius = std::stof(tokens[4]);

            auto sphere = new Sphere(position, radius);
            sphere->ambient = ambient;
            sphere->diffuse = diffuse;
            sphere->emission = emission;
            sphere->shininess = shininess;
            sphere->specular = specular;
            sphere->transform = transformStack.top();
            sphere->objId = objId++;

            this->objects.push_back(sphere);
        }
        else if (tokens[0] == "vertex") {
            Vector4* vertex = new Vector4();
            vertex->x() = std::stof(tokens[1]);
            vertex->y() = std::stof(tokens[2]);
            vertex->z() = std::stof(tokens[3]);
            vertex->w() = 1;

            this->vertices.push_back(vertex);
        }
        else if (tokens[0] == "tri") {
            int idx1 = std::stoi(tokens[1]);
            int idx2 = std::stoi(tokens[2]);
            int idx3 = std::stoi(tokens[3]);

            Triangle* tri = new Triangle(this->vertices[idx1],
                         this->vertices[idx2],
                         this->vertices[idx3]);

            tri->ambient = ambient;
            tri->diffuse = diffuse;
            tri->emission = emission;
            tri->shininess = shininess;
            tri->specular = specular;
            tri->objId = objId++;

            tri->transform = transformStack.top();
            this->objects.push_back(tri);
        }


        // TRANSFORMS
        else if (tokens[0] == "translate") {
            Matrix4 &T = transformStack.top();
            T = T * translation(std::stof(tokens[1]),
                    std::stof(tokens[2]),
                    std::stof(tokens[3]));
        }
        else if (tokens[0] == "rotate") {
            Vector3 axis(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
            Matrix4 R = rotation(std::stof(tokens[4]), axis);

            Matrix4 &T = transformStack.top();
            T = R * T;
        }
        else if (tokens[0] == "scale") {
            Matrix4 &T = transformStack.top();
            T = T * scale(std::stof(tokens[1]),
                    std::stof(tokens[2]),
                    std::stof(tokens[3]));
        }
        else if (tokens[0] == "pushTransform") {
            transformStack.push(transformStack.top());
        }
        else if (tokens[0] == "popTransform") {
            transformStack.pop();
        }

        // LIGHTS
        else if (tokens[0] == "directional") {
            Light* light = new Light(); // SHOULD I APPLY TRANSFORMS TO LIGHT OR NOT?
            light->position = Vector4(std::stof(tokens[1]),
                    std::stof(tokens[2]),
                    std::stof(tokens[3]),
                    0);
            light->color = Vector3(std::stof(tokens[4]),
                    std::stof(tokens[5]),
                    std::stof(tokens[6]));

            this->lights.push_back(light);
        }
        else if (tokens[0] == "point") {
            Light* light = new Light();
            light->position = Vector4(std::stof(tokens[1]),
                    std::stof(tokens[2]),
                    std::stof(tokens[3]),
                    1);
            light->color = Vector3(std::stof(tokens[4]),
                    std::stof(tokens[5]),
                    std::stof(tokens[6]));

            this->lights.push_back(light);
        }
        else if (tokens[0] == "attenuation") {
            this->attenuation = Vector3(std::stof(tokens[1]),
                    std::stof(tokens[2]),
                    std::stof(tokens[3]));
        }
        else if (tokens[0] == "ambient") {
            ambient = Vector3(std::stof(tokens[1]),
                    std::stof(tokens[2]),
                    std::stof(tokens[3]));
        }

        // MATERIALS
        else if (tokens[0] == "diffuse") {
            diffuse = Vector3(std::stof(tokens[1]),
                    std::stof(tokens[2]),
                    std::stof(tokens[3]));
        }
        else if (tokens[0] == "specular") {
            specular = Vector3(std::stof(tokens[1]),
                    std::stof(tokens[2]),
                    std::stof(tokens[3]));
        }
        else if (tokens[0] == "shininess") {
            shininess = std::stof(tokens[1]);
        }
        else if (tokens[0] == "emission") {
            emission = Vector3(std::stof(tokens[1]),
                    std::stof(tokens[2]),
                    std::stof(tokens[3]));
        }
        else {
            continue;
        }
    }

    return true;
}

FRay::Camera::Camera(const FRay::Scene& scene, const Vector3& lookFrom, const Vector3& lookAt, const Vector3& up, float fovy) {
    this->lookFrom = lookFrom;
    this->lookAt = lookAt;
    this->up = up;
    this->fovy = fovy * PI/180;

    this->tan_half_fovy = tan(this->fovy/2);
    this->tan_half_fovx = this->tan_half_fovy * (scene.IMAGE_WIDTH/scene.IMAGE_HEIGHT);

    this->w = (lookAt-lookFrom).normalized();
    this->u = up.cross(w).normalized();
    this->v = w.cross(u);
}


FRay::Sphere::Sphere(Vector3 location, float radius)
{
    this->location = location;
    this->radius = radius;
}

FRay::Intersection FRay::Sphere::testIntersection(const Ray& ray) {
    Matrix4 inv = this->transform.inverse();
    Vector3 ray_dir = (inv * Vector4(ray.direction, 0)).xyz();
    Vector3 ray_origin = (inv * Vector4(ray.origin, 1)).xyz();

    Vector3 originMinusCenter = ray_origin - this->location;

    float a = ray_dir.dot(ray_dir);
    float b = 2 * ray_dir.dot(originMinusCenter);
    float c = originMinusCenter.dot(originMinusCenter) - (this->radius * this->radius);

    float discrim = b*b - 4*a*c;

    if (discrim >= 0)
    {
        float root1 = (-b + sqrt(discrim)) / (2*a);
        float root2 = (-b - sqrt(discrim)) / (2*a);
        float t;

        if (root1 > 0 && root2 > 0)
            t = std::min(root1, root2);

        else if ((root1 > 0 && root2 < 0) || (root2 > 0 && root2 < 0))
            t = std::max(root1, root2);

        else if (root1 < 0 && root2 < 0)
            return Intersection(false);

        Vector3 point = ray_origin + (ray_dir * t);
        Vector3 normal = (point - this->location).normalized();
        point = (this->transform * Vector4(point, 1)).xyz();
        normal = inv.submatrix().transposed() * normal;
        normal.normalize();

        return Intersection(true, point, normal, this, ray);
    }
    else
    {
        return Intersection(false);
    }
}


FRay::Triangle::Triangle(Vector4* vert1, Vector4* vert2, Vector4* vert3)
{
    this->vert1 = *vert1;
    this->vert2 = *vert2;
    this->vert3 = *vert3;

    transformPerformed = false;
}

FRay::Intersection FRay::Triangle::testIntersection(const FRay::Ray& ray) {
    if (!transformPerformed)
    {
        this->vert1 = transform * vert1;
        this->vert2 = transform * vert2;
        this->vert3 = transform * vert3;

        Vector3 side1 = (this->vert2 - this->vert3).xyz();
        Vector3 side2 = (this->vert1 - this->vert3).xyz();

        this->unnormal = side1.cross(side2);
        this->normal = this->unnormal.normalized();

        this->transformPerformed = true;
    }

    //Matrix4 inv = this->transform.inverse();
    Vector3 ray_dir = ray.direction;//(inv * Vector4(ray.direction, 0)).xyz();
    Vector3 ray_origin = ray.origin;//(inv * Vector4(ray.origin, 1)).xyz();

    float rayDotNorm = ray_dir.dot(normal);
    if  (rayDotNorm == 0)
       return Intersection(false);
    else
    {
        float root = (this->vert1.xyz() - ray_origin).dot(normal) / rayDotNorm;

        if (root < 0)
            return Intersection(false);

        Vector3 point = ray_origin + (ray_dir * root);

        Vector3 AP = point - this->vert3.xyz();
        Vector3 AB = (this->vert2 - this->vert3).xyz();
        Vector3 ABxAP = AB.cross(AP);
        float v_num = this->unnormal.dot(ABxAP);
        if (v_num < 0)
            return Intersection(false);

        Vector3 BP = point - this->vert2.xyz();
        Vector3 BC = (this->vert1 - this->vert2).xyz();
        Vector3 BCxBP = BC.cross(BP);

        if (this->unnormal.dot(BCxBP) < 0)
            return Intersection(false);

        Vector3 CP = point - this->vert1.xyz();
        Vector3 CA = (this->vert3 - this->vert1).xyz();
        Vector3 CAxCP = CA.cross(CP);

        float u_num = this->unnormal.dot(CAxCP);

        if (u_num < 0)
            return Intersection(false);

        float denom = this->unnormal.dot(this->unnormal);
        float u = u_num / denom;
        float v = v_num / denom;
        float w = 1 - u - v;

        //point = (this->transform * Vector4(point, 1)).xyz();
        Vector3 norm = this->normal;//(inv.submatrix().transposed() * this->normal);
        return Intersection(true, point, -norm, this, ray);
    }
}

FRay::Ray::Ray(const Vector3& origin, const Vector3& direction) {
    this->origin = origin;
    this->direction = direction;
}


FRay::Intersection::Intersection(bool exists) {
    this->exists = exists;
}

FRay::Intersection::Intersection(bool exists, const Vector3& point, const Vector3& normal, const Object* object, const Ray& ray) {
    this->exists = exists;
    this->point = point;
    this->normal = normal;
    this->object = object;
    this->ray = ray;
}
