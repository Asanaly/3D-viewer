#include "global.h"
#include <random>
#include <iostream>

using namespace std;

Vector3 set_vec(double x, double y, double z){
    Vector3 vc;
    vc.x = x;
    vc.y = y;
    vc.z = z;
    return vc;
}

void print_vec(Vector3 vec){
    printf("Vector:(%lf, %lf, %lf)\n", vec.x, vec.y, vec.z);
}


Point3 vect_to_point(Vector3 v){
    return {v.x, v.y, v.z};
}

Vector3 point_to_vect(Point3 p){
    return {p.x, p.y, p.z} ;
}

void print_point(Point3 p){
    printf("Point:(%lf, %lf, %lf)\n", p.x, p.y, p.z);
}

double generateRandomValue(double l, double r) {
    if(r < l)swap(l , r);
    // Create a random device and use it to seed the random number generator
    std::random_device rd;  
    std::mt19937 gen(rd()); // Mersenne Twister random number generator
    std::uniform_real_distribution<double> dis(l, r); // Uniform distribution in the range [l, r]

    return dis(gen); // Generate and return the random value
}
