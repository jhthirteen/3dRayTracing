#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>

#include "vec.h"
#include "sphere.h"
using namespace std;

#define PI 3.141592653589793
#define INF 1e8

float mix(const float &a, const float &b, const float &mix){
    return (b*mix) + (a*(1-mix));
}

Vec trace(const Vec &originalRay, Vec &rayDirection, vector<Sphere> &spheres, const int &currentDepth){
    float near = INF;
    Sphere* currentSphere = nullptr;
    //check if an intersection w/ the sphere (determined on ray direction) exists
    for( int i = 0; i < spheres.size(); i++ ){
        float t1 = INF;
        float t2 = INF;
        if( spheres.at(i).rayGeometryIntersect(originalRay, rayDirection, t1, t2)){
            if( t1 < 0 ){t1 = t2;}
            if( t1 < near ){
                near = t1;
                currentSphere = &spheres.at(i);
            }
        }
    }

    if( currentSphere == nullptr ){return Vec(2);} //no intersection was found

    Vec surfaceColor = 0;
    Vec intersectionLocation = originalRay + (rayDirection*near); //calculating the intersection
    Vec normalAtIntersection = intersectionLocation - currentSphere->midpoint; //calculating the normal at the intersection
    normalAtIntersection.norm();

    float bias = 1e-4; //bias necessary via scratchapixel-code walkthrough
    bool inSphere = false; //we need to determine if we are "inside the sphere" --> when the normal and dir are the same
    if( rayDirection.dotProduct(normalAtIntersection) > 0){ //normal and dir same --> positive dot product
        normalAtIntersection = -normalAtIntersection;
        inSphere = true;
    }
    if((currentSphere->transparency > 0 || currentSphere->reflection > 0) && currentDepth < 5){ //5 serves as a limit to the number of recursive calls we make 
        float r = -(rayDirection.dotProduct(normalAtIntersection));
        float fresnelNum = mix(pow(1-r, 3), 1, 0.1); 
        Vec reflectionDirection = (rayDirection-normalAtIntersection)*2*(rayDirection.dotProduct(normalAtIntersection)); //computing direction of our reflection
        reflectionDirection.norm();
        Vec reflection = trace((intersectionLocation+(normalAtIntersection*bias)), reflectionDirection, spheres, currentDepth+1);
        Vec refraction = 0;
        if( currentSphere->transparency ){
            
        }
    }
}