
#pragma once 

#include <vector>
#include <memory>

#include "../data.hpp"
#include "../math/vec2d.hpp"
#include "commands/entity_command.hpp"
#include "brain/entity_brain.hpp"
#include "brain/dummy_brain.hpp"
#include "brain/random_movement_brain.hpp"

namespace roguelike {
    class World;
    class Renderer;
    class Entity {
    public:
        Entity(const WorldRepresentation& r, const vec2di& p) 
            : world_representation(r), position(p), brain(new DummyBrain()) {}

        const WorldRepresentation& GetRepresentation() const;

        // ==================== POSITION
        void SetPosition(int x, int y);
        const vec2di& GetPosition() const;
        
        // ==================== BRAIN
        void SetBrain(EntityBrain* brain);
        std::shared_ptr<EntityBrain> GetBrain() const;
        commands::EntityCommand* GetNextAction(const World& world);
        
        // ==================== RENDERING
        void Draw(const Renderer* renderer) const;
    private:
        vec2di position;
        WorldRepresentation world_representation;
        EntityStats stats;

        std::shared_ptr<EntityBrain> brain;

        int GetRandomInt() const;
    };

    typedef std::vector<Entity*> EntityVector;
}