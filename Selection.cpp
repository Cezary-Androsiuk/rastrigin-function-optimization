#include "Selection.hpp"


void Selection::_TournamentMethods::_min(
    const std::string chromosomesIn[constants::populationSize],
    const double functionOutputsIn[constants::populationSize],
    std::string chromosomesOut[constants::populationSize]
)
{
    constexpr uint groupSize = constants::groupSize;

    for(int i=0; i<constants::populationSize; i++)
    {
        std::string chromosome;
        double targetValue = __DBL_MAX__; // minimum part
        for(int j=0; j<groupSize; j++)
        {
            // ze zwracaniem
            uint randomIndex = static_cast<uint>(rand()) % constants::populationSize;
            if(functionOutputsIn[randomIndex] < targetValue) // minimum part
            {
                chromosome = chromosomesIn[randomIndex];
                targetValue = functionOutputsIn[randomIndex];
            }
        }
        chromosomesOut[i] = chromosome;
    }

}

void Selection::_TournamentMethods::_max(
    const std::string chromosomesIn[constants::populationSize],
    const double functionOutputsIn[constants::populationSize],
    std::string chromosomesOut[constants::populationSize]
)
{
    constexpr uint groupSize = constants::groupSize;

    for(int i=0; i<constants::populationSize; i++)
    {
        std::string chromosome;
        double targetValue = __DBL_MIN__; // maximum part
        for(int j=0; j<groupSize; j++)
        {
            // ze zwracaniem
            uint randomIndex = static_cast<uint>(rand()) % constants::populationSize;
            if(functionOutputsIn[randomIndex] > targetValue) // maximum part
            {
                chromosome = chromosomesIn[randomIndex];
                targetValue = functionOutputsIn[randomIndex];
            }
        }
        chromosomesOut[i] = chromosome;
    }
}


void Selection::tournament(
    const std::string chromosomesIn[constants::populationSize],
    const double functionOutputsIn[constants::populationSize],
    std::string chromosomesOut[constants::populationSize]
)
{
    constexpr uint groupSize = constants::groupSize;
    if(groupSize == 0 || groupSize >= constants::populationSize)
    {
        printf("error, input data are not valid: groupSize cant be 0 and need to be less than populationSize\n");
        exit(1);
    }

    if(constants::lookingFor) // maximum is 1, minimum is 0
        Selection::_TournamentMethods::_max(chromosomesIn, functionOutputsIn, chromosomesOut);
    else
        Selection::_TournamentMethods::_min(chromosomesIn, functionOutputsIn, chromosomesOut);
}















template <class T>
void Selection::_RankingMethods::_copy(
    const T in[constants::populationSize],
    T out[constants::populationSize]
)
{
    for(int i=0; i<constants::populationSize; i++)
        out[i] = in[i];
}

void Selection::_RankingMethods::_sort(
    const std::string chromosomesIn[constants::populationSize],
    const double functionOutputsIn[constants::populationSize],
    std::string chromosomesOut[constants::populationSize]
)
{
    double functionOutputsSort[constants::populationSize];

    Selection::_RankingMethods::_copy(chromosomesIn, chromosomesOut);
    Selection::_RankingMethods::_copy(functionOutputsIn, functionOutputsSort);

    for(int i=0; i<constants::populationSize; i++)
    {
        bool nothingChanged = true;
        for(int j=0; j<constants::populationSize-1; j++)
        {
            // constants::lookingFor;
            bool needChange = constants::lookingFor ? // maximum is 1, minimum is 0
                functionOutputsSort[j] < functionOutputsSort[j+1] : // descending  (3, 2, 1, 0, ...) looking for a Maximum
                functionOutputsSort[j] > functionOutputsSort[j+1] ; // ascending   (0, 1, 2, 3, ...) looking for a Minimum

            if(needChange)
            {
                std::string tmps = chromosomesOut[j];
                chromosomesOut[j] = chromosomesOut[j+1];
                chromosomesOut[j+1] = tmps;

                double tmpd = functionOutputsSort[j];
                functionOutputsSort[j] = functionOutputsSort[j+1];
                functionOutputsSort[j+1] = tmpd;

                nothingChanged = false;
            }
        }

        if(nothingChanged) // if nothing changed, then is sorted
            break;
    }
}

void Selection::ranking(
    const std::string chromosomesIn[constants::populationSize],
    const double functionOutputsIn[constants::populationSize],
    std::string chromosomesOut[constants::populationSize]
)
{
    std::string chromosomesSorted[constants::populationSize];
    Selection::_RankingMethods::_sort(chromosomesIn, functionOutputsIn, chromosomesSorted);

    for(int i=0; i<constants::populationSize; i++)
    {
        uint rnd1 = rand() % constants::populationSize;
        rnd1++; // can't be 0 and rnd1 value can be just like constants::populationSize for rnd2
        uint rnd2 = rand() % rnd1;
        chromosomesOut[i] = chromosomesSorted[rnd2];
    }
}










    
void Selection::roulette(
    const std::string chromosomesIn[constants::populationSize],
    const double functionOutputsIn[constants::populationSize],
    std::string chromosomesOut[constants::populationSize]
)
{
    constexpr uint popSize = constants::populationSize;

    double f[popSize]; // values of function output
    if(constants::lookingFor)// maximum is 1, minimum is 0
    {
        for(int i=0; i<popSize; i++)
            f[i] = functionOutputsIn[i];
    }
    else
    {
        // for minimum inverse values
        for(int i=0; i<popSize; i++)
            f[i] = 1/functionOutputsIn[i];
    }

    double F = 0; // sum function outputs
    for(int i=0; i<popSize; i++)
        F += f[i];

    double p[popSize]; // propability of chromosome depending on function output
    for(int i=0; i<popSize; i++)
        p[i] = f[i] / F;
    
    double q[popSize]; // distributor of propability
    for(int i=0; i<popSize; i++)
    {
        double pSum = 0;
        for(int j=0; j<i+1; j++)
        {
            pSum += p[j];
        }
        q[i] = pSum;
    }
    q[popSize-1] = 1; // correction

    // for(int i=0; i<popSize; i++)
    //     printf("%d F=% 10g, p=% 10g, q=% 10g\n", i, functionOutputsIn[i], p[i], q[i]);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(0.0, 1.0);

    for(int i=0; i<popSize; i++)
    {
        double randomValue = dis(gen);
        // printf("rnd: % 10g\n", randomValue);
        
        for(int j=0; j<popSize; j++)
        {
            if(randomValue < q[j])
            {
                // printf("found: q[%d] = % 10g\n", j, q[j]);
                chromosomesOut[j] = chromosomesIn[j];
                break;
            }
        }

    }
}