#ifndef GAME__H
#define GAME__H

#include <vector>

namespace roguelike
{
    class Renderer;
    struct EntityData;

    class Roguelike
    {
    public:
        Roguelike(Renderer* pRenderer); 
        ~Roguelike(); 

        void Update(const float& dt);
        void SpawnEntity(EntityData* pEntity);
        void DestroyEntity(EntityData* pEntity);

    private:
        Renderer* m_pRenderer;
        std::vector<EntityData*> m_Entities;
    };
}

#endif