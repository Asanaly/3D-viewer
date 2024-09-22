#include "global.h"
#include "object.h"
#include "VectorLib.h"
#include <cmath>

class Sphere : Object{
    public:
        double radius;

        double calculate_third(double a, double b, double radius){
            double c = radius * radius - (a * a) - (b * b) ; 
            if( c >= 0)return sqrt(c);
            else return -1;
        }

        void generate_mesh(Point3 pos, double radius, int points){
            int cnt = 0;
            while(cnt++ < points){
                triangle tr;

                double x = generateRandomValue(0, radius);
                double y = generateRandomValue(0, radius);
                double z = calculate_third(x,y,radius);

                if(z == 0){
                    cnt--;
                    continue;
                }

                Point3 base = {x + pos.x,y + pos.y,z + pos.z};

                x += 0.5;
                z = calculate_third(x,y,radius) ;
                if(z == 0){
                    cnt--;
                    continue;
                }
                Point3 son1 = {x + pos.x,y + pos.y,z + pos.z};

                y += 0.5;
                z = calculate_third(x,y,radius) ;
                Point3 son2 = {x + pos.x,y + pos.y,z + pos.z};

                if(z == 0){
                    cnt--;
                    continue;
                }

                tr = {base, son1, son2};
                Mesh.push_back(tr) ;

            }
        }

        double on_light(Point3 a, Vector3 dir){
            return 0.0;
        }

        Ray ray_hit(Point3 p_0, Vector3 direction){

            // Returns ray reflected from the mesh grid triangle

            for(int i = 0 ; i < Mesh.size() ; ++i){

                // Check for every point in the triangle

                if(VectorSolver::onVector(p_0, direction, Mesh[i].a)){
                    Ray reflected_ray = {Mesh[i].a , VectorSolver::reflect_Surf(direction, VectorSolver::get_normal_triangle(Mesh[i]))} ;
                    return reflected_ray;
                }
                if(VectorSolver::onVector(p_0, direction, Mesh[i].b)){
                    Ray reflected_ray = {Mesh[i].b , VectorSolver::reflect_Surf(direction, VectorSolver::get_normal_triangle(Mesh[i]))} ;
                    return reflected_ray;
                }
                if(VectorSolver::onVector(p_0, direction, Mesh[i].c)){
                    Ray reflected_ray = {Mesh[i].c , VectorSolver::reflect_Surf(direction, VectorSolver::get_normal_triangle(Mesh[i]))} ;
                    return reflected_ray;
                }
            }
            return {{0,0,0}, {0,0,0}};
        }

        Sphere(Point3 pos, double radius) : Object(pos){
            this -> radius = radius ;
            generate_mesh(pos, radius, 100) ;
        }

        
};

int main(){
    Sphere sp = Sphere({0,10,0} , 1) ;

    Ray ray = sp.ray_hit({0,7,0}, {0,1,0});
    
    cout << "Reflected form point : " << ray.p.x << " " << ray.p.y << " " << ray.p.z << endl;
    cout << "Reflected vector : "; print_vec(ray.vect);

}