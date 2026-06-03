// utils.cpp
#include <iostream>
#include "utils.h"

void clearScreen() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void titleScreen(std::string title){
    // clearScreen();
    std::cout << sep << std::endl;
    std::cout << "           " << title << std::endl;
    std::cout << sep << std::endl;
}