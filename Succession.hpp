#ifndef SUCCESSION_HPP
#define SUCCESSION_HPP

#include <cstdio>
#include <string>
#include <random>
#include <vector>

#include "constants.hpp"

namespace Succession
{
    void elite(
        const std::string chromosomesIn[constants::populationSize],
        cvstr chromosomesMutated,
        cvstr chromosomesInverted,
        cvstr chromosomesCrossbreed,
        std::string chromosomesOut[constants::populationSize]
    ) noexcept;

    void squeeze(
        const std::string chromosomesIn[constants::populationSize],
        cvstr chromosomesMutated,
        cvstr chromosomesInverted,
        cvstr chromosomesCrossbreed,
        std::string chromosomesOut[constants::populationSize]
    ) noexcept;

    void random(
        const std::string chromosomesIn[constants::populationSize],
        cvstr chromosomesMutated,
        cvstr chromosomesInverted,
        cvstr chromosomesCrossbreed,
        std::string chromosomesOut[constants::populationSize]
    ) noexcept;

}

#endif // SUCCESSION_HPP