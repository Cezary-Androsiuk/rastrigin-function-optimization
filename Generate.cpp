#include "Generate.hpp"

bool Generate::_InternalMethods::isChromosomeValid(const std::string &chromosome, std::string chromosomes[constants::populationSize])
{
    // test if string already exist
    for(int i=0; i<constants::populationSize; i++)
    {
        if(chromosomes[i] == chromosome)
        {
            // printf("  duplicate of %s\n", chromosome.c_str());
            return false;
        }
    }

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
            return false;
        }
        startPos += bitsCount;
    }

    // printf("found duplicate\n");
    return true;
}


void Generate::generateChromosomes(std::string chromosomes[constants::populationSize])
{
    constexpr uint n = constants::n;
    constexpr uint populationSize = constants::populationSize;

    printf("generating chromosomes...");

    // generate random strings
    uint chromosomeLength = 0;
    for(int i=0; i<n; i++)
        chromosomeLength += partOfChromosomeBitsRequired(i);

    for(int i=0; i<populationSize; i++)
    {
        std::string chromosome;
        chromosome.reserve(chromosomeLength);

        // random :<
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist('0', '1');

        do{
            chromosome.clear();

            for (int i=0; i<chromosomeLength; ++i)
                chromosome.push_back(dist(gen));

            // printf("  found value %s\n", chromosome.c_str());

        } while(!Generate::_InternalMethods::isChromosomeValid(chromosome, chromosomes));

        // printf("value is valid\n");

        chromosomes[i] = chromosome;
    }
    
    printf("\r" "chromosomes generated!   \n");
    
}

void Generate::generateFunctionValues(
    const std::string chromosomes[constants::populationSize], 
    double functionInputs[constants::populationSize][constants::n], 
    double functionOutputs[constants::populationSize]
)
{
    printf("generating function values...");
    for(int i=0; i<constants::populationSize; i++)
    {
        ull readedGens = 0;
        for(int j=0; j<constants::n; j++)
        {
            ull m = partOfChromosomeBitsRequired(j);
            std::string partOfChromosome = chromosomes[i].substr(readedGens, m);
            readedGens += m;

            ull partOfChromosomeValue = translateStringToBinary(partOfChromosome);

            double rangeSize = constants::ranges[j].b - constants::ranges[j].a;
            double valuePossibilities = (pow(2, m) - 1); // how much values can be represented by this partOfChromosome
            double ratio = (rangeSize * partOfChromosomeValue) / valuePossibilities;
            double normalizedFunctionArgument = constants::ranges[j].a + ratio;
            
            functionInputs[i][j] = normalizedFunctionArgument;
        }

        functionOutputs[i] = function(functionInputs[i]);
    }
    printf("\r" "function values generated!   \n");
}