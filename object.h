#ifndef OBJECT_H
#define OBJECT_H

#include "global.h"
#include <vector>
#include "VectorLib.h"

class Object{
    // Don't use it alone
    // Maybe add colour later
    public:
        
        short int intensity = 1;

        Point3 coord;

        virtual Ray ray_hit(Point3 p_0, Vector3 direction){
            cout << "Object ray_hit error" << endl;
            return {{0,0,0}, {0,0,0}};
        }

        virtual bool on_light(Point3 a, Vector3 dir){
            return 0;
        }

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