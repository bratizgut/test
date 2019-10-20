#include <iostream>
#include "tritset.h"

int main(){

    tritset unit(8);

    unit[20] = trit::True;

    tritset unit2(30);

    unit = unit2;
    
    // unit[2] = trit::True;

    // unit[1] = unit[2];

    // std::cout << (unit[1] | unit[2]) << std::endl;

    // std::cout << unit[20];

    tritset unit3 = unit | unit2;

    tritset unitc(20);

    std::cout << "s";
    
    return 0;
}