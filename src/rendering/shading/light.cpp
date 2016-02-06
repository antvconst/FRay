#include "light.h"

Light::Light(const Vec3 position, const Color& color) :
    position(position), color(color) {}



PointLight::PointLight(const Vec3& position, const Color& color, const Vec3& attenuation) :
    Light(position, color) {
    attenuation_const = attenuation.el(0);
    attenuation_linear = attenuation.el(0);
    attenuation_quadratic = attenuation.el(0);
}

double PointLight::intensity(double distance) {
    return 1/(attenuation_const +
              distance*attenuation_linear +
              distance*distance*attenuation_quadratic);
}


DirectionalLight::Light(const Vec3& position, const Color& color) :
    Light(position, color) {}

double DirectionalLight::intensity(double distance) {
    return 1.0;
}
