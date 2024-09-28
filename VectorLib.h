#ifndef VECT_LIB
#define VECT_LIB

#include <vector>
#include "global.h"

using namespace std;

class VectorSolver{
    public:
        static Vector3 get_normal_triangle(triangle tr);

        VectorSolver();

        

        static double dot(Vector3 a, Vector3 b);

        static double dist(Point3 a, Point3 b);

        static bool onVector(Point3 p_0, Vector3 vect, Point3 p_1);

        static Vector3 crossP(Vector3 a, Vector3 b);

        static Vector3 minus(Vector3 a, Vector3 b);
        
        static Vector3 plus(Vector3 a, Vector3 b);

        static Vector3 mult(Vector3 a, double val);
        
        static bool equall(Vector3 a, Vector3 b);
        
        static Vector3 reflect_Surf(Vector3 ray, Vector3 surf);

        static double magnitude(Vector3 vect);

        static Vector3 normalize(Vector3 vect);

        static Vector3 project_to_plane(Vector3 normal, Point3 point_plane, Point3 point );

        static Vector3 vector_from_points(Point3 a, Point3 b);

        static bool within_triangle(triangle tr , Vector3 camera, Point3 ray_from, Vector3 plane_normal);

};

#endif