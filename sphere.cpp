#include "sphere.h"
#include <cmath>

Sphere::Sphere(const Vec &center, const float &r, const Vec &surfColor, const float &refl, const float &transp, const Vec &emission){
    midpoint = center;
    radius = r;
    radiusSquared = r * r;
    surfaceColor = surfColor;
    lightEmission = emission;
    transparency = transp;
    reflection = refl;
}

bool Sphere::rayGeometryIntersect(const Vec &originalRay, const Vec &rayDirection, float &a, float &b) const{
    Vec diff = midpoint - originalRay;
    float t1 = diff.dotProduct(rayDirection);
    if( t1 < 0 ){return false;}
    float t2 = diff.dotProduct(diff) - t1 * t1;
    if( t2 > radiusSquared ){return false;}
    float t3 = sqrt(radiusSquared - t2);
    a = t1 - t3;
    b = t1 + t3;
    return true;
}