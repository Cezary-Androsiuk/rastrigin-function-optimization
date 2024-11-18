#ifndef SUCCESSION_HPP
#define SUCCESSION_HPP

#include <cstdio>
#include <string>
#include <random>
#include <vector>
#include <map>
#include <algorithm>

#include "constants.hpp"
#include "Generate.hpp"

namespace Succession
{
    namespace _InternalMethods{
        void combineChromosomes(
            const std::string chromosomesIn[constants::populationSize],
            cvstr chromosomesMutated,
            cvstr chromosomesInverted,
            cvstr chromosomesCrossbreed,
            vstr &chromosomesCombined
        ) noexcept;
    }

    namespace _EliteInternalMethods{
        void eliteMinimum(
            cvstr chromosomesCombined,
            const std::vector<double> &functionOutputs,
            std::string chromosomesOut[constants::populationSize]
        ) noexcept;
        
        void eliteMaximum(
            cvstr chromosomesCombined,
            const std::vector<double> &functionOutputs,
            std::string chromosomesOut[constants::populationSize]
        ) noexcept;
    }

    void elite(
        const std::string chromosomesIn[constants::populationSize],
        cvstr chromosomesMutated,
        cvstr chromosomesInverted,
        cvstr chromosomesCrossbreed,
        std::string chromosomesOut[constants::populationSize]
    ) noexcept;

    namespace _SqueezeInternalMethods{
        void removeOneOfNearestElements( std::multimap<double, std::string> &map ) noexcept;
        void printMap( const std::multimap<double, std::string> &map ) noexcept;
    }

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