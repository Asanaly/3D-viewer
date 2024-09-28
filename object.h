#ifndef OBJECT_H
#define OBJECT_H

#include "global.h"
#include <vector>
#include "VectorLib.h"

class Object
{
    // Don't use it alone
    // Maybe add colour later
public:
    short int intensity = 1;

    Point3 coord;

    Object(Point3 coordinates)
    {
        coord = coordinates;
    }

    virtual bool on_light(Point3 a, Vector3 dir)
    {
        return 0;
    }

    vector<triangle> Mesh;

    Ray ray_hit(Point3 p_0, Vector3 direction)
    {

        // Returns a ray from reflected triangle from mesh

        for (int i = 0; i < Mesh.size(); ++i)
        {

            Vector3 normal_tri = VectorSolver::get_normal_triangle(Mesh[i]);

            if (VectorSolver::within_triangle(Mesh[i], direction, p_0, normal_tri))
            {

                /*if (DEBUG){
                    cout << "This will do" << endl;
                    print_point(Mesh[i].a);
                    print_point(Mesh[i].b);
                    print_point(Mesh[i].c);
                }*/

                // Get the point of reflection by projecting it on the triangle surface
                
                Point3 proj_p = vect_to_point(VectorSolver::project_to_plane(normal_tri, Mesh[i].a, p_0));
                Vector3 reflected_vector = VectorSolver ::reflect_Surf(direction, normal_tri);

                return {proj_p, reflected_vector};
            }
        }

        return {{0, 0, 0}, {0, 0, 0}};
    }

    Point3 get_coord()
    {
        return coord;
    }

    void set_coord(Point3 p)
    {
        coord = p;
    }
};

#endif