#include "Constants.hpp"


ull constPowULL(ull x, ull y) noexcept
{
    ull result = 1;
    while(y-- > 0) result *= x;
    return result;
}

ull partOfChromosomeMaxValue(uint i) noexcept 
{
    constexpr double d = constants::accuracy;
    double a = constants::ranges[i].a;
    double b = constants::ranges[i].b;

    // ! can overflow occur below
    return (b-a) * constPowULL(10, d) + 1;
}

uint partOfChromosomeBitsRequired(uint i) noexcept
{
    ull maxValue = partOfChromosomeMaxValue(i);

    uint m = 0;
    while(constPowULL(2, m++) < maxValue) {
        if(m > 64)
        {
            fprintf(stderr, "error: required %u bits per chunk of Chromosome, max that can be stored is 64 bits\n", m);
            exit(1);
        }
    }
    return m;
}

double function(double x_es[constants::n]) noexcept
{
    constexpr double A = constants::A;
    constexpr double omega = constants::omega;
    constexpr int n = constants::n;

    double result = A * n;
    for(int i=0; i<constants::n; i++)
        result += (x_es[i]*x_es[i]) - A * cos(omega * x_es[i]);
    
    return result;
}

ull translateStringToBinary(const std::string &string)
{
    ull power = 1;
    ull sum = 0;
    for(int i=0; i<string.size(); i++)
    {
        int index = string.size() -i -1;
        int value = string[index] - '0';
        if(value) sum += power;
        power *= 2;
    }
    return sum;
}