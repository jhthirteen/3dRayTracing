#ifndef SPHERE_H
#define SPHERE_H
#include "vec.h"

class Sphere{
    public:
        Vec midpoint;
        Vec surfaceColor;
        Vec lightEmission;
        float radius;
        float radiusSquared;
        float transparency;
        float reflection;

        Sphere(Vec &center, Vec &surfColor, const Vec &emission = 0, float &rad, const float &trans = 0, const float &refl = 0);

        bool rayGeometryIntersect(const Vec &originalRay, Vec &rayDirection, float &a, float &b);
};
#endif