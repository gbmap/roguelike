#pragma once

#include "../entity.hpp"
#include "../world.hpp"
#include "command.hpp"

namespace roguelike
{
    namespace commands
    {
        class WorldCommand : public Command
        {
        public:
            virtual void Execute(World& world) = 0;
        };

        class WorldSpawnEntityCommand : public WorldCommand
        {
        public:
            WorldSpawnEntityCommand(Entity *entity) : entity(entity) {}
            void Execute(World &world) override {
                world.SpawnEntity(entity);
                std::cout << " [WORLD] Spawned entity " 
                          << entity->GetRepresentation().GetSymbol() 
                          << " at " << entity->GetPosition().GetX() 
                          << ", "  << entity->GetPosition().GetY()
                          << " (Number of entities: " << world.GetEntityCount() << ")" 
                          << std::endl;
            }

            const Entity &GetEntity() const {
                return *entity;
            }

        private:
            Entity *entity;
        };

        class WorldDestroyEntityCommand : public WorldCommand {
            WorldDestroyEntityCommand(Entity *entity) : entity(entity) {}
            void Execute(World &world) override {
                world.DestroyEntity(entity);
            }

            const Entity &GetEntity() const {
                return *entity;
            }

        private:
            Entity *entity;
        };
    }
}
