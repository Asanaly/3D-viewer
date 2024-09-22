#include "object.h"
//#include "plane.h"
#include "light.h"
#include "VectorLib.h"
#include <iostream>
#include<vector>

using namespace std;

char brightness[5] = {' ' , '.' , '|' , '8' , '@'};

class Display{

    /*Class for displaying the scene*/

    private:
    
        vector<Light>Scene;
        double resX, resY;
        double dx, dz;
        Vector3 camera_direction = {0,1,0};
        Point3 left_down = {0,0, 0}, right_up = {15,0,15};

        // Perspective angle
        double angleX = 2; // Will go from -2 to 2
        double angleZ = 3; // Goes from -3 to 3 
        double d_angleX;
        double d_angleZ;

    public:

        Display(){
            if(DEBUG)cout << "Display instance created" << endl;
        }

        void add_object(Light obj){
            Scene.push_back(obj) ;
        }

        void set_resolution(int resY, int resX){
            if(resX * resY <= 0){
                cout << "Resolution cannot be zero" << endl;
            }
            else if(resX >= 1000 || resY >= 1000){
                cout << "Resolution can't exceed 1000 in any axis" << endl;
            }
            else{
                this->resX = resX;
                this->resY = resY;
            }
            this -> dx = ( right_up.x - left_down.x ) / resX;
            this -> dz = ( right_up.z - left_down.z ) / resY;

            this -> d_angleX = (2 * angleX) / resX;
            this -> d_angleZ = (2 * angleZ) / resY;

        }

        short int raycast(Point3 p, int depth, Vector3 persp_camera){

            //cout << "Launching raycast from point : " <<p.x << " " << p.y << " " << p.z << " in direction : " ;
            //print_vec(persp_camera);
            //system("PAUSE");

            while(depth-- > 0){
                for(int i = 0 ; i < Scene.size() ; ++i){

                    // Adding depths with perspective

                    if(Scene[i].on_light(p , persp_camera)){
                        return Scene[i].intensity;
                    }
                }
            }
            return 0;
        }
        void screen_update(){
            
            // Raycasts every pixel

            if(DEBUG){
                cout << "Updating screen" << endl;
            }

            Point3 cur_point = left_down, temp_point;
            Vector3 perspective_camera_direction = camera_direction;
            double angleX_temp;
            double angleZ_temp;

            
            angleX_temp = -angleX;

            for(int i = 1 ; i <= resX ; ++i){
                
                angleZ_temp = -angleZ;

                temp_point = cur_point;

                for(int j = 1 ; j <= resY ; ++j){
                    perspective_camera_direction = camera_direction;
                    perspective_camera_direction.z += angleZ_temp;
                    perspective_camera_direction.x += angleX_temp;

                    int intensity_val = raycast(temp_point, 3, perspective_camera_direction);
                    
                    cout << brightness[ intensity_val ];

                    angleZ_temp += d_angleZ;
                    temp_point.z += dz;
                }cout << endl;

                angleX_temp += d_angleX;
                cur_point.x += dx; 
            }
        }

};

int main(){

    system("cls") ;

    Light lt = Light({7,10,7} , 6, 1);
    Display dsp = Display();
    
    dsp.add_object(lt);
    dsp.set_resolution(100,100);
    dsp.screen_update();

    return 0;
}