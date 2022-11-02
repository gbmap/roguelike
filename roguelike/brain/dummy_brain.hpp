#pragma once

#include "entity_brain.hpp"
#include "../commands/entity_command.hpp"

namespace roguelike
{
    class Entity;
    class DummyBrain : public EntityBrain
    {
    public:
        commands::EntityCommand* GetNextCommand(
            Entity& entity, const World& world
        ) override { return nullptr; }
    };
}