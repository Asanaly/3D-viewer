#include "global.h"
#include "object.h"
#include "VectorLib.h"
#include <cmath>
#include "sphere.h"
#include <iostream>

double Sphere::calculate_third(double a, double b, double radius)
{
    double c = radius * radius - (a * a) - (b * b);
    if (c >= 0)
        return sqrt(c);
    else
        return -1;
}

void Sphere::generate_mesh(Point3 pos, double radius, int points)
{
    int cnt = 0;
    int layers = radius * 8;
    double height = -radius, d_height = 2 * radius / layers;
    double angle = 0, D_angle = 2 * 3.14 / points;

    vector<Point3> layer1, layer2;

    Point3 temp;

    // Starting from the bottom

    Point3 bottom = {-radius + pos.x, 0 + pos.y, 0 + pos.z};

    // Generate next layer of points
    height += d_height;

    double upd_rad = sqrt(radius * radius - height * height);

    for (int i = 1; i <= points; ++i)
    {
        temp = {height + pos.x, {upd_rad * sin(angle) + pos.y}, {upd_rad * cos(angle) + pos.z}};
        angle += D_angle;
        layer1.push_back(temp);
    }

    // Connecting first layer with bottom

    for (int i = 0; i < layer1.size() - 1; ++i)
    {
        triangle tr = {layer1[i], layer1[i + 1], bottom};
        Mesh.push_back(tr);
    }

    for (int i = 1; i <= layers - 2; ++i)
    {
        // Generate two layers
        height += d_height;
        angle = 0;

        double upd_rad = sqrt(radius * radius - height * height);

        for (int j = 1; j <= points; j++)
        {
            // Generate a points
            temp = {height + pos.x, {upd_rad * sin(angle) + pos.y}, {upd_rad * cos(angle) + pos.z}};
            layer2.push_back(temp);
            angle += D_angle;
        }

        // Connecting points back to previous level

        for (int j = 0; j < layer1.size() - 1; ++j)
        {
            // Create two triangles

            triangle tr = {layer1[j], layer1[j + 1], layer2[j]};
            Mesh.push_back(tr);

            tr = {layer2[j], layer2[j + 1], layer1[j]};

            Mesh.push_back(tr);

            layer1[j] = layer2[j];
        }

        // Old points are erased
        layer2.clear();
    }

    // Finishing up with a vertex

    Point3 vertex = {radius + pos.x, 0 + pos.y, 0 + pos.z};
    height = radius;

    angle = 0;

    for (int i = 0; i < layer1.size() - 1; ++i)
    {
        triangle tr = {layer1[i], layer1[i + 1], vertex};
        Mesh.push_back(tr);
    }
}

bool Sphere::on_light(Point3 a, Vector3 dir)
{
    // Function that returns true if ray hits the sphere

    // Vector from the ray origin 'a' to the light center 'coord'
    Vector3 oc = {a.x - coord.x, a.y - coord.y, a.z - coord.z};

    // Coefficients of the quadratic equation
    double A = VectorSolver::dot(dir, dir);
    double B = 2.0 * VectorSolver::dot(oc, dir);
    double C = VectorSolver::dot(oc, oc) - radius * radius;

    // Discriminant of the quadratic equation
    double discriminant = B * B - 4 * A * C;

    if (discriminant < 0)
    {
        // No intersection, return 0 (no light hits the point)
        return 0;
    }
    else
    {
        // Ray intersects the sphere, compute the nearest intersection point
        double t1 = (-B - sqrt(discriminant)) / (2.0 * A);
        double t2 = (-B + sqrt(discriminant)) / (2.0 * A);

        // We're interested in the first positive `t` (closest point of intersection)
        if (t1 > 0)
        {
            return 1; // Ray hits the light
        }
        else if (t2 > 0)
        {
            return 1; // Ray hits the light
        }
        else
        {
            return 0; // Both intersections are behind the ray origin
        }
    }
}

Sphere::Sphere(Point3 pos, double radius) : Object(pos)
{
    this->intensity = 0;
    this->radius = radius;
    generate_mesh(pos, radius, 100);
}
