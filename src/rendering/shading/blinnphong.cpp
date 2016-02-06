#include "blinnphong.h"

BlinnPhong::BlinnPhong() {}

Color BlinnPhong::shade(const Vec3& v, const Vec3& n, const Vec3& l, Color light_color) {
    Vec3 h = (v+l)*1/sqrt(2);
    double diffuse_intensity = std::max(0.0, dot(n, l));
    double specular_intensity = pow(std::max(0.0, dot(n, h)), shininess);

    return emissive + (diffuse*diffuse_intensity + specular*specular_intensity)*light_color;
}
