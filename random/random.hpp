#pragma once

#include <iostream>
#include <random>
#include <array>
#include <ctime>

class Xor128{ //XorShift pseudorandom number generator. Period of 2^128 - 1. Cant be seeded with 0
    private:
        uint64_t m_state[2];

    public:
        Xor128(){
            seed(std::time(0));
        }

        Xor128(uint64_t seed_value){
            seed(seed_value);
        }      

        void seed(uint64_t seed_value){
            m_state[0] = seed_value;
            m_state[1] = seed_value;
        }

        uint64_t operator() () {
            uint64_t t = m_state[0];
            uint64_t const s = m_state[1];
            m_state[0] = s;
            t ^= t << 23;
            t ^= t >> 18;
            t ^= s ^ (s >> 5);
            m_state[1] = t;
            return t + s;
        }
};

std::string bitstring(uint64_t num){
    std::string str;
    str.resize(64);
    for(int i = 0; i<64; i++){
        str.at(63-i) = '0' + ((num & (uint64_t)1 <<i) > 0);
    }
    std::cout << str << " " << num << "\n";
    return str;
}

inline int distribution_uniform(Xor128& rng, size_t num){
    return rng()%num;
}

int distribution_discrete(Xor128& rng, const std::vector<uint>& weights){
    uint count = 0;
    for(const uint& v : weights){
        count += v;
    }

    if(count == 0) return -1;

    uint64_t rand = rng()%count;

    uint sum = 0;
    for(uint i = 0; i<weights.size(); i++){
        sum += weights.at(i);
        if(rand < sum) return i;
    }

    //Should never reach here
    return -1; 
}

template<size_t Size>
int distribution_discrete(Xor128& rng, const std::array<uint, Size>& weights){
    uint count = 0;
    for(const uint& v : weights){
        count += v;
    }

    uint64_t rand = rng();
    rand %= count;

    uint sum = 0;
    for(uint i = 0; i<weights.size(); i++){
        if(rand <= sum) return i;
        sum += weights.at(i);
    }

    //Should never reach here
    return -1; 
}