#pragma once
#include <random>

class Random {
private:
    //static: one instance of the variable, can be called by class; ALL INSTANCES SHARE IT
    //they exist for the lifetime of the program
    static std::mt19937 random;
public:
    static int Int(int min, int max);
    static float Float(float min, float max);

};