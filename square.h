#ifndef SQUARE_H
#define SQUARE_H

#include "global.h"
#include "object.h"
#include "VectorLib.h"
#include <cmath>

typedef struct{
    Point3 a,b,c,d;

    triangle get_first_tr(){
        triangle tr = {a,b,c};
        return tr;
    }
    triangle get_second_tr(){
        triangle tr = {c,d,a};
        return tr;
    }
    
}Square_plane;

class Square : public Object{

    private:
    
        double size = 1; // Actuall side of a square is size * 2
    
    public:

        Square(Point3 pos, double size);
        
        bool on_light(Point3 ray_origin, Vector3 dir);

        void generate_mesh(Point3 pos, double size);

};

#endif