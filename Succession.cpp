#include "Succession.hpp"

void Succession::elite(
    const std::string chromosomesIn[constants::populationSize],
    cvstr chromosomesMutated,
    cvstr chromosomesInverted,
    cvstr chromosomesCrossbreed,
    std::string chromosomesOut[constants::populationSize]
) noexcept
{
    
}

void Succession::squeeze(
    const std::string chromosomesIn[constants::populationSize],
    cvstr chromosomesMutated,
    cvstr chromosomesInverted,
    cvstr chromosomesCrossbreed,
    std::string chromosomesOut[constants::populationSize]
) noexcept
{
    vstr chromosomes;
    // sort

    // powtarzaj do momentu gdy chromosomes.size() == constants::populationSize
        // znajdż najmniejszą różnicę w funkcji między dwoma chromosomami
        // usuń losowy z nich
}

void Succession::random(
    const std::string chromosomesIn[constants::populationSize],
    cvstr chromosomesMutated,
    cvstr chromosomesInverted,
    cvstr chromosomesCrossbreed,
    std::string chromosomesOut[constants::populationSize]
) noexcept
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(false, true);
    dist(gen);
}