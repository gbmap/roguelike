#include "entity.hpp"

#include <random>
#include <functional>

#include "world/world.hpp"
#include "renderer.hpp"
#include "commands/entity_command.hpp"
#include "rng.hpp"

namespace roguelike {
    const WorldRepresentation& Entity::GetRepresentation() const {
        return world_representation;
    }

    void Entity::SetPosition(int x, int y) 
    {
        position = vec2di({x,y});
    }

    const vec2di& Entity::GetPosition() const 
    {
        return position;
    }

    void Entity::SetBrain(EntityBrain* brain)
    {
        this->brain = std::shared_ptr<EntityBrain>(brain);
    }

    std::shared_ptr<EntityBrain> Entity::GetBrain() const
    {
        return brain;
    }

    commands::EntityCommand* Entity::GetNextAction(const World& world) 
    {
        if (brain == nullptr)
            return nullptr;

        return brain->GetNextCommand(*this, world);
    }

    void Entity::Draw(const Renderer* renderer) const {
        renderer->Render(world_representation, position);
    }

    int Entity::GetRandomInt() const {
        return RNG::Rand();
    }
}