#pragma once

#include "command.hpp"
#include "../../math/vec2d.hpp"


namespace roguelike{
    class Entity;
    class World;
    namespace commands{
        class EntityCommand : public Command {
        public:
            EntityCommand(Entity* target_entity) : entity(target_entity) {}
            virtual void Execute(World& world) = 0;

            Entity* GetEntity() const {
                return entity;
            }

        private:
            Entity* entity;
        };

        class MoveEntityCommand : public EntityCommand {
        public:
            MoveEntityCommand(Entity* target_entity, vec2di target_position) 
                : EntityCommand(target_entity), target_position(target_position) {}

            void Execute(World& world) override;

            const vec2di& GetTargetPosition() const {
                return target_position;
            }
        private:
                vec2di target_position;
        };
    }
}