#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cstdio>
#include <string>
#include <vector>
#include <array>
#include <cmath>

typedef unsigned int uint;
typedef unsigned long long ull;

typedef std::vector<uint> vuint;
typedef const vuint & cvuint;

typedef std::vector<std::string> vstr;
typedef const vstr & cvstr;

namespace constants{
    constexpr double A = 10;                    // leave it
    constexpr double omega = 20 * M_PI;         // leave it
}

enum Target{
    Minimum, // 0
    Maximum, // 1
};
struct Range{ 
    double a; 
    double b;
};

namespace constants{ //* can be modified to adjust program
    constexpr uint n = 2;                           //*  n represents how many dimentions Restring function has // remember to change ranges
    constexpr uint accuracy = 6;                    //* can be changed, but 6 will be the best choice I guess
    constexpr uint populationSize = 10;             //* how many chromosomes belongs to the population
    constexpr Range ranges[constants::n] = {        //* ranges limits the value that will be passed as a parameter for the Restring function (for each dimention)
        {-1, 1},
        {-1, 1},
    };
    constexpr Target lookingFor = Target::Minimum;  //* looking for maximum or minimum

    // selection
    constexpr uint groupSize = 2;                   //* represents amount of chromosomes in one group, need to be less than populationSize, prefered is 2

    // mutation
    constexpr double mutationProbability = 0.03;
    constexpr double inversionProbability = 0.15;

    // crossbreeding
    constexpr double involvementCrossbreedingProbability = 0.6; //* prefered larger than 0.5
}

/**
 * @brief x to the power of y
 * 
 * @param x 
 * @param y 
 * @return ull 
 */
ull constPowULL(ull x, ull y) noexcept;

/**
 * @brief returning decimal value, that represents amount of possibilities to 
 * create partOfChromosome, knowing the accuracy and the range
 * 
 * @param i index of the part of chromosome [0, n-1)
 * @return large integer
 */
ull partOfChromosomeMaxValue(uint i) noexcept;

/**
 * @brief returning amount of bits, that is required to represent value got by partOfChromosomeMaxValue()
 * 
 * @param i index of the part of chromosome [0, n-1)
 * @return small integer
 */
uint partOfChromosomeBitsRequired(uint i) noexcept;

double function(double x_es[constants::n]) noexcept;

ull translateStringToBinary(const std::string &string);

#endif // CONSTANTS_HPP