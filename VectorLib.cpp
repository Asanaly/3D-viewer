#include "global.h"
#include "VectorLib.h"

const double EXC = 99999999999;

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

    return mult(normal, -1);
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

/*
int main(){
    print_vec(VectorSolver::reflect_Surf({1,0,0} , {-1,1,0}));
}*/