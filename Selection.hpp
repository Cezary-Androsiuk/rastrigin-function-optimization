#ifndef SELECTION_HPP
#define SELECTION_HPP

#include <string>
#include <random>

#include "constants.hpp"

namespace Selection{
    namespace _TournamentMethods{

        void _min(
            const std::string chromosomesIn[constants::populationSize],
            const double functionOutputsIn[constants::populationSize],
            std::string chromosomesOut[constants::populationSize]
        );
        
        void _max(
            const std::string chromosomesIn[constants::populationSize],
            const double functionOutputsIn[constants::populationSize],
            std::string chromosomesOut[constants::populationSize]
        );

    };

    void tournament(
        const std::string chromosomesIn[constants::populationSize],
        const double functionOutputsIn[constants::populationSize],
        std::string chromosomesOut[constants::populationSize]
    );


    namespace _RankingMethods{
        
        template <class T>
        void _copy(
            const T in[constants::populationSize],
            T out[constants::populationSize]
        );

        void _sort(
            const std::string chromosomesIn[constants::populationSize],
            const double functionOutputsIn[constants::populationSize],
            std::string chromosomesOut[constants::populationSize]
        );

    };

    void ranking(
        const std::string chromosomesIn[constants::populationSize],
        const double functionOutputsIn[constants::populationSize],
        std::string chromosomesOut[constants::populationSize]
    );


    namespace _RouletteMethods{

    };
    
    void roulette(
        const std::string chromosomesIn[constants::populationSize],
        const double functionOutputsIn[constants::populationSize],
        std::string chromosomesOut[constants::populationSize]
    );
};

#endif // SELECTION_HPP