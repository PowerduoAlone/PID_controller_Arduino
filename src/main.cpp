#include <windows.h>
#include <iostream>
#include <chrono>
#include "PID.h"

class PID_CPP : public PID
{
    private:
        virtual unsigned long determine_time(){
            const auto p1 = std::chrono::system_clock::now();
            std::cout << p1.time_since_epoch().count() << "\n";
            return p1.time_since_epoch().count();
        }
};

auto p1 = std::chrono::system_clock::now();
float temp = 23;
float des_temp = 20.5;
bool res = false;
PID_CPP contr;

int main(){
    std::cout << "starting PID controller";
    while (1)
    {
        Sleep(200);
        
    }
    
    return 0;
}