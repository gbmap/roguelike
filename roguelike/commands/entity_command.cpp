
#include "entity_command.hpp"
#include "../entity.hpp"
#include "../world/world.hpp"

namespace roguelike {
    namespace commands {
        void MoveEntityCommand::Execute(World& world) {
            GetEntity()->SetPosition(target_position.GetX(), target_position.GetY());
        }
    }
}