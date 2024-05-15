#include "vec.h"
#include <cmath>
#include <iostream>
#include <fstream>

Vec::Vec(){
    x = 0;
    y = 0;
    z = 0;
}

Vec::Vec(float xV){
    x = xV;
    y = xV;
    z = xV;
}

Vec::Vec(float xV, float yV, float zV){
    x = xV;
    y = yV;
    z = zV;
}

Vec& Vec::norm(){ //recall: normalization of a vector is each entry is divided by its length 
    float normSquared = lengthSquared();
    if( normSquared > 0 ){ //assuring there is no division by zero
        float reciprocal = 1 / sqrt(normSquared); 
        x *= reciprocal;
        y *= reciprocal;
        z *= reciprocal;
    }
    return *this;
}

Vec Vec::operator*(const float &f) const{ //recall: scaling a vector is multiplying each entry by said scalar
    return Vec(x*f, y*f, z*f);
}

Vec Vec::operator*(const Vec &v) const{
    return Vec(x*v.x, y*v.y, z*v.z);
}

float Vec::dotProduct(const Vec &v) const{
    return (x*v.x)+(y*v.y)+(z*v.z);
}

Vec Vec::operator-(const Vec &v) const{
    return Vec(x-v.x, y-v.y, z-v.z);
}

Vec Vec::operator+(const Vec &v) const{
    return Vec(x+v.x, y+v.y, z+v.z);
}

Vec& Vec::operator+=(const Vec &v){
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vec& Vec::operator*=(const Vec &v){
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

Vec Vec::operator-() const{
    return Vec(-x, -y, -z);
}

float Vec::length() const{
    return sqrt(lengthSquared());
}

float Vec::lengthSquared() const{
    return (x*x)+(y*y)+(z*z);
}

ostream& operator<<(ostream &os, Vec &v){
    os << "[" << v.x << " " << v.y << " " << v.z << "]";
    return os;
}