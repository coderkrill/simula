#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

class Realm : public sf::Drawable{
    private:
        int m_elev; //Elevation
        int m_temp; //Temperature
        int m_fert; //Soil Fertility
        
        

    public:
        Realm();

        
};