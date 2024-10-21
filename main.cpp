#include <cstdio>
#include <string>
#include <ctime>

#include "constants.hpp"

#include "Selection.hpp"
#include "Generate.hpp"
#include "Mutation.hpp"


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


int main()
{
    srand(time(0));
    
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

    

    std::string selectedChromosomes[constants::populationSize];

    /// Selected Population - Tournament
    {
        Selection::tournament(chromosomes, functionOutputs, selectedChromosomes);
        Generate::generateFunctionValues(selectedChromosomes, functionInputs, functionOutputs);
        printf("\n" "selected population by tournament:\n");
        printData(selectedChromosomes, functionInputs, functionOutputs);
        printf("\n");
    }


    // /// Selected Population - Ranking
    // {
    //     Selection::ranking(chromosomes, functionOutputs, selectedChromosomes);
    //     Generate::generateFunctionValues(selectedChromosomes, functionInputs, functionOutputs);
        
    //     printf("\n" "selected population by ranking:\n");
    //     printData(selectedChromosomes, functionInputs, functionOutputs);
    //     printf("\n");
    // }


    /// Selected Population - Roulette
    {
        Selection::roulette(chromosomes, functionOutputs, selectedChromosomes);
        Generate::generateFunctionValues(selectedChromosomes, functionInputs, functionOutputs);
        
        printf("\n" "selected population by roulette:\n");
        printData(selectedChromosomes, functionInputs, functionOutputs);
        printf("\n");
    }

    
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
    
    printf("finished\n");
}



// jak posortować malejąco te dwie tablice porównując wartości względem functionOutputs?
// std::string chromosomes[constants::populationSize];
// double functionOutputs[constants::populationSize];