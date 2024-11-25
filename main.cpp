#include <cstdio>
#include <string>
#include <ctime>

#include "constants.hpp"

#include "Selection.hpp"
#include "Generate.hpp"
#include "Mutation.hpp"
#include "Crossbreeding.hpp"
#include "Succession.hpp"

void printData(
    const std::string chromosomes[constants::populationSize], 
    const double functionInputs[constants::populationSize][constants::n], 
    const double functionOutputs[constants::populationSize]
)
{
    for(int i=0; i<constants::populationSize; i++)
    {
        printf("chromosome: %s,    ", chromosomes[i].c_str());
        
        printf("F(");
        for(int j=0; j<constants::n; j++)
            printf("% 16g ", functionInputs[i][j]);
            // printf("%g%s", functionInputs[i][j], j+1!=constants::n ? ", " : "");
        printf(")");

        printf(" = % 10g\n", functionOutputs[i]);
    }
}

void printData(
    cvstr chromosomes,
    const std::vector<std::array<double, constants::n>> &functionInputs,
    const std::vector<double> &functionOutputs
)
{
    for(int i=0; i<chromosomes.size(); i++)
    {
        printf("chromosome: %s,    ", chromosomes[i].c_str());
        
        printf("F(");
        for(int j=0; j<constants::n; j++)
            printf("% 16g ", functionInputs[i][j]);
            // printf("%g%s", functionInputs[i][j], j+1!=constants::n ? ", " : "");
        printf(")");

        printf(" = % 10g\n", functionOutputs[i]);
    }
}

void printData(const std::string chromosomes[constants::populationSize])
{
    double functionInputs[constants::populationSize][constants::n];
    double functionOutputs[constants::populationSize];

    Generate::generateFunctionValues(chromosomes, functionInputs, functionOutputs);

    printf("\n" "generated values:\n");
    printData(chromosomes, functionInputs, functionOutputs);
    printf("\n");
}

void printDataSummary(const std::string chromosomes[constants::populationSize])
{
    double functionInputs[constants::populationSize][constants::n];
    double functionOutputs[constants::populationSize];

    Generate::generateFunctionValues(chromosomes, functionInputs, functionOutputs);

    double sum=0;
    double max=__DBL_MIN__;
    double min=__DBL_MAX__;

    for(int i=0; i<constants::populationSize; i++)
    {
        double value = functionOutputs[i];
        if(max<value) max = value;
        if(min>value) min = value;
        sum += value;
    }
    double mean = sum / static_cast<double>(constants::populationSize);

    printf("\n" "mean: %g, max: %g, min: %g\n", mean, max, min);
}

