#include "roguelike.hpp"
#include "world/world.hpp"
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
        thread_update = std::thread(&Roguelike::ThreadUpdate, this);
        thread_command = std::thread(&Roguelike::ThreadExecuteCommands, this);
        thread_world_command = std::thread(&Roguelike::ThreadExecuteWorldCommands, this);

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
        world.UpdateEntityLogic();
    }

    void Roguelike::Render() {
        renderer->Clear();
        int entity_count = world.GetEntityCount();
        for (int i = 0; i < world.GetEntityCount(); i++) {
            world.GetEntity(i)->Draw(renderer);
        }
        renderer->Present();
    }

    void Roguelike::ThreadUpdate()
    {
        while (!should_exit)
        {
            Update(0.1f);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void Roguelike::ThreadExecuteCommands()
    {
        while (!should_exit) {
            auto command = command_poll.PopCommand();
            command->Execute(*this);
            delete command;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    void Roguelike::ThreadExecuteWorldCommands()
    {
        while (!should_exit) {
            auto command = GetWorld().GetCommandPoll()->PopCommand();
            command->Execute(world);
            delete command;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}

