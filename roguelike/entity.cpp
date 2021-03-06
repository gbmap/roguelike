#include "entity.hpp"

#include <random>
#include <functional>

#include "world.hpp"
#include "renderer.hpp"
#include "commands/entity_command.hpp"
#include "rng.hpp"

namespace roguelike {
    const WorldRepresentation& Entity::GetRepresentation() const {
        return world_representation;
    }

    void Entity::SetPosition(int x, int y) {
        position = vec2di({x,y});
    }

    const vec2di& Entity::GetPosition() const {
        return position;
    }

    commands::EntityCommand* Entity::GetNextAction(const World& world) {
        vec2di p = GetPosition();
        int random_x = p.GetX() + (GetRandomInt() % 2 == 0 ? -1 : 1);
        int random_y = p.GetY() + (GetRandomInt() % 2 == 0 ? -1 : 1);
        return new commands::MoveEntityCommand(this, vec2di({random_x,random_y}));
    }

    void Entity::Draw(const Renderer* renderer) const {
        renderer->Render(world_representation, position);
    }

    int Entity::GetRandomInt() const {
        return RNG::Rand();
    }
}