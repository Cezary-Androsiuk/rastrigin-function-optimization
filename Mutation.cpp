#include "Mutation.hpp"

bool Mutation::_InternalMethods::isChromosomeStillValid(const std::string &chromosome)
{
    // test if parts of chromosome is smaller, than max value
    ull startPos = 0;
    for(int i=0; i<constants::n; i++)
    {
        ull bitsCount = partOfChromosomeBitsRequired(i);
        ull generatedRandomValue = translateStringToBinary(chromosome.substr(startPos, bitsCount));
        ull maxChromosomeValue = partOfChromosomeMaxValue(i);
        if( generatedRandomValue > maxChromosomeValue )
        {
            // printf("  generated (%llu) is larger than max (%llu)\n", generatedRandomValue, maxChromosomeValue);
            // printf("retry\n");
            return false;
        }
        startPos += bitsCount;
    }

    return true;
}

char Mutation::_MutationMethods::mutateGen(char gen) noexcept
{
    return gen == '1' ? '0' : '1';
}

void Mutation::mutation(
    const std::string chromosomesIn[constants::populationSize],
    std::string chromosomesOut[constants::populationSize]
) noexcept
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(0.0, 1.0);

    for(int i=0; i<constants::populationSize; i++)
    {
        do{
            chromosomesOut[i].clear();

            // printf("in %s\n", chromosomesIn[i].c_str());
            for(const char c : chromosomesIn[i])
            {
                chromosomesOut[i].push_back(
                    dis(gen) < constants::mutationProbability ?
                    Mutation::_MutationMethods::mutateGen(c) : c
                );
            }
            // printf("out %s\n\n", chromosomesOut[i].c_str());
        }
        while(!Mutation::_InternalMethods::isChromosomeStillValid(chromosomesOut[i]));
    }
}

void Mutation::mutation(
    const std::string chromosomesIn[constants::populationSize],
    vstr &chromosomesOut
) noexcept
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(0.0, 1.0);

    std::string chromosomesTemporary[constants::populationSize];

    int j=0;
    for(int i=0; i<constants::populationSize; i++)
    {
        do{
            chromosomesTemporary[i].clear();

            // printf("in %s\n", chromosomesIn[i].c_str());
            for(const char c : chromosomesIn[i])
            {
                chromosomesTemporary[i].push_back(
                    dis(gen) < constants::mutationProbability ?
                    Mutation::_MutationMethods::mutateGen(c) : c
                );
            }
            j++;
            // printf("out %s\n\n", chromosomesTemporary[i].c_str());
        }
        while(!Mutation::_InternalMethods::isChromosomeStillValid(chromosomesTemporary[i]));
    }
    // fprintf(stderr, "j %d\n", j);

    for(int i=0; i<constants::populationSize; i++)
    {
        if(chromosomesTemporary[i] == chromosomesIn[i])
            continue;
        
        chromosomesOut.push_back(chromosomesTemporary[i]);
    }
}














std::string Mutation::_InversionMethods::inversePartOfChromosome(const std::string &chromosome) noexcept
{
    size_t m1 = rand() % chromosome.size();
    size_t m2 = rand() % chromosome.size();
    if(m1 == m2)
        return chromosome;

    if(m1 > m2)
    {
        size_t tmp = m1;
        m1 = m2;
        m2 = tmp;
    }

    std::string chromosomeOut;
    for(size_t i=0; i<chromosome.size(); i++)
    {
        size_t index;
        if(i >= m1 && i <= m2)
            index = m2 - i + m1;
        else
            index = i;
        
        chromosomeOut.push_back( chromosome[index] );
    }

    // printf("m1=%d, m2=%d\nin:  %s\nout: %s\n", m1, m2, chromosome.c_str(), chromosomeOut.c_str());
    return chromosomeOut;
}

void Mutation::inversion(
    const std::string chromosomesIn[constants::populationSize],
    std::string chromosomesOut[constants::populationSize]
) noexcept
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(0.0, 1.0);

    for(int i=0; i<constants::populationSize; i++)
    {
        bool inverseChromosome = dis(gen) < constants::inversionProbability;
        if(inverseChromosome)
        {
            chromosomesOut[i] = Mutation::_InversionMethods::inversePartOfChromosome(
                chromosomesIn[i]
            );
        }
        else
        {
            chromosomesOut[i] = chromosomesIn[i];
        }
    }

}


void Mutation::inversion(
    const std::string chromosomesIn[constants::populationSize],
    vstr &chromosomesOut
) noexcept
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(0.0, 1.0);
    
    for(int i=0; i<constants::populationSize; i++)
    {
        bool inverseChromosome = dis(gen) < constants::inversionProbability;
        if(!inverseChromosome)
            continue;

        chromosomesOut.push_back(
            Mutation::_InversionMethods::inversePartOfChromosome(
                chromosomesIn[i]
            )
        );
    }
}