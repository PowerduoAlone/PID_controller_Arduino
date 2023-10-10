#include <iostream>
#include <ctime>
#include "windows.h"
#include "PID.h"

using namespace std;

class PID_CPP : public PID
{
public:
    PID_CPP() : PID(1,0,0,true){}
private:
    unsigned long determine_time(){
        return std::clock();
    }
};

PID_CPP controller;
float desired_temp = 20;
float temp = 22.5;
bool test = false;

int main()
{
    cout << "Hello world!" << endl;
    //controller.start(desired_temp)
    while(1){
        test = controller.calculate_controller_output_bool(temp);
        Sleep(200);
        desired_temp +=1;
        std::cout << test << std::endl;
    }
    return 0;
}
