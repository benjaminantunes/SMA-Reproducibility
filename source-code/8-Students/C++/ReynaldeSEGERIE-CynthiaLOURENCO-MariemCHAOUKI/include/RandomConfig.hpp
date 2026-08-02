#pragma once

#include <random>

// Singleton Patron

/**
 * @class RandomGenerator
 * @brief A class implementing the Singleton pattern for random number generation.
 *
 * This class provides a single instance of the Mersenne Twister random number generator
 * (std::mt19937) to ensure consistent and thread-safe random number generation throughout the program.
 */

class RandomGenerator
{
    private :
        unsigned int seed;

        RandomGenerator(unsigned int initialSeed) : seed(initialSeed){}

    public:
        /**
         * @brief Get the single instance of the random number generator.
         *
         * This static function returns a reference to the single instance of the random number generator.
         * If the instance does not exist, it will be created with a predefined seed (42).
         *
         * @return A reference to the single instance of std::mt19937 random number generator.
         */
        static std::mt19937& getInstance()
        {
            static std::mt19937 instance(5489); 
            return instance;
        }

        /**
         * @brief Get the single instance of the random number generator.
         *
         * This static function returns a reference to the single instance of the Linear Congruential Generator.
         * If the instance does not exist, it will be created with a predefined seed.
         *
         * @return A reference to the single instance of the Linear Congruential Generator.
         */
        static std::linear_congruential_engine<uint32_t, 1664525, 1013904223, 0>& getInstanceLCG()
        {
            static std::linear_congruential_engine<uint32_t, 1664525, 1013904223, 0> instance(5489); 
            return instance;
        }

        /**
         * @brief Get the single instance of the Middle Square random number generator.
         *
         * This static function returns a reference to the single instance of the Middle Square random number generator.
         * If the instance does not exist, it will be created with a predefined seed.
         *
         * @return A reference to the single instance of the Middle Square random number generator.
         */
        static RandomGenerator& getInstanceMS()
        {
            static RandomGenerator instance(675248); 
            return instance;
        }

        // Generate a random number using the Middle Square algorithm
        unsigned int generateRandom()
        {
            seed = (seed * seed) / 100 % 10000; 
            return seed;
        }

};