void runFunctions()
{
    std::string chromosomes[constants::populationSize];

    double functionInputs[constants::populationSize][constants::n];
    double functionOutputs[constants::populationSize];

    /// Random Population
    {
        Generate::generateChromosomes(chromosomes);
        Generate::generateFunctionValues(chromosomes, functionInputs, functionOutputs);

        printf("\n" "generated values:\n");
        printData(chromosomes, functionInputs, functionOutputs);
        printf("\n");
    }

    /// Selection
    {
        std::string selectedChromosomes[constants::populationSize];

        /// Selected Population - Tournament
        {
            Selection::tournament(chromosomes, functionOutputs, selectedChromosomes);
            Generate::generateFunctionValues(selectedChromosomes, functionInputs, functionOutputs);
            printf("\n" "selected population by tournament:\n");
            printData(selectedChromosomes, functionInputs, functionOutputs);
            printf("\n");
        }

        /// Selected Population - Ranking
        {
            Selection::ranking(chromosomes, functionOutputs, selectedChromosomes);
            Generate::generateFunctionValues(selectedChromosomes, functionInputs, functionOutputs);
            
            printf("\n" "selected population by ranking:\n");
            printData(selectedChromosomes, functionInputs, functionOutputs);
            printf("\n");
        }

        /// Selected Population - Roulette
        {
            Selection::roulette(chromosomes, functionOutputs, selectedChromosomes);
            Generate::generateFunctionValues(selectedChromosomes, functionInputs, functionOutputs);
            
            printf("\n" "selected population by roulette:\n");
            printData(selectedChromosomes, functionInputs, functionOutputs);
            printf("\n");
        }
    }
    
    /// Mutation
    {
        std::string mutatedChromosomes[constants::populationSize];

        /// Mutated Population - Mutation
        {
            Mutation::mutation(chromosomes ,mutatedChromosomes);
            Generate::generateFunctionValues(mutatedChromosomes, functionInputs, functionOutputs);
            
            printf("\n" "mutated population by mutation:\n");
            printData(mutatedChromosomes, functionInputs, functionOutputs);
            printf("\n");
        }

        /// Mutated Population - Inversion
        {
            Mutation::inversion(chromosomes ,mutatedChromosomes);
            Generate::generateFunctionValues(mutatedChromosomes, functionInputs, functionOutputs);
            
            printf("\n" "mutated population by inversion:\n");
            printData(mutatedChromosomes, functionInputs, functionOutputs);
            printf("\n");
        }
    }

    /// Crossbreeding
    {
        std::string crossbredChromosomes[constants::populationSize];

        /// Crossbred Population - Single Point
        {
            printf("\n" "crossbred population by single point:\n");

            Crossbreeding::multipoint(chromosomes, crossbredChromosomes, 1);
            Generate::generateFunctionValues(crossbredChromosomes, functionInputs, functionOutputs);

            printData(crossbredChromosomes, functionInputs, functionOutputs);
            printf("\n");
        }
        
        /// Crossbred Population - Double Point
        {
            printf("\n" "crossbred population by double point:\n");

            Crossbreeding::multipoint(chromosomes, crossbredChromosomes, 2);
            Generate::generateFunctionValues(crossbredChromosomes, functionInputs, functionOutputs);

            printData(crossbredChromosomes, functionInputs, functionOutputs);
            printf("\n");
        }
        
        /// Crossbred Population - Multi Point
        {
            printf("\n" "crossbred population by Multi point:\n");

            Crossbreeding::multipoint(chromosomes, crossbredChromosomes, 0);
            Generate::generateFunctionValues(crossbredChromosomes, functionInputs, functionOutputs);

            printData(crossbredChromosomes, functionInputs, functionOutputs);
            printf("\n");
        }

        /// Crossbred Population - Even Crossing
        {
            printf("\n" "crossbred population by even crossing:\n");
            Crossbreeding::even(chromosomes, crossbredChromosomes);
            Generate::generateFunctionValues(crossbredChromosomes, functionInputs, functionOutputs);

            printData(crossbredChromosomes, functionInputs, functionOutputs);
            printf("\n");
        }
    }
    
    /// For Epochs...
    {
        vstr mutatedChromosomes;
        std::vector<std::array<double, constants::n>> functionInputs;
        std::vector<double> functionOutputs;

        /// Mutated Population - Mutation
        {
            Mutation::mutation(chromosomes ,mutatedChromosomes);
            Generate::generateFunctionValues(mutatedChromosomes, functionInputs, functionOutputs);
            
            printf("\n" "mutated population by mutation:\n");
            printData(mutatedChromosomes, functionInputs, functionOutputs);
            printf("\n");
        }


        /// Mutated Population - Inversion
        {
            Mutation::inversion(chromosomes ,mutatedChromosomes);
            Generate::generateFunctionValues(mutatedChromosomes, functionInputs, functionOutputs);
            
            printf("\n" "mutated population by inversion:\n");
            printData(mutatedChromosomes, functionInputs, functionOutputs);
            printf("\n");
        }
        

        vstr crossbredChromosomes;

        /// Crossbred Population - Double Point
        {
            printf("\n" "crossbred population by Double point:\n");

            Crossbreeding::multipoint(chromosomes, crossbredChromosomes, 2);
            Generate::generateFunctionValues(crossbredChromosomes, functionInputs, functionOutputs);

            printData(crossbredChromosomes, functionInputs, functionOutputs);
            printf("\n");
        }
    }
}


void launchTrivialEpochs()
{
    std::string chromosomes[constants::populationSize];

    /// Random Population
    {
        Generate::generateChromosomes(chromosomes);
        printData(chromosomes);
    }
    
    for(int i=0; i<100; i++)
    {
        fprintf(stderr, "epoch: %d\n", i+1);
        printf("epoch: %d\n", i+1);
        std::string selectedChromosomes[constants::populationSize];
        
        double functionOutputs[constants::populationSize];
        Generate::generateFunctionValues(chromosomes, functionOutputs);

        fprintf(stderr, "tournament:\n");
        Selection::ranking(chromosomes, functionOutputs, selectedChromosomes);

        std::string chromosomesMutated[constants::populationSize];
        fprintf(stderr, "mutation:\n");
        Mutation::mutation(selectedChromosomes, chromosomesMutated);
        
        std::string chromosomesInverted[constants::populationSize];
        fprintf(stderr, "inversion:\n");
        Mutation::inversion(chromosomesMutated, chromosomesInverted);

        fprintf(stderr, "multipoint:\n");
        Crossbreeding::multipoint(chromosomesInverted, chromosomes, 5);

        printData(chromosomes);
        
    }
}

void launchEpochs(int epochs)
{
    std::string chromosomes[constants::populationSize];

    /// Random Population
    {
        Generate::generateChromosomes(chromosomes);
        // printData(chromosomes);
    }
    double epochsSum = 0;
    for(int i=0; i<epochs; i++)
    {
        fprintf(stderr, "epoch: %d/%d\n", i+1, epochs);
        // printf("epoch: %d\n", i+1);
        std::string selectedChromosomes[constants::populationSize]; // used by mutation and crossbreeding
        
        double functionOutputs[constants::populationSize];
        Generate::generateFunctionValues(chromosomes, functionOutputs);

        // fprintf(stderr, "tournament:\n");
        Selection::tournament(chromosomes, functionOutputs, selectedChromosomes);


        vstr chromosomesMutated;
        // fprintf(stderr, "mutation:\n");
        Mutation::mutation(selectedChromosomes, chromosomesMutated);
        
        vstr chromosomesInverted;
        // fprintf(stderr, "inversion:\n");
        Mutation::inversion(selectedChromosomes, chromosomesInverted);

        vstr chromosomesCrossbred;
        // fprintf(stderr, "multipoint:\n");
        Crossbreeding::multipoint(selectedChromosomes, chromosomesCrossbred, 1);

        // fprintf(stderr, "elite:\n");
        Succession::elite(chromosomes, chromosomesMutated, chromosomesInverted, chromosomesCrossbred, chromosomes);
        // output can be the same array as input, because array is copied before any changes on it
        

        double functionOutputs2[constants::populationSize];

        Generate::generateFunctionValues(chromosomes, functionOutputs2);

        double sum=0;
        // double max=__DBL_MIN__;
        // double min=__DBL_MAX__;

        for(int i=0; i<constants::populationSize; i++)
        {
            // double value = functionOutputs2[i];
            // if(max<value) max = value;
            // if(min>value) min = value;
            sum += functionOutputs2[i];
        }
        double mean = sum / static_cast<double>(constants::populationSize);
        epochsSum += mean;
        // printf("\n" "mean: %g, max: %g, min: %g\n", mean, max, min);

        // printDataSummary(chromosomes);
    }
    double epochsMean = epochsSum / static_cast<double>(epochs);
    printf("\n" "populationSize: %d, epochs: %d, mean: %g\n", constants::populationSize, epochs, epochsMean);
}

int main()
{
    srand(time(0));
    
    // runFunctions();
    
    // launchTrivialEpochs();

    int epochs[6] = {10, 50, 100, 200, 500, 1000};
    for(int i=0; i<6; i++)
        launchEpochs(epochs[i]);

    

    printf("finished\n");
}
