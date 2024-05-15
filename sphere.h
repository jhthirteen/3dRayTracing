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

        Sphere(const Vec &center, const float &r, const Vec &surfColor, const float &refl = 0, const float &transp = 0, const Vec &emission = 0);

        bool rayGeometryIntersect(const Vec &originalRay, const Vec &rayDirection, float &a, float &b) const;
};
#endif