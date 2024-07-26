#pragma once

#include <iostream>
#include <string>

class Savable{
    public:
        virtual void save(std::string filename) = 0;
        virtual void load(std::string filename) = 0;
};