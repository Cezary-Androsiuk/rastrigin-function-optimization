#ifndef GENERATE_HPP
#define GENERATE_HPP

#include <string>
#include <cstdio>
#include <cmath>

#include <unordered_set>
#include <random>

#include "constants.hpp"

namespace Generate{
    namespace _InternalMethods{
        bool isChromosomeValid(const std::string &chromosome, std::string chromosomes[constants::populationSize]);
    };

    void generateChromosomes(std::string chromosomes[constants::populationSize]);

    void generateFunctionValues(
        const std::string chromosomes[constants::populationSize], 
        double functionInputs[constants::populationSize][constants::n], 
        double functionOutputs[constants::populationSize]
    );
    
    void generateFunctionValues(
        const std::string chromosomes[constants::populationSize],  
        double functionOutputs[constants::populationSize]
    );

    void generateFunctionValues(
        cvstr chromosomes,
        std::vector<std::array<double, constants::n>> &functionInputs,
        std::vector<double> &functionOutputs
    );
    
    void generateFunctionValues(
        cvstr chromosomes,
        std::vector<double> &functionOutputs
    );
};

#endif // GENERATE_HPP