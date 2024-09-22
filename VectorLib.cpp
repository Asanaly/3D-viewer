#include "global.h"
#include "VectorLib.h"

const double EXC = 99999999999;

double max(double a, double b){

    if(a == EXC)return b;
    if(b == EXC)return a;

    if(a - b >= 0)return a;
    return b;
}
double min(double a, double b){

    if(a == EXC)return b;
    if(b == EXC)return a;

    if(a - b >= 0)return b;
    return a;
}

VectorSolver::VectorSolver() {
    // So empty?
}

Vector3 VectorSolver::get_normal_triangle(triangle tr){
    // Compute two vectors;
    Point3 a = tr.a, b = tr.b, c = tr.c;
    Vector3 vec1 = set_vec(a.x - b.x, a.y - b.y , a.z - b.z);
    Vector3 vec2 = set_vec(a.x - b.x, a.y - b.y , a.z - b.z);

    Vector3 normal = VectorSolver::crossP(vec1, vec2);
    return normal;
}

double VectorSolver::dot(Vector3 a, Vector3 b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

bool VectorSolver::onVector(Point3 p_0, Vector3 vect, Point3 p_1)
{
    cout << "OnVector func : " << endl;
    cout << "Going from : "; print_point(p_0);
    cout << "In direction : "; print_vec(vect);
    cout << "To : "; print_point(p_1);

    // Checks if points is in the directioncls of a vector
    double t1 = EXC, t2 = EXC, t3 = EXC;
    if(vect.x != 0)t1 = (p_1.x - p_0.x) / vect.x;
    if(vect.y != 0)t2 = (p_1.y - p_0.y) / vect.y;
    if(vect.z != 0)t3 = (p_1.z - p_0.z) / vect.z;

    double mx, mn;

    cout << t1 << " " << t2 << " " << t3 << endl;

    mx = max(t1, max(t2, t3)) ;
    mn = min(t1, min(t2, t3)) ;

    cout << "Range : " << (mx - mn) << endl;
    system("PAUSE") ;

    // Range < precision
    return (mx - mn) <= PRECISION;
}
Vector3 VectorSolver::crossP(Vector3 a, Vector3 b)
{
    Vector3 product;
    product.x = a.y * b.z - b.y * a.z;
    product.y = -(a.x * b.z - a.z * b.x);
    product.z = (a.x * b.y - b.x * a.y);
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

Vector3 VectorSolver::reflect_Surf(Vector3 ray, Vector3 surf)
{
    /*
        Computes reflected vector
    */
    
    Vector3 plane = crossP(ray, surf);
    double dt = dot(ray, surf);

    Vector3 refl = minus(ray, mult(surf, 2 * (dot(ray, surf) * dot(surf, surf))));

    return refl;
}
