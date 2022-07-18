#include "rng.hpp"

namespace roguelike {
    RNG* RNG::instance = nullptr;
    int RNG::Rand() {
        return GetInstance()->gen();
    }
    
    RNG* RNG::GetInstance() {
        if (!instance) {
            instance = new RNG();
        }
        return instance;
    }

    RNG::RNG() 
        : distribution(0, 100), 
          generator(), 
          gen(std::bind(distribution, generator)) {}
}