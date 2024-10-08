#ifndef GLOBAL_H
#define GLOBAL_H

#include <random>
#include <iostream>
using namespace std;


const int INF = 9999999;
const bool DEBUG = true;
const double PRECISION = 0.001;
const double TRIANGLES = 100;

struct Vector3{
    double x;
    double y;
    double z;

};

struct Point3{
    double x;
    double y;
    double z;
};


Point3 vect_to_point(Vector3 v);

Vector3 point_to_vect(Point3 p);

typedef struct{
    Point3 p;
    Vector3 vect;
}Ray;

typedef struct{
    Point3 a,b,c;
}triangle;

Vector3 set_vec(double x, double y, double z);

void print_vec(Vector3 vec);

void print_point(Point3 p);

double generateRandomValue(double l, double r);


#endif

