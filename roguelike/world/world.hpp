#pragma once
#include <vector>
#include <mutex>

#include "../entity.hpp"
#include "../commands/command_poll.hpp"
// #include "commands/world_command.hpp"

namespace roguelike {

    namespace commands{
        class WorldCommand;
        class EntityCommand;
    }

    typedef std::vector<commands::EntityCommand*> EntityCommandVector;
    class World {
    public:
        World() : entities() {}
        ~World() {
            std::lock_guard lock(mutex);
            for (auto entity : entities) {
                delete entity;
            }
            entities.clear();
        }

        commands::CommandPoll<commands::WorldCommand>* GetCommandPoll();

        size_t GetEntityCount();  
        Entity* GetEntity(int index);
        void SpawnEntity(Entity* entity);
        void DestroyEntity(Entity* entity);
        void UpdateEntityLogic();
    private:
        World(const World&) = delete;

        std::mutex mutex;
        std::vector<Entity*> entities;

        commands::CommandPoll<commands::WorldCommand> command_poll;
        EntityCommandVector GatherEntitiesNextActions();

        EntityCommandVector UpdateInSingleThread();
        EntityCommandVector UpdateMultipleThreads();
        EntityCommandVector UpdateMultipleTasks();
    };
}