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

        static bool onVector(Point3 p_0, Vector3 vect, Point3 p_1);

        static Vector3 crossP(Vector3 a, Vector3 b);

        static Vector3 minus(Vector3 a, Vector3 b);
        
        static Vector3 plus(Vector3 a, Vector3 b);

        static Vector3 mult(Vector3 a, double val);
        
        static bool equall(Vector3 a, Vector3 b);
        
        static Vector3 reflect_Surf(Vector3 ray, Vector3 surf);
};

#endif