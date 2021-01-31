#ifndef BELL_RANDOM_H
#define BELL_RANDOM_H

#include <random>

class Random
{
public:
    /**
     * @brief Initializes the random engine with a random seed
     * 
     */
    static void Init()
    {
        s_RandomEngine.seed(std::random_device()());
    }

    /**
     * @brief Gets a random float
     * 
     * @return float Randomized float
     */
    static float Float()
    {
        return (float)s_Distribution(s_RandomEngine) / (float)std::numeric_limits<uint32_t>::max();
    }

private:
    static std::mt19937 s_RandomEngine;
    static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
};

#endif // !_RANDOM_H