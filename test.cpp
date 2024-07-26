#include <iostream>
#include <vector>
#include <cmath>

#include "random/random.hpp"

// constexpr double PI  = 3.141592653589793238462643383279;
// constexpr double PI2 = 3.1415926535897934;

template<typename T>
std::string to_binary(T f){
    std::string s;
    uint64_t u = *(uint64_t*)&f;
    s.resize(64);
    for(int i = 63; i>=0; i--){
        s.at(63-i) = '0' + ((u & (uint64_t)1<<i) != 0);
    }
    return s;
}


uint64_t random_map(uint64_t num, uint64_t seed){
    const static int64_t prime = 29996224275833; //The 1 trillionth prime!!

    num *= prime;      //Spread out nearby values
    num ^= num << 7;   //XorShift random number generator *2
	num ^= num >> 9;

    num ^= seed;       //Influence rng via seed

	num ^= num << 13;
	num ^= num >> 7;
	num ^= num << 17;

    return num;
}

struct Vec{
    int a;
    int b;
};

int main(){
    Vec vec;
    vec.a = 0;
    vec.b = 1;

    uint64_t val = *(uint64_t*)&vec;

    std::cout << &vec << "\n" << &val << "\n";

    int last;
    std::cout << &last << "\n"; 
    // for(int i = 0; i<100; i++){
    //     std::cout << to_binary(random_map(i, 1)) << "\n";
    // }
}