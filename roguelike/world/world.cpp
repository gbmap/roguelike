#include "world.hpp"

#include <algorithm>
#include <math.h>
#include <future>

#include "../commands/command.hpp"
#include "../commands/world_command.hpp"
#include "../commands/entity_command.hpp"

namespace roguelike {
    commands::CommandPoll<commands::WorldCommand>* World::GetCommandPoll() {
        return &command_poll;
    }

    void World::SpawnEntity(Entity* entity) {
        std::lock_guard lock(mutex);
        entities.push_back(entity);
    }

    void World::DestroyEntity(Entity* entity) {
        std::lock_guard lock(mutex);
        entities.erase(std::find(entities.begin(), entities.end(), entity));
        delete entity;
    }

    size_t World::GetEntityCount() {
        std::lock_guard lock(mutex);
        return entities.size();
    }

    Entity* World::GetEntity(int index) {
        std::lock_guard lock(mutex);
        return entities[index];
    }

    void World::UpdateEntityLogic() {
        std::vector<commands::EntityCommand*> commands = GatherEntitiesNextActions();
        for (auto command : commands) {
            command->Execute(*this);
        }
    } 

    std::vector<commands::EntityCommand*> World::GatherEntitiesNextActions() {
        std::lock_guard lock(mutex);
        return UpdateInSingleThread();
    }

    EntityCommandVector World::UpdateInSingleThread() {
        std::vector<commands::EntityCommand*> commands;
        for (auto entity : entities) {
            commands::EntityCommand* command = entity->GetNextAction(*this);
            if (command != nullptr) {
                commands.push_back(command);
            }
        }
        return commands;
    }

    EntityCommandVector World::UpdateMultipleThreads() {
        std::vector<std::thread> threads;

        int n_threads = (int)std::thread::hardware_concurrency();
        int n_entities = entities.size();
        if (n_entities == 0)
            return EntityCommandVector();

        if (n_entities < n_threads)
            n_threads = 1;

        int block_size = n_entities / n_threads;
        int remaining_size = n_entities;

        EntityCommandVector final_commands;
        std::mutex commands_mutex;

        for (auto begin = entities.begin(), end = entities.end(); begin!=end;) {
            int current_block_size = std::min(block_size, remaining_size);
            threads.emplace_back([begin, end, this, current_block_size, &final_commands, &commands_mutex]() {
                std::vector<commands::EntityCommand*> thread_commands;
                std::for_each(begin, begin+current_block_size, [&](Entity* entity) {
                    auto command = entity->GetNextAction(*this);
                    if (command != nullptr)
                        thread_commands.push_back(command);
                });

                std::lock_guard lock(commands_mutex);
                final_commands.insert(final_commands.end(), thread_commands.begin(), thread_commands.end());
            });
            begin += current_block_size;
            remaining_size -= current_block_size;
        }

        for (auto& t : threads) {
            t.join();
        }

        return final_commands;
    }
    
    EntityCommandVector World::UpdateMultipleTasks() {
        int n_threads = (int)std::thread::hardware_concurrency();
        int n_entities = entities.size();
        if (n_entities == 0)
            return EntityCommandVector();

        if (n_entities < n_threads)
            n_threads = 1;

        int block_size = n_entities / n_threads;
        int remaining_size = n_entities;

        EntityCommandVector final_commands;
        std::mutex commands_mutex;

        std::vector<std::future<EntityCommandVector>> futures;

        for (auto begin = entities.begin(), end = entities.end(); begin!=end;) {
            int current_block_size = std::min(block_size, remaining_size);
            futures.emplace_back(
                std::async([begin, current_block_size, this]() {
                std::vector<commands::EntityCommand*> thread_commands;
                std::for_each(begin, begin+current_block_size, [&](Entity* entity) {
                    auto command = entity->GetNextAction(*this);
                    if (command != nullptr)
                        thread_commands.push_back(command);
                });
                return thread_commands;
            }));
            begin += current_block_size;
            remaining_size -= current_block_size;
        }

        std::for_each(futures.begin(), futures.end(), [&final_commands](std::future<EntityCommandVector>& future) {
            EntityCommandVector commands = future.get();
            final_commands.insert(final_commands.end(), commands.begin(), commands.end());
        });

        return final_commands;
    }
} 