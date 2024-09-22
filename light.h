#ifndef LIGHT_H
#define LIGHT_H

#include "global.h"
#include "object.h"
#include "VectorLib.h"
#include <cmath>

using namespace std;


class Light : Object{

    public:
        short int intensity;
        double radius;
        
        Light(Point3 pos, double rad, double intensity);

        double on_light(Point3 a, Vector3 dir);

};

#endif