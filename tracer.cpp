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

float mix(const float &a, const float &b, const float &mix){
    return b * mix + a * (1 - mix);
}

Vec trace(const Vec &originalRay, Vec &rayDirection, vector<Sphere> &spheres, const int &currentDepth){
    float near = INFINITY;
    Sphere* currentSphere = nullptr;
    //check if an intersection w/ the sphere (determined on ray direction) exists
    for( int i = 0; i < spheres.size(); i++ ){
        float t1 = INFINITY;
        float t2 = INFINITY;
        if( spheres.at(i).rayGeometryIntersect(originalRay, rayDirection, t1, t2) ){
            if( t1 < 0 ){t1 = t2;}
            if( t1 < near ){
                near = t1;
                currentSphere = &spheres.at(i);
            }
        }
    }

    if( !currentSphere ){return Vec(2);} //no intersection was found
    cout << "intersection found" << endl;
    Vec surfaceColor = 0;
    Vec intersectionLocation = originalRay + rayDirection * near; //calculating the intersection
    Vec normalAtIntersection = intersectionLocation - currentSphere->midpoint; //calculating the normal at the intersection
    normalAtIntersection.norm();

    float bias = 1e-4; //bias necessary via scratchapixel-code walkthrough
    bool inSphere = false; //we need to determine if we are "inside the sphere" --> when the normal and dir are the same
    if( rayDirection.dotProduct(normalAtIntersection) > 0){ //normal and dir same --> positive dot product
        normalAtIntersection = -normalAtIntersection;
        inSphere = true;
    }
    if((currentSphere->transparency > 0 || currentSphere->reflection > 0) && currentDepth < 5){ //5 serves as a limit to the number of recursive calls we make 
        float r = -rayDirection.dotProduct(normalAtIntersection);
        float fresnelNum = mix(pow(1-r, 3), 1, 0.1); 
        Vec reflectionDirection = rayDirection - normalAtIntersection * 2 * rayDirection.dotProduct(normalAtIntersection); //computing direction of our reflection
        reflectionDirection.norm();
        Vec reflection = trace(intersectionLocation + normalAtIntersection * bias, reflectionDirection, spheres, currentDepth + 1);
        Vec refraction = 0;
        if( currentSphere->transparency ){ //computations needed to generate the refraction ray
            float i = 1.1;
            float theta = 0;
            if( inSphere == true ){theta = i;}
            else{theta = 1/i;}
            float cos = -normalAtIntersection.dotProduct(rayDirection);
            float j = 1- theta * theta * (1 - cos * cos);
            Vec refractionDirection = rayDirection * theta + normalAtIntersection * (theta * cos-sqrt(j));
            refractionDirection.norm();
            refraction = trace(intersectionLocation - normalAtIntersection * bias, refractionDirection, spheres, currentDepth + 1);
        }
        // now can compute the surface's color w/ reflection and refraction
        surfaceColor = reflection * fresnelNum + refraction * (1-fresnelNum) * currentSphere->transparency * currentSphere->surfaceColor;
    }
    else{
        for( int i = 0; i < spheres.size(); i++ ){
            if( spheres.at(i).lightEmission.x > 0 ){
                Vec transmission = 1;
                Vec lightDirection = spheres.at(i).midpoint - intersectionLocation;
                lightDirection.norm();
                for( int j = 0; j < spheres.size(); j++ ){
                    if( i != j ){
                        float t0;
                        float t1;
                        if( spheres.at(j).rayGeometryIntersect(intersectionLocation + normalAtIntersection * bias, lightDirection, t0, t1)){
                            transmission = 0;
                            break;
                        }
                    }
                }
                surfaceColor += currentSphere->surfaceColor * transmission * max(float(0), normalAtIntersection.dotProduct(lightDirection)) * spheres.at(i).lightEmission;
            }
        }
    }
    return surfaceColor + currentSphere->lightEmission;
}

void render(vector<Sphere> &spheres){
    //initialize scene
    int width = 640;
    int height = 480;
    Vec *image = new Vec[width*height]; //dynamically allocate memory for an array of Vec objects for the entire screen
    Vec *pixel = image; //pointer to the first pixel "head of this array"
    float iWidth = 1 / float(width);
    float iHeight = 1 / float(height);
    float fieldOfView = 30;
    float aspectRatio = width / float(height);
    float angle = tan(M_PI * 0.5 * fieldOfView / 180);
    //begin the ray tracing process
    for( int y = 0; y < height; y++ ){
        for( int x = 0; x < width; x++, pixel++ ){
            float x2 = (2 * ((x+0.5) * iWidth) - 1) * angle * aspectRatio;
            float y2 = (1 - 2 * ((y + 0.5) * iHeight)) * angle;
            Vec rayDirection(x2, y2, -1);
            rayDirection.norm();
            *pixel = trace(Vec(0), rayDirection, spheres, 0);
        }
    }

    ofstream ofs("./untitled.ppm"); //rendering the image to output file -> untitled.ppm
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for( int i = 0; i < width*height; i++ ){
        ofs << (unsigned char)(min(float(1), image[i].x)*255) << (unsigned char)(min(float(1), image[i].y)*255) << (unsigned char)(min(float(1), image[i].z)*255);
    }
    ofs.close();
    delete[] image;
}

int main(int argc, char **argv){
    srand48(13); 
    vector<Sphere> spheres;
    // spheres we want to generate:
    spheres.push_back(Sphere(Vec( 0.0, -10004, -20), 10000, Vec(0.20, 0.20, 0.20), 0, 0.0));
    spheres.push_back(Sphere(Vec( 0.0,      0, -20),     4, Vec(1.00, 0.32, 0.36), 1, 0.5));
    spheres.push_back(Sphere(Vec( 5.0,     -1, -15),     2, Vec(0.90, 0.76, 0.46), 1, 0.0));
    spheres.push_back(Sphere(Vec( 5.0,      0, -25),     3, Vec(0.65, 0.77, 0.97), 1, 0.0));
    spheres.push_back(Sphere(Vec(-5.5,      0, -15),     3, Vec(0.90, 0.90, 0.90), 1, 0.0));
    // adding a light source:
    spheres.push_back(Sphere(Vec( 0.0,     20, -30),     3, Vec(0.00, 0.00, 0.00), 0, 0.0, Vec(3)));
    render(spheres);
}