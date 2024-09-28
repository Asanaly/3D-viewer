#ifndef LIGHT_H
#define LIGHT_H

#include "global.h"
#include "object.h"
#include "VectorLib.h"
#include <cmath>

using namespace std;


class Light : public Object{

    public:
        double radius;
        
        Light(Point3 pos, double rad, double intensity);

        bool on_light(Point3 a, Vector3 dir);

        Ray ray_hit(Point3 p_0, Vector3 direction);

};

#endif