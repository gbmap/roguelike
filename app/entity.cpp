#include "entity.hpp"
#include "world.hpp"

namespace roguelike {
    const WorldRepresentation& Entity::GetRepresentation() const {
        return world_representation;
    }
    const vec2di& Entity::GetPosition() const {
        return position;
    }

    commands::Command* Entity::GetNextAction(World& world) {
        return nullptr;
    }
}