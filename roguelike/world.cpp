#include "world.hpp"

#include <algorithm>
#include <math.h>
#include <future>

#include "commands/command.hpp"
#include "commands/world_command.hpp"
#include "commands/entity_command.hpp"

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
        /*
        typedef std::vector<commands::EntityCommand*> CommandVector;
        // typedef std::vector<Entity*> EntityVector;

        int n_threads = std::min(
            (int)entities.size(), (int)std::thread::hardware_concurrency()
        );
        n_threads = std::max(n_threads, 1);

        CommandVector commands;
        // std::vector<std::thread> threads;
        std::vector<std::future<CommandVector>> futures;

        int block_size = entities.size() / n_threads;
        int exceeding = entities.size() % n_threads;

        EntityVector::iterator it = entities.begin();
        for (int i = 0; i < n_threads; i++) {
            std::future<CommandVector> future = std::async([this](EntityVector entities) {
                CommandVector commands;
                for (auto entity : entities) {
                    commands::EntityCommand* command = entity->GetNextAction(*this);
                    if (command != nullptr) {
                        commands.push_back(command);
                    }
                }
                return commands;
            }, EntityVector(it, it+block_size+exceeding*(i==n_threads-1)));
            futures.push_back(std::move(future));

            // threads.push_back(std::thread([&, begin, end]() {
            //     std::vector<commands::Command*> thread_commands;
            //     for (auto entity = begin; entity != end; entity++) {
            //         auto command = (*entity)->GetNextAction(*this);
            //         if (command == nullptr)
            //             continue;
            //         thread_commands.push_back(command);
            //     }

            //     std::lock_guard lock(mutex);
            //     commands.insert(commands.end(), thread_commands.begin(), thread_commands.end());
            // }));
        }

        for (auto& future : futures) {
            // std::lock_guard lock(mutex);
            auto thread_commands = future.get();
            commands.insert(commands.end(), thread_commands.begin(), thread_commands.end());
        }


        // for (auto& t : threads) {
        //     t.join();
        // }

        return commands;
        */

    //    return UpdateMultipleThreads();
        return UpdateMultipleThreads();
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
        return EntityCommandVector();
    }

} 