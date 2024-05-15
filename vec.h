#ifndef VEC_H
#define VEC_H

#include <fstream>
#include <iostream>
using namespace std;

class Vec{
    public:
        float x;
        float y;
        float z;

        Vec();
        Vec(float xV);
        Vec(float xV, float yV, float zV);

        Vec& norm();
        Vec operator*(const float &f); //defines scalar multiplication -> f acts as a scalar
        Vec operator*(const Vec &v); //defines vector multiplication -> v acts as a vector
        float dotProduct(const Vec &v); //defines our inner product for two vectors
        Vec operator-(const Vec &v); //defines vector subtraction 
        Vec operator+(const Vec &v); //defines vector addition
        Vec& operator+=(const Vec &v);
        Vec& operator*=(const Vec &v);
        Vec operator-(); //defines negating a vector 
        float length();
        float lengthSquared();
        friend ostream& operator<<(ostream &os, Vec &v);
};
#endif