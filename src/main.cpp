#include <windows.h>
#include <iostream>
#include "PID.h"

class PID_CPP : public PID
{
    PID_CPP() : PID;
};

int main(){
    std::cout << "Hello World";
    return 0;
}