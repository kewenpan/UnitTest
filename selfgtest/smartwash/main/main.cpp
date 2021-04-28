//
// Created by blithepan on 2021/4/2.
//

#include <iostream>
#include "smartwash.h"

int main() {
    SmartWash::GetInstance().ConfigUserMode(8,true);
    std::cout << "test" << std::endl;
}