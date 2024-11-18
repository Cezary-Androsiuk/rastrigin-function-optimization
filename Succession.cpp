#include "Succession.hpp"

void Succession::_InternalMethods::combineChromosomes(
    const std::string chromosomesIn[constants::populationSize],
    cvstr chromosomesMutated,
    cvstr chromosomesInverted,
    cvstr chromosomesCrossbreed,
    vstr &chromosomesCombined
) noexcept
{
    constexpr uint popSize = constants::populationSize;

    chromosomesCombined.clear();
    const uint chromosomesContainerSize = popSize + chromosomesMutated.size() + 
        chromosomesInverted.size() + chromosomesCrossbreed.size();

    chromosomesCombined.reserve(chromosomesContainerSize);


    // add chromosomesIn to chromosomesCombined
    for(int i=0; i<constants::populationSize; i++)
        chromosomesCombined.push_back(chromosomesIn[i]);

    // add chromosomesMutated to chromosomesCombined
    for(const auto &chromosome : chromosomesMutated)
        chromosomesCombined.push_back(chromosome);
    
    // add chromosomesInverted to chromosomesCombined
    for(const auto &chromosome : chromosomesInverted)
        chromosomesCombined.push_back(chromosome);
    
    // add chromosomesCrossbreed to chromosomesCombined
    for(const auto &chromosome : chromosomesCrossbreed)
        chromosomesCombined.push_back(chromosome);
    
}






void Succession::_EliteInternalMethods::eliteMinimum(
    cvstr chromosomesCombined,
    const std::vector<double> &functionOutputs,
    std::string chromosomesOut[constants::populationSize]
) noexcept
{
    //  auto sorts itself in ascending order (firsts elements are the smallest)
    std::multimap<double, std::string> map;

    for(int i=0; i<chromosomesCombined.size(); i++)
    {
        map.emplace(functionOutputs[i], chromosomesCombined[i]);
    }

    /// emplace first [constant::populationSize] chromosomes to chromosomesOut
    int i=0;
    for(const auto &[functionOut, chromosome] : map)
    {
        chromosomesOut[i] = chromosome;

        if(++i >= constants::populationSize)
            break;
    }
}

void Succession::_EliteInternalMethods::eliteMaximum(
    cvstr chromosomesCombined,
    const std::vector<double> &functionOutputs,
    std::string chromosomesOut[constants::populationSize]
) noexcept
{
    //  auto sorts itself in descending order (firsts elements are the largest)
    std::multimap<double, std::string, std::greater<double>> map; 

    for(int i=0; i<chromosomesCombined.size(); i++)
    {
        map.emplace(functionOutputs[i], chromosomesCombined[i]);
    }

    /// emplace first [constant::populationSize] chromosomes to chromosomesOut
    int i=0;
    for(const auto &[functionOut, chromosome] : map)
    {
        chromosomesOut[i] = chromosome;

        if(++i >= constants::populationSize)
            break;
    }
}

void Succession::elite(
    const std::string chromosomesIn[constants::populationSize],
    cvstr chromosomesMutated,
    cvstr chromosomesInverted,
    cvstr chromosomesCrossbreed,
    std::string chromosomesOut[constants::populationSize]
) noexcept
{
    vstr chromosomesCombined;
    _InternalMethods::combineChromosomes(
        chromosomesIn, chromosomesMutated, chromosomesInverted, chromosomesCrossbreed, 
        chromosomesCombined);
        
    std::vector<double> functionOutputs;

    Generate::generateFunctionValues(chromosomesCombined, functionOutputs);

    if(constants::lookingFor == Target::Maximum)
        _EliteInternalMethods::eliteMaximum(chromosomesCombined, functionOutputs, chromosomesOut);
    else
        _EliteInternalMethods::eliteMinimum(chromosomesCombined, functionOutputs, chromosomesOut);
    

}







void Succession::_SqueezeInternalMethods::removeOneOfNearestElements(
    std::multimap<double, std::string> &map
) noexcept
{
    if(map.size()<2)
    {
        fprintf(stderr, "map is to small\n");
        return;
    }

    int lowIndex1 = 0;
    auto it1 = map.begin();
    auto it2 = map.begin(); it2++;
    double smallestDiff = it2->first - it1->first; // while computing shouldn't go below 0

    for(int i=0; i<map.size()-1; i++)
    {
        double diff = it2->first - it1->first;
        if(smallestDiff > diff)
        {
            smallestDiff = diff;
            lowIndex1 = i;
        }
        
        it1++; it2++;
    }

    int deleteIndex = rand()%2 ? lowIndex1 : (lowIndex1 +1 /* second index  */);
    auto deleteIt = map.begin();
    std::advance(deleteIt, deleteIndex);
    map.erase(deleteIt);
}

void printMap(const std::multimap<double, std::string> &map ) noexcept
{
    for(const auto &[functionValue, chromosome] : map)
        printf("%s : %g\n", chromosome.c_str(), functionValue);
}

void Succession::squeeze(
    const std::string chromosomesIn[constants::populationSize],
    cvstr chromosomesMutated,
    cvstr chromosomesInverted,
    cvstr chromosomesCrossbreed,
    std::string chromosomesOut[constants::populationSize]
) noexcept
{
    vstr chromosomesCombined;
    _InternalMethods::combineChromosomes(
        chromosomesIn, chromosomesMutated, chromosomesInverted, chromosomesCrossbreed, 
        chromosomesCombined);

    std::vector<double> functionOutputs;

    Generate::generateFunctionValues(chromosomesCombined, functionOutputs);

    //  auto sorts itself in ascending order (firsts elements are the smallest)
    std::multimap<double, std::string> map; // order is not important

    for(int i=0; i<chromosomesCombined.size(); i++)
    {
        map.emplace(functionOutputs[i], chromosomesCombined[i]);
    }

    // squeeze until [constants::populationSize] values is left
    while(map.size() > constants::populationSize)
    {
        // printMap(map);
        // printf("\n");
        _SqueezeInternalMethods::removeOneOfNearestElements(map);
    }

    // printf("final: \n");
    // printMap(map);
    
    auto mapIt = map.begin();
    for(int i=0; i<constants::populationSize; i++)
    {
        chromosomesOut[i] = mapIt->second;
        mapIt++;
    }
}











void Succession::random(
    const std::string chromosomesIn[constants::populationSize],
    cvstr chromosomesMutated,
    cvstr chromosomesInverted,
    cvstr chromosomesCrossbreed,
    std::string chromosomesOut[constants::populationSize]
) noexcept
{
    vstr chromosomesCombined;
    _InternalMethods::combineChromosomes(
        chromosomesIn, chromosomesMutated, chromosomesInverted, chromosomesCrossbreed, 
        chromosomesCombined);

    std::random_device rd;
    std::mt19937 gen(rd());

    // randomize elements
    std::shuffle(chromosomesCombined.begin(), chromosomesCombined.end(), gen);

    for(int i=0; i<constants::populationSize; i++)
        chromosomesOut[i] = chromosomesCombined[i];
}