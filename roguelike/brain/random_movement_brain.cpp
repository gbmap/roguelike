#include "random_movement_brain.hpp"

#include "../../math/vec2d.hpp"
#include "../../data.hpp"
#include "../rng.hpp"

#include "../entity.hpp"

namespace roguelike
{
    commands::EntityCommand* RandomMovementBrain::GetNextCommand(
        Entity& entity, const World& world
    )
    {
        vec2di p = entity.GetPosition();
        int random_x = p.GetX() + (RNG::Rand() % 2 == 0 ? -1 : 1);
        int random_y = p.GetY() + (RNG::Rand() % 2 == 0 ? -1 : 1);
        return new commands::MoveEntityCommand(&entity, vec2di({random_x,random_y}));
    }
}