#pragma once

/*
Engine commands.
*/

#include "command.hpp"
namespace roguelike {
    class Roguelike;
    namespace commands {
        class RoguelikeCommand : public commands::Command {
        public:
            virtual void Execute(Roguelike& roguelike) = 0;
        };

        class RoguelikeKeyCommand : public RoguelikeCommand {
        public:
            RoguelikeKeyCommand(int key) : key(key) {}
            void Execute(Roguelike& roguelike) override;
        private:
            int key;
        };

        class RoguelikeExitCommand : public RoguelikeCommand {
        public:
            void Execute(Roguelike& roguelike) override;
        };
    }
}