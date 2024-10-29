#include "Crossbreeding.hpp"



template <class T>
void Crossbreeding::_InternalMethods::_copy(
    const T in[constants::populationSize],
    T out[constants::populationSize]
) noexcept
{
    for(int i=0; i<constants::populationSize; i++)
        out[i] = in[i];
}

void Crossbreeding::_InternalMethods::_selection(
    const std::string chromosomesIn[constants::populationSize],
    vuint &selectedPairs

) noexcept
{
    constexpr double icp = constants::involvementCrossbreedingProbability;
    constexpr uint popSize = constants::populationSize;
    
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(0.0, 1.0);

    selectedPairs.clear();
    for(int i=0; i<popSize; i++)
    {
        double randomValue = dis(gen);
        if(randomValue >= icp)
            continue;

        selectedPairs.push_back(i);
    }

    std::shuffle(selectedPairs.begin(), selectedPairs.end(), gen); // important stuff to keep random at this point

    if(selectedPairs.size()%2 == 0)
        return;
        
    // remove odd chromosome
    selectedPairs.pop_back();
        
    if(selectedPairs.empty())
    {
        printf("warning: no chromosomes was choosed for crossbreeding\n");
    }
    
}









void Crossbreeding::_MultipointMethods::_randomUniqueNumbersSorted(
    const uint count, const uint range,
    vuint &randomNumers
) noexcept
{
    std::vector<int> numbers(range);
    for (int i=0; i<range; ++i) 
        numbers[i] = i + 1;

    // shuffle
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(numbers.begin(), numbers.end(), gen);

    // select n first numbers
    randomNumers.clear();
    randomNumers.assign(numbers.begin(), numbers.begin() + count);
    std::sort(randomNumers.begin(), randomNumers.end());
}

void Crossbreeding::_MultipointMethods::_crossbreadChromosomes(
    const std::string parents[2],
    std::string childs[2],
    const uint splitLinesCount
) noexcept
{
    const uint chromosomesSize = parents[0].size();
    vuint splitLines;
    _randomUniqueNumbersSorted(splitLinesCount, chromosomesSize-1, splitLines);

    // printf("parent1: %s\n", parents[0].c_str());
    // printf("parent2: %s\n", parents[1].c_str());

    // for(uint splitLine : splitLines)
    //     printf("splitLine: %u\n", splitLine);

    // create child 1 
    bool useOriginalParent = true;
    uint lastChangedIndex = 0;

    childs[0].clear();
    for(int i=0; i<parents[0].size(); i++)
    {
        for(int j=0; j<splitLinesCount; j++)
        {
            if(splitLines[j] <= lastChangedIndex)
                continue;
            if(i < splitLines[j])
                continue;

            lastChangedIndex = splitLines[j];
            useOriginalParent = !useOriginalParent;
        }

        // printf("index: %d, get: %c, original: %s\n", i, parents[ useOriginalParent? 0:1 ][i], useOriginalParent?"true":"false");
        childs[0].push_back(
            parents[ useOriginalParent? 0:1 ][i]
        );
    }
    // printf("generated child 1: %s\n", childs[0].c_str());


    // create child 2
    useOriginalParent = true;
    lastChangedIndex = 0;
    
    childs[1].clear();
    for(int i=0; i<parents[1].size(); i++)
    {
        for(int j=0; j<splitLinesCount; j++)
        {
            if(splitLines[j] <= lastChangedIndex)
                continue;
            if(i < splitLines[j])
                continue;

            lastChangedIndex = splitLines[j];
            useOriginalParent = !useOriginalParent;
        }

        // printf("index: %d, get: %c, original: %s\n", i, parents[ useOriginalParent? 1:0 ][i], useOriginalParent?"true":"false");
        childs[1].push_back( 
            parents[ useOriginalParent? 1:0 ][i]
        );
    }
    
    // printf("generated child 2: %s\n", childs[1].c_str());
}


void Crossbreeding::multipoint(
    const std::string chromosomesIn[constants::populationSize],
    std::string chromosomesOut[constants::populationSize],
    const uint limitPoints
) noexcept
{
    const uint chromosomesSize = chromosomesIn[0].size();
    uint splitLinesCount;
    if(limitPoints >= chromosomesSize)
    {
        splitLinesCount = chromosomesSize-1;
        printf("warning: limitPoints is %u, but should be smaller than chromosomes size, which is %u."
        " Set splitLinesCount as %u\n", limitPoints, chromosomesSize, chromosomesSize-1);
    }
    else if(limitPoints == 0)
        splitLinesCount = (rand()%(chromosomesSize-1)) + 1;
    else 
        splitLinesCount = limitPoints;
    // printf("choosed splitLinesCount: %u\n", splitLinesCount);

    vuint selectedForCrossbreeding;
    _InternalMethods::_selection(chromosomesIn, selectedForCrossbreeding);
    // printf("selected indexes for crossbreeding:\n");
    // for(uint chromosomeIndex : selectedForCrossbreeding)
    //     printf("%u, ", chromosomeIndex);
    // printf("\n");

    _InternalMethods::_copy(chromosomesIn, chromosomesOut);

    uint pairsCount = selectedForCrossbreeding.size() /2;
    for(int i=0; i<pairsCount; i+=2)
    {
        uint index1 = selectedForCrossbreeding[i];
        uint index2 = selectedForCrossbreeding[i+1];

        const std::string parents[2] = {chromosomesIn[index1], chromosomesIn[index2]};
        std::string childs[2];

        _MultipointMethods::_crossbreadChromosomes(parents, childs, splitLinesCount);

        chromosomesOut[index1] = childs[0];
        chromosomesOut[index2] = childs[1];
    }

}


















std::string Crossbreeding::_EvenMethods::_generateRandomBinaryChain(uint length) noexcept
{
    std::string randomBinaryChain;
    randomBinaryChain.reserve(length);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist('0', '1');
    for(int i=0; i<length; i++)
        randomBinaryChain.push_back(dist(gen));

    return randomBinaryChain;
}

void Crossbreeding::_EvenMethods::_crossbreadChromosomes(
    const std::string parents[2],
    std::string childs[2]
) noexcept
{
    // printf("parent1: %s\n", parents[0].c_str());
    // printf("parent2: %s\n", parents[1].c_str());

    std::string randomBinaryChain = _generateRandomBinaryChain(parents[0].size());
    // printf("generated random binary string: %s\n", randomBinaryChain.c_str());

    // create child 1
    for(int i=0; i<parents[0].size(); i++)
    {
        bool useOriginalParent = randomBinaryChain[i] == '0';
        childs[0].push_back(
            parents[ useOriginalParent? 0:1 ][i]
        );
    }
    // printf("generated child 1: %s\n", childs[0].c_str());
    
    // create child 1
    for(int i=0; i<parents[1].size(); i++)
    {
        bool useOriginalParent = randomBinaryChain[i] == '0';
        childs[1].push_back(
            parents[ useOriginalParent? 1:0 ][i]
        );
    }
    // printf("generated child 2: %s\n", childs[1].c_str());

}

void Crossbreeding::even(
    const std::string chromosomesIn[constants::populationSize],
    std::string chromosomesOut[constants::populationSize]
) noexcept
{
    vuint selectedForCrossbreeding;
    _InternalMethods::_selection(chromosomesIn, selectedForCrossbreeding);

    _InternalMethods::_copy(chromosomesIn, chromosomesOut);
    
    uint pairsCount = selectedForCrossbreeding.size() /2;
    for(int i=0; i<pairsCount; i+=2)
    {
        uint index1 = selectedForCrossbreeding[i];
        uint index2 = selectedForCrossbreeding[i+1];

        const std::string parents[2] = {chromosomesIn[index1], chromosomesIn[index2]};
        std::string childs[2];

        _EvenMethods::_crossbreadChromosomes(parents, childs);

        chromosomesOut[index1] = childs[0];
        chromosomesOut[index2] = childs[1];
    }
}