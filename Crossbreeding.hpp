#ifndef CROSSBREEDING_HPP
#define CROSSBREEDING_HPP

#include <cstdio>
#include <string>
#include <random>
#include <vector>
#include <algorithm>

#include "constants.hpp"

namespace Crossbreeding
{
    namespace _InternalMethods
    {
        template <class T>
        void _copy(
            const T in[constants::populationSize],
            T out[constants::populationSize]
        ) noexcept;
        void _selection(
            const std::string chromosomesIn[constants::populationSize],
            vuint &selectedPairs

        ) noexcept;
    }

    namespace _MultipointMethods
    {
        void _randomUniqueNumbersSorted(
            const uint count, const uint range,
            vuint &randomNumers
        ) noexcept;

        void _crossbreadChromosomes(
            const std::string parents[2],
            std::string childs[2],
            const uint splitLines
        ) noexcept;
    }

    void multipoint(
        const std::string chromosomesIn[constants::populationSize],
        std::string chromosomesOut[constants::populationSize],
        const uint limitPoints = 0
    ) noexcept;

    void multipoint(
        const std::string chromosomesIn[constants::populationSize],
        vstr &chromosomesOut,
        const uint limitPoints = 0
    ) noexcept;


    namespace _EvenMethods
    {
        std::string _generateRandomBinaryChain(uint length) noexcept;

        void _crossbreadChromosomes(
            const std::string parents[2],
            std::string childs[2]
        ) noexcept;
    }

    void even(
        const std::string chromosomesIn[constants::populationSize],
        std::string chromosomesOut[constants::populationSize]
    ) noexcept;

    void even(
        const std::string chromosomesIn[constants::populationSize],
        vstr &chromosomesOut
    ) noexcept;

}

#endif // CROSSBREEDING_HPP