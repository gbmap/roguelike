
#include "roguelike_command.hpp"

#include "../roguelike.hpp"
#include <iostream>

namespace roguelike::commands {
    void RoguelikeKeyCommand::Execute(Roguelike& roguelike) {
        std::cout << "Key pressed " << (char)key << std::endl;
    }

    void RoguelikeExitCommand::Execute(Roguelike& roguelike) {
        std::cout << "Exiting..." << std::endl;
        roguelike.Exit();
    }

}