#pragma once


#include "../commands/entity_command.hpp"

namespace roguelike
{
    class Entity;
    class EntityBrain
    {
    public:
        virtual commands::EntityCommand* GetNextCommand(
            Entity& entity, const World& world
        ) = 0;
    };
}