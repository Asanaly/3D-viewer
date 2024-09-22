#ifndef BOX_H
#define BOX_H

#include "global.h"
#include "VectorLib.h"
#include "object.h"
#include <vector>

class Square_Plane : Object{

    /*
    int dx[4] = {1 , 0 , -1 , 0};
    int dx2[4] = {0 , -1 , 0 , 1};
    */

    public:

        Point3 pos1, pos2;

        Point3 generate_square_point(Point3 a, Point3 b){
            Point3 p;
            p.x = generateRandomValue(a.x, b.x);
            p.y = generateRandomValue(a.y, b.y);
            p.z = generateRandomValue(a.z, b.z);
        }

        Square_Plane(Point3 position1, Point3 position2) : Object(position1){

            pos1 = position1;
            pos2 = position2;

            // Generate mesh
            int cnt = 0;

            Point3 p, p2, p3;
            
            while(cnt++ < TRIANGLES){
                p = generate_square_point(pos1, pos2);
                p2 = p;
                p2.x += 0.1;
                p3 = p;
                p3.y += 0.1;
                triangle tr;
                
                tr.a = p;
                tr.b = p2;
                tr.c = p3;

                Mesh.push_back(tr);
            }
        }
     
};


#endif