#include "object.h"
// #include "plane.h"
#include "light.h"
#include "VectorLib.h"
#include "sphere.h"
#include <iostream>
#include <memory>
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

    // Perspective angle
    double angleX = 0; //2; // Will go from -2 to 2
    double angleZ = 0; //3; // Goes from -3 to 3
    double d_angleX;
    double d_angleZ;

public:
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

        //this->d_angleX = (2 * angleX) / resX;
        //this->d_angleZ = (2 * angleZ) / resY;
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
                //cout << "On Light" << Scene[i] -> on_light(p, persp_camera) << endl;
                // Check if light?
                if(Scene[i] -> intensity > 1){
                    return Scene[i] -> intensity;
                }
                else{
                    // Recursion for the reflected light
                    //cout << "Ray is coming from ";
                    //print_point(p);

                    //cout << "Going for a recursion, current depth " << depth << endl;
                
                    Ray reflected_ray = Scene[i] -> ray_hit(p, persp_camera);
                    //cout << "I am gonna reflect from " << endl;

                    //print_point(reflected_ray.p);
                    //print_vec(reflected_ray.vect);
                    //system("PAUSE") ;
                    return max(raycast(reflected_ray.p , depth - 1 , reflected_ray.vect) - 1, 0) + (Scene[i] -> intensity) ;
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

        if (DEBUG)
        {
            cout << "Updating screen" << endl;
        }

        Point3 cur_point = left_down, temp_point;
        Vector3 perspective_camera_direction = camera_direction;
        double angleX_temp;
        double angleZ_temp;

        //angleX_temp = -angleX;

        for (int i = 1; i <= resX; ++i)
        {

            angleZ_temp = -angleZ;

            temp_point = cur_point;

            for (int j = 1; j <= resY; ++j)
            {
                perspective_camera_direction = camera_direction;
                //perspective_camera_direction.z += angleZ_temp;
                //perspective_camera_direction.x += angleX_temp;

                short int intensity_val = raycast(temp_point, 3, perspective_camera_direction);

                //cout << brightness[intensity_val];
                intensity_array[i][j] = intensity_val;
                
                //cout << "Inteisty : " << intensity_array[i][j] << endl;
                //system("PAUSE") ;

                //angleZ_temp += d_angleZ;
                temp_point.z += dz;
            }cout << endl;

            //angleX_temp += d_angleX;
            cur_point.x += dx;
        }
    }
    void print_screen()
    {
        for (int i = 1; i <= resX; ++i)
        {
            for (int j = 1; j <= resY; ++j)
            {
                short int br = ceil( (double) (intensity_array[i - 1][j] + intensity_array[i][j - 1] + intensity_array[i + 1][j] + intensity_array[i][j + 1]) / 4.0) ;
                cout << brightness[ br ];
            }
            cout << endl;
        }
    }
};

int main()
{

    system("cls");

    /*Vector3 camera_direction = {0, 1, 0};
        //map<int,int> intensity_array;
        Point3 left_down = {0, 0, 0}, right_up = {20, 0, 20};
    */

    Display dsp = Display();
    Sphere sp = Sphere(Point3{7, 6, 7}, 2);
    //Sphere sp2 = Sphere(Point3{2, 10, 7}, 4);

    Light lt = Light(Point3{7, 2, 15}, 2 , 5);
    Light lt2 = Light(Point3{15, 2, 7}, 2 , 5);

    dsp.Scene.push_back(make_unique<Light>(lt));
    dsp.Scene.push_back(make_unique<Light>(lt2));
    dsp.Scene.push_back(make_unique<Sphere>(sp));
    //dsp.Scene.push_back(make_unique<Sphere>(sp2));

    // Add objects to the scene manually

    dsp.set_resolution(100, 50);
    dsp.screen_update();
    
    
    /*while(true){
        system("cls");
        dsp.screen_update();
        dsp.Scene[0]->coord.z += 10;
    }*/
    dsp.print_screen();

    return 0;
}