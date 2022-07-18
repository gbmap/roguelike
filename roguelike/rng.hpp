#pragma once
#include <random>
#include <functional>

namespace roguelike {
    typedef std::_Binder<
        std::remove_cv<std::_Unforced>::type, 
        std::uniform_int_distribution<int> &, 
        std::mt19937 &
    > GeneratorBind;

    class RNG {
    public:
        static int Rand();
    private:
        static RNG *instance;
        static RNG* GetInstance();

        std::uniform_int_distribution<int> distribution;
        std::mt19937 generator;
        GeneratorBind gen;

        RNG();
    };
}