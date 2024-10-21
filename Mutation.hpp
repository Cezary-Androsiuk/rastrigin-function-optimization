#ifndef MUTATION_HPP
#define MUTATION_HPP

#include <cstdio>
#include <string>
#include <random>

#include "constants.hpp"

namespace Mutation{
    namespace _InternalMethods{
        bool isChromosomeStillValid(const std::string &chromosome);
    };

    namespace _MutationMethods{
        char mutateGen(char gen) noexcept;
    };


    void mutation(
        const std::string chromosomesIn[constants::populationSize],
        std::string chromosomesOut[constants::populationSize]
    ) noexcept;

    namespace _InversionMethods{
        std::string inversePartOfChromosome(const std::string &chromosome) noexcept;
    };

    
    void inversion(
        const std::string chromosomesIn[constants::populationSize],
        std::string chromosomesOut[constants::populationSize]
    ) noexcept;

};

#endif // MUTATION_HPP