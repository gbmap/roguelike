#ifndef GAME__H
#define GAME__H

#include <vector>
#include <thread>
#include <atomic>

#include "renderer.hpp"
#include "world.hpp"
#include "commands/command_handler.hpp"
#include "commands/command_poll.hpp"
#include "commands/roguelike_command.hpp"

namespace roguelike
{
    using namespace commands;

    class Roguelike
    {
    public:
        Roguelike(Renderer* pRenderer); 
        ~Roguelike(); 
        void StartSystems();
        void Render();
        void Exit();

        CommandPoll<RoguelikeCommand>* GetCommandPoll();

        World& GetWorld() { return world; };
    private:
        Renderer* renderer;
        World world;
        CommandPoll<RoguelikeCommand> command_poll;

        std::atomic<bool> should_exit;
        std::thread thread_update;
        std::thread thread_command;
        std::thread thread_world_command;

        void Update(const float& dt);
    };
}

#endif