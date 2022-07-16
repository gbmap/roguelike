#include "world.hpp"

#include <algorithm>
#include <math.h>

#include "commands/command.hpp"
#include "commands/world_command.hpp"

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
        std::remove(entities.begin(), entities.end(), entity);
        delete entity;
    }

    void World::UpdateEntityLogic() {
        int n_threads = std::max((unsigned int)1, std::thread::hardware_concurrency() / 2);
        std::mutex mutex;
        std::vector<commands::Command*> commands;
        std::vector<std::thread> threads;

        int block_size = entities.size() / n_threads;
        int exceeding = entities.size() % n_threads;

        for (int i = 0; i < n_threads; i++) {
            auto begin = GetEntities().begin() + i * block_size;
            auto end = begin + block_size;
            if (i == n_threads-1) {
                end += exceeding;
            }

            threads.push_back(std::thread([&, begin, end]() {
                std::vector<commands::Command*> thread_commands;
                for (auto entity = begin; entity != end; entity++) {
                    auto command = (*entity)->GetNextAction(*this);
                    if (command == nullptr)
                        continue;
                    thread_commands.push_back(command);
                }

                std::lock_guard lock(mutex);
                commands.insert(commands.end(), thread_commands.begin(), thread_commands.end());
            }));
        }

        for (auto& t : threads) {
            t.join();
        }
    } 
} 