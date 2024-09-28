#include "object.h"
#include "square.h"
#include "light.h"
#include "VectorLib.h"
#include "sphere.h"
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <vector>
#include <map>

using namespace std;

char brightness[7] = {' ', '.', '*','|' , '8', '@'};

class Display
{

    /*Class for displaying the scene*/

private:
    double resX, resY;
    double dx, dz;
    Vector3 camera_direction = {0, 1, 0};
    short int intensity_array[200][200];
    Point3 left_down = {0, 0, 0}, right_up = {20, 0, 20};
    double current_camera_angle = 0;

    // Perspective angle
    double angleX = 1; // Will go from -2 to 2
    double angleZ = 1; // Goes from -3 to 3
    double d_angleX;
    double d_angleZ;

public:

    void rotate_aroundX(double angle_change){
        
        /*Rotate camera around y axis, ang_speed positive for counter clockwise*/

        double angle = current_camera_angle + angle_change;
        current_camera_angle += angle_change;

        camera_direction.y = cos(angle) ;
        camera_direction.z = sin(angle) ;
        print_vec(camera_direction) ;
        cout << current_camera_angle << endl;
    }

    vector<std::unique_ptr<Object>> Scene;

    Display()
    {
        if (DEBUG)
            cout << "Display instance created" << endl;
    }

    void set_resolution(int resY, int resX)
    {
        if (resX * resY <= 0)
        {
            cout << "Resolution cannot be zero" << endl;
        }
        else if (resX > 1000 || resY > 1000)
        {
            cout << "Resolution can't exceed 1000 in any axis" << endl;
        }
        else
        {
            this->resX = resX;
            this->resY = resY;
        }
        this->dx = (right_up.x - left_down.x) / resX;
        this->dz = (right_up.z - left_down.z) / resY;

        this->d_angleX = (2 * angleX) / resX;
        this->d_angleZ = (2 * angleZ) / resY;
    }

    short int raycast(Point3 p, int depth, Vector3 persp_camera)
    {

        if (depth == 0)
            return 0;

        for (int i = 0; i < Scene.size(); ++i)
        {
            // Adding depths with perspective

            if (Scene[i] -> on_light(p, persp_camera))
            {
                // Check if light?
                if(Scene[i] -> intensity > 1){
                    return Scene[i] -> intensity;
                }
                else{
                    // Recursion for the reflected light
                    // cout << "Ray is coming from with depths " << depth <<endl;
                
                    //print_point(p);
                    //print_vec(persp_camera);


                    Ray reflected_ray = Scene[i] -> ray_hit(p, persp_camera);
                    //cout << "I am gonna reflect from " << endl;

                    //print_point(reflected_ray.p);
                    //print_vec(reflected_ray.vect);
                    //system("PAUSE") ;
                    return max( max(raycast(reflected_ray.p , depth - 1 , reflected_ray.vect) - 1, 0) , (int) (Scene[i] -> intensity) ) ;
                } 
            }
            else{
                //cout << "I am not touching object number " << i << endl;
            }
        }
        return 0;
    }
    void screen_update()
    {

        // Raycasts every pixel


        Point3 cur_point = left_down, temp_point;
        Vector3 perspective_camera_direction = camera_direction;
        double angleX_temp;
        double angleZ_temp;

        angleX_temp = -angleX;

        for (int i = 1; i <= resX; ++i)
        {

            angleZ_temp = -angleZ;

            temp_point = cur_point;

            for (int j = 1; j <= resY; ++j)
            {
                perspective_camera_direction = camera_direction;
                
                perspective_camera_direction.z += angleZ_temp;
                perspective_camera_direction.x += angleX_temp;

                short int intensity_val = raycast(temp_point, 2, VectorSolver::normalize( perspective_camera_direction ));

                //cout << brightness[intensity_val];
                intensity_array[i][j] = intensity_val;
                
                //cout << "Inteisty : " << intensity_array[i][j] << endl;
                //system("PAUSE") ;

                angleZ_temp += d_angleZ;
                temp_point.z += dz;
            }cout << endl;

            angleX_temp += d_angleX;
            cur_point.x += dx;
        }
    }
    void print_screen()
    {
        system("cls") ;
        string buffer = "";
        for (int i = 1; i <= resX; ++i)
        {
            for (int j = 1; j <= resY; ++j)
            {
                short int br = ceil( (double) (intensity_array[i - 1][j] + intensity_array[i][j - 1] + intensity_array[i + 1][j] + intensity_array[i][j + 1]) / 4.0) ;
                buffer += brightness[ br ];
            }
            buffer += '\n';
        }
        cout << buffer;
    }
};

int main()
{

    /*Vector3 camera_direction = {0, 1, 0};
        //map<int,int> intensity_array;
        Point3 left_down = {0, 0, 0}, right_up = {20, 0, 20};
    */
   
    Display dsp = Display();
    dsp.set_resolution(150, 80);

    Square sq = Square({10,1,5}, 2);
    Square floor = Square({100, 1 ,0} , 82) ;
    
    Sphere sp = Sphere(Point3{10, 1, 15}, 2) ;
    
    Light lt = Light(Point3{15, -20, 10}, 20 , 5);

    dsp.Scene.push_back(make_unique<Square>(sq)) ;
    dsp.Scene.push_back(make_unique<Light>(lt)) ;
    dsp.Scene.push_back(make_unique<Sphere>(sp));
    dsp.Scene.push_back(make_unique<Square>(floor));

    //dsp.screen_update();
    //dsp.print_screen();

    /*Sphere sp = Sphere(Point3{10, 1, 10}, 2);
    Sphere sp2 = Sphere(Point3{10, 1, 15}, 3);
    Sphere sp3 = Sphere(Point3{10, 1, 5}, 3);
    Light lt = Light(Point3{10, -20, 10}, 20 , 5);

    dsp.Scene.push_back(make_unique<Light>(lt));
    dsp.Scene.push_back(make_unique<Sphere>(sp));
    dsp.Scene.push_back(make_unique<Sphere>(sp2));
    dsp.Scene.push_back(make_unique<Sphere>(sp3));

    // Add objects to the scene manually

    dsp.screen_update();
    */
    
    while(true){
        dsp.screen_update();
        dsp.print_screen();
        dsp.rotate_aroundX(3.14 / 45);
        
        this_thread::sleep_for(chrono::milliseconds(200));

    }

    
    

    return 0;
}