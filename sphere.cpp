#include "sphere.h"
#include <cmath>

Sphere::Sphere(Vec &center, Vec &surfColor, const Vec &emission, float &rad, const float &trans, const float &refl){
    midpoint = center;
    surfaceColor = surfColor;
    lightEmission = emission;
    radius = rad;
    radiusSquared = (rad*rad);
    transparency = trans;
    reflection = refl;
}

bool Sphere::rayGeometryIntersect(const Vec &originalRay, Vec &rayDirection, float &a, float &b){
    Vec diff = midpoint - originalRay;
    float t1 = diff.dotProduct(rayDirection);
    if( t1 < 0 ){return false;}
    float t2 = diff.dotProduct(diff) - (t1*t1);
    if( t2 > radiusSquared ){return false;}
    float t3 = sqrt(radiusSquared = t2);
    a = t1 - t3;
    b = t1 + t3;
    return true;
}