#include "global.h"
#include "VectorLib.h"

const double EXC = 99999999999;

bool absolute(double a){
    return (a < 0) ? -a : a;
}

double max(double a, double b)
{

    if (a == EXC)
        return b;
    if (b == EXC)
        return a;

    if (a - b >= 0)
        return a;
    return b;
}
double min(double a, double b)
{

    if (a == EXC)
        return b;
    if (b == EXC)
        return a;

    if (a - b >= 0)
        return b;
    return a;
}

VectorSolver::VectorSolver()
{
    // So empty?
}

double VectorSolver::dist(Point3 a, Point3 b)
{
    double d = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
    return sqrt(d);
}

Vector3 VectorSolver::get_normal_triangle(triangle tr)
{
    // Compute two vectors;

    Point3 a = tr.a, b = tr.b, c = tr.c;
    Vector3 vec1 = set_vec(a.x - b.x, a.y - b.y, a.z - b.z);
    Vector3 vec2 = set_vec(a.x - c.x, a.y - c.y, a.z - c.z);

    Vector3 normal = VectorSolver::crossP(vec1, vec2);

    return  normalize ( mult(normal, -1) );
}

double VectorSolver::dot(Vector3 a, Vector3 b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

bool VectorSolver::onVector(Point3 p_0, Vector3 vect, Point3 p_1)
{

    // Checks if points is in the directioncls of a vector
    double t;
    if (vect.x != 0)
        t = (p_1.x - p_0.x) / vect.x;
    if (vect.y != 0)
        t = (p_1.y - p_0.y) / vect.y;
    if (vect.z != 0)
        t = (p_1.z - p_0.z) / vect.z;

    double mx, mn;

    if(t <= 0)return false;

    if ((vect.x * t + p_0.x) - p_1.x > PRECISION)
        return false;

    if ((vect.y * t + p_0.y) - p_1.y > PRECISION)
        return false;
        
    if ((vect.z * t + p_0.z) - p_1.z > PRECISION)
        return false;

    return true;
}

Vector3 VectorSolver::crossP(Vector3 a, Vector3 b)
{
    Vector3 product;
    product.x = -(a.y * b.z - b.y * a.z);
    product.y = (a.x * b.z - a.z * b.x);
    product.z = -(a.x * b.y - b.x * a.y);
    return product;
}
Vector3 VectorSolver::minus(Vector3 a, Vector3 b)
{
    Vector3 c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
    return c;
}

Vector3 VectorSolver::plus(Vector3 a, Vector3 b)
{
    Vector3 c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
    return c;
}

Vector3 VectorSolver::mult(Vector3 a, double val)
{
    Vector3 c;
    c.x = a.x * val;
    c.y = a.y * val;
    c.z = a.z * val;
    return c;
}

bool VectorSolver::equall(Vector3 a, Vector3 b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

// Function to compute the magnitude of the vector
double VectorSolver::magnitude(Vector3 vect)
{
    return sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
}

// Function to normalize the vector
Vector3 VectorSolver::normalize(Vector3 vect)
{
    double mag = magnitude(vect);
    vect.x = vect.x / mag;
    vect.y = vect.y / mag;
    vect.z = vect.z / mag;
    return vect;
}

Vector3 VectorSolver::reflect_Surf(Vector3 ray, Vector3 surf)
{
    /*
        Computes reflected vector
    */

    // Normalizing the surface normal vector (optional if it's already normalized)
    surf = normalize(surf);

    Vector3 refl = minus(ray, mult(surf, 2 * dot(ray, surf)));

    return refl;
}


Vector3 VectorSolver :: vector_from_points(Point3 a, Point3 b){
    return {b.x - a.x , b.y - a.y , b.z - a.z} ;
}

Vector3 VectorSolver :: project_to_plane(Vector3 normal, Point3 point_plane, Point3 p ){
    Vector3 point = {p.x, p.y, p.z};
    Vector3 point_plane_v = {point_plane.x, point_plane.y, point_plane.z};
    Vector3 v = VectorSolver::minus(point, point_plane_v);

    Vector3 v_proj = VectorSolver::mult(normal,VectorSolver::dot(v , normal));
    return VectorSolver::minus(point,v_proj);
}    

double triangle_area(Point3 a, Point3 b, Point3 c) {
    // Area = 0.5 * || (b - a) x (c - a) ||
    Vector3 ab = VectorSolver::vector_from_points(a, b);
    Vector3 ac = VectorSolver::vector_from_points(a, c);
    Vector3 crossProduct = VectorSolver::crossP(ab, ac);
    return 0.5 * VectorSolver::magnitude(crossProduct);
}

bool VectorSolver :: within_triangle(triangle tr , Vector3 camera, Point3 ray_from , Vector3 plane_normal){
    // Computes if ray touches triangle
    // Return false in case if it is not

    double dot_product = dot(camera, plane_normal); // Assuming you have a dot product function

    if(dot_product >= 0)return 0;

    Vector3 a = VectorSolver::project_to_plane(camera, ray_from, tr.a) ;
    Vector3 b = VectorSolver::project_to_plane(camera, ray_from, tr.b) ;
    Vector3 c = VectorSolver::project_to_plane(camera, ray_from, tr.c) ;

    double A = triangle_area(vect_to_point(a), vect_to_point(b), vect_to_point(c));

    // Calculate areas of sub-triangles formed with point p
    double A1 = triangle_area(ray_from, vect_to_point(b), vect_to_point(c));
    double A2 = triangle_area(vect_to_point(a), ray_from, vect_to_point(c));
    double A3 = triangle_area(vect_to_point(a), vect_to_point(b), ray_from);

    // Check if the sum of sub-triangle areas equals the whole triangle's area (within a tolerance)
    return (absolute(A - (A1 + A2 + A3)) < 1e-6) ;

}
