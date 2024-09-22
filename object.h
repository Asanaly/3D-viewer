#ifndef OBJECT_H
#define OBJECT_H

#include "global.h"
#include <vector>
#include "VectorLib.h"

class Object{
    // Don't use it alone
    // Maybe add colour later
    public:
        
        Point3 coord;

        vector<triangle>Mesh;

        Object(Point3 coordinates){
            coord = coordinates;
        }

        Point3 get_coord(){
            return coord;
        }

        void set_coord(Point3 p){
            coord = p;
        }
};


#endif