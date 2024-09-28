#include "global.h"
#include "VectorLib.h"
#include "object.h"
#include "square.h"

Square::Square(Point3 pos, double size) : Object(pos)
{
    this->size = size;
    this->intensity = 1;
    generate_mesh(pos, size) ;
}

bool Square::on_light(Point3 ray_origin, Vector3 dir)
{

    // Vector from ray origin to the center of the square

    Vector3 pos_vec = {coord.x, coord.y, coord.z};
    Vector3 ray_origin_vec = {ray_origin.x, ray_origin.y, ray_origin.z};

    Vector3 w = VectorSolver::minus(pos_vec, ray_origin_vec);
    double t = VectorSolver::dot(w, dir);

    //cout << "Dot between" << endl;
    //print_vec(w);
    //print_vec(dir);
    //cout << "Checking on light the dot product :" << t << endl; 


    // Behind the camera
    if (t <= 0)
    {
        return false;
    }

    Vector3 Q = VectorSolver::plus(ray_origin_vec, VectorSolver::mult(dir, t));

    if (!(Q.x >= coord.x - size && Q.x <= coord.x + size))
        return false;
    if (!(Q.y >= coord.y - size && Q.y <= coord.y + size))
        return false;
    if (!(Q.z >= coord.z - size && Q.z <= coord.z + size))
        return false;

    return true;
}

void Square::generate_mesh(Point3 pos, double size)
{
    // First define all squares

    Point3 A, B, C, D, A_1, B_1, C_1, D_1;
    Square_plane bottom, top, left, right, front, back;

    // Define points on the first square (in the yz-plane at x = coord.x)
    A = {coord.x - size, coord.y - size, coord.z - size}; // left-down
    B = {coord.x - size, coord.y - size, coord.z + size}; // right-down
    C = {coord.x - size, coord.y + size, coord.z - size}; // left-up
    D = {coord.x - size, coord.y + size, coord.z + size}; // right-up

    // Define points on the second square (shifted along x-axis)
    A_1 = {coord.x + size, coord.y - size, coord.z - size}; // left-down
    B_1 = {coord.x + size, coord.y - size, coord.z + size}; // right-down
    C_1 = {coord.x + size, coord.y + size, coord.z - size}; // left-up
    D_1 = {coord.x + size, coord.y + size, coord.z + size}; // right-up

    top = {A_1, C_1, D_1, B_1};
    bottom = {C, A, B, D};
    front = {D, D_1, C_1, C};
    back = {B_1, B, A, A_1};
    right = {B, B_1, D_1, D};
    left = {A_1, A, C, C_1};

    // Adding triangles to the mesh

    Mesh.push_back(top.get_first_tr());
    Mesh.push_back(top.get_second_tr());

    Mesh.push_back(bottom.get_first_tr());
    Mesh.push_back(bottom.get_second_tr());

    Mesh.push_back(right.get_first_tr());
    Mesh.push_back(right.get_second_tr());

    Mesh.push_back(left.get_first_tr());
    Mesh.push_back(left.get_second_tr());

    Mesh.push_back(front.get_first_tr());
    Mesh.push_back(front.get_second_tr());

    Mesh.push_back(back.get_first_tr());
    Mesh.push_back(back.get_second_tr());

    // Done, so easy huh?
}
