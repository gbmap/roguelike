

#include "roguelike_app.hpp"
#include "renderer.hpp"

namespace roguelike 
{
    Roguelike::Roguelike(roguelike::Renderer* pRenderer)
    {
        m_pRenderer = pRenderer;
    }

    Roguelike::~Roguelike()
    {
        for (auto pEntity : m_Entities)
            delete pEntity;
        delete m_pRenderer;
    }

    void Roguelike::Update(const float& dt)
    {
        m_pRenderer->Render(m_Entities);
    }

    void Roguelike::SpawnEntity(roguelike::EntityData* pEntity)
    {
        m_Entities.push_back(pEntity);
    }

    void Roguelike::DestroyEntity(roguelike::EntityData* pEntity)
    {
        auto it = std::find(m_Entities.begin(), m_Entities.end(), pEntity);
        if (it != m_Entities.end())
        {
            m_Entities.erase(it);
        }
    }

}

