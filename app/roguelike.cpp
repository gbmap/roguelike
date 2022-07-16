#include "roguelike.hpp"
#include "world.hpp"
#include "commands/world_command.hpp"

#include <iostream>
#include <thread>

namespace roguelike 
{
    Roguelike::Roguelike(roguelike::Renderer* renderer)
        : renderer(renderer), should_exit(false) { }

    Roguelike::~Roguelike()
    {
        delete renderer;
    }

    void Roguelike::StartSystems() {
        thread_update = std::thread([this]() {
            while (!should_exit) {
                Update(0.1f);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });

        thread_command = std::thread([this]() {
            while (!should_exit) {
                auto command = command_poll.PopCommand();
                command->Execute(*this);
                delete command;
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        });

        thread_world_command = std::thread([this]() {
            while (!should_exit) {
                auto command = GetWorld().GetCommandPoll()->PopCommand();
                command->Execute(world);
                delete command;
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        });

        thread_update.detach();
        thread_command.detach();
        thread_world_command.detach();
    }

    void Roguelike::Exit() {
        should_exit = true;
    }

    commands::CommandPoll<RoguelikeCommand>* Roguelike::GetCommandPoll() {
        return &command_poll;
    }

    void Roguelike::Update(const float& dt)
    {
    }

    void Roguelike::Render() {
        renderer->Clear();
        renderer->Render(world.GetEntities());
        renderer->Present();
    }
}

