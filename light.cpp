#include "global.h"
#include "object.h"
#include "VectorLib.h"
#include <cmath>
#include "light.h"

using namespace std;

Light::Light(Point3 pos, double rad, double intensity) : Object(pos)
{
    if(DEBUG)cout << "Light created at : " <<coord.x << " " << coord.y << " " << coord.z << endl;
    this->intensity = intensity;
    this->radius = rad;
}

double Light::on_light(Point3 a, Vector3 dir)
{
    // Vector from the ray origin 'a' to the light center 'coord'
    Vector3 oc = {a.x - coord.x, a.y - coord.y, a.z - coord.z};

    // Coefficients of the quadratic equation
    double A = VectorSolver::dot(dir, dir);
    double B = 2.0 * VectorSolver::dot(oc, dir);
    double C = VectorSolver::dot(oc, oc) - radius * radius;

    // Discriminant of the quadratic equation
    double discriminant = B * B - 4 * A * C;

    if (discriminant < 0) {
        // No intersection, return 0 (no light hits the point)
        return 0;
    }
    else {
        // Ray intersects the sphere, compute the nearest intersection point
        double t1 = (-B - sqrt(discriminant)) / (2.0 * A);
        double t2 = (-B + sqrt(discriminant)) / (2.0 * A);

        // We're interested in the first positive `t` (closest point of intersection)
        if (t1 > 0) {
            return intensity;  // Ray hits the light
        }
        else if (t2 > 0) {
            return intensity;  // Ray hits the light
        }
        else {
            return 0;  // Both intersections are behind the ray origin
        }
    }
}

