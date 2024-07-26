#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#include <SFML/System/Vector2.hpp>

class PerlinNoise{
    private:
        constexpr static double s_PI = 3.141592653589793238462643383279;
        uint64_t m_seed;

        sf::Vector2f random_unit_vector(uint64_t num) const;
        uint64_t bitcast(const sf::Vector2i& pos) const;

        float linear_interpolate (const float& v1, const float& v2, const float& f) const;
        float cubic_interpolate  (const float& v1, const float& v2, const float& f) const;
        float quintic_interpolate(const float& v1, const float& v2, const float& f) const;
        float dot_product(const sf::Vector2f& v1, const sf::Vector2f& v2) const;
        

    public:
        PerlinNoise(const uint64_t& seed);
        void seed(const uint64_t& seed);

        float sample(sf::Vector2f pos, const sf::Vector2u& wavelength) const;  //Position, Wavelength
};

sf::Vector2f PerlinNoise :: random_unit_vector(uint64_t num) const{
    const static int64_t prime = 29996224275833; //The 1 trillionth prime!!

    num *= prime;      //Spread out nearby values
    num ^= num << 7;   //XorShift random number generator *2
	num ^= num >> 9;

    num ^= m_seed;     //Influence rng via seed

	num ^= num << 13;  //XorShift final time
	num ^= num >> 7;
	num ^= num << 17;

    double val = num / ((uint64_t)1<<63) * s_PI;

    return sf::Vector2f(cos(num), sin(num));
}

uint64_t PerlinNoise :: bitcast(const sf::Vector2i& pos) const{
    return *(uint64_t*)&pos;
}

float PerlinNoise :: linear_interpolate(const float& v1, const float& v2, const float& f) const{
    return v1 * (1-f) + v2 * f;
}

float PerlinNoise :: cubic_interpolate(const float& v1, const float& v2, const float& f) const{
    const float val = -2 * f * f * f + 3 * f * f;
    return linear_interpolate(v1, v2, val);
}

float PerlinNoise :: quintic_interpolate(const float& v1, const float& v2, const float& f) const{
    const float f3 = f * f * f;
    const float val = (6 * f * f - 15 * f + 10) * f3;
    return linear_interpolate(v1, v2, val);
}

float PerlinNoise :: dot_product(const sf::Vector2f& v1, const sf::Vector2f& v2) const{
    return v1.x * v2.x + v1.y * v2.y;
}

PerlinNoise :: PerlinNoise(const uint64_t& seed){
    m_seed = seed;
}

float PerlinNoise :: sample(sf::Vector2f pos, const sf::Vector2u& wavelength) const{
    //Scale down to range of 0-1
    pos.x /= wavelength.x;
    pos.y /= wavelength.y;
    pos.x -= (pos.x < 0);
    pos.y -= (pos.y < 0);
    sf::Vector2i v11 = (sf::Vector2i)pos; //Top left index

    // Calculate remainder between 0-1
    pos.x -= v11.x;
    pos.y -= v11.y;

    //Scale back up to 0-Wavelength 
    v11.x *= wavelength.x;
    v11.y *= wavelength.y;

    //Calculate other vertices of bounding box
    sf::Vector2i v12 = v11 + sf::Vector2i(wavelength.x,            0); 
    sf::Vector2i v21 = v11 + sf::Vector2i(           0, wavelength.y); 
    sf::Vector2i v22 = v11 + sf::Vector2i(wavelength.x, wavelength.y); 

    //Final Interpolation Step
    float u11 = dot_product(sf::Vector2f(pos.x       , pos.y       ), random_unit_vector(bitcast(v11)));
    float u12 = dot_product(sf::Vector2f(pos.x - 1.0f, pos.y       ), random_unit_vector(bitcast(v12)));
    float u21 = dot_product(sf::Vector2f(pos.x       , pos.y - 1.0f), random_unit_vector(bitcast(v21)));
    float u22 = dot_product(sf::Vector2f(pos.x - 1.0f, pos.y - 1.0f), random_unit_vector(bitcast(v22)));

    u11 = quintic_interpolate(u11, u12, pos.x);
    u21 = quintic_interpolate(u21, u22, pos.x);

    return quintic_interpolate(u11, u21, pos.y);
}
