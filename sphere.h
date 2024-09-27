#ifndef SPHERE_H
#define SPHERE_H

#include "global.h"
#include "object.h"

#include "VectorLib.h"
#include <cmath>
#include<iostream>

class Sphere : public Object{
    public:

        short int intensity = 1; 

        double radius;

        double calculate_third(double a, double b, double radius);

        void generate_mesh(Point3 pos, double radius, int points);

        bool on_light(Point3 a, Vector3 dir);
        
        Ray ray_hit(Point3 p_0, Vector3 direction);

        Sphere(Point3 pos, double radius);

        
};

#endif