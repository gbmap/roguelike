
#include "renderer.hpp"
#include "../message_router.hpp"
#include <functional>

Renderer::Renderer()
{
    auto message_router = MessageRouter::GetInstance();   

    on_renderable_created_handler = std::bind(&Renderer::Callback_OnRenderableCreated, this, std::placeholders::_1);
    on_renderable_created = message_router->AddHandler<MsgOnRenderableCreated>(on_renderable_created_handler);

    on_renderable_destroyed_handler = std::bind(&Renderer::Callback_OnRenderableDestroyed, this, std::placeholders::_1);
    on_renderable_destroyed = message_router->AddHandler<MsgOnRenderableDestroyed>(on_renderable_destroyed_handler);
}

Renderer::~Renderer()
{
    auto message_router = MessageRouter::GetInstance();
    message_router->RemoveHandler<MsgOnRenderableCreated>(on_renderable_created);
    message_router->RemoveHandler<MsgOnRenderableDestroyed>(on_renderable_destroyed);
}

void Renderer::Callback_OnRenderableCreated(MsgOnRenderableCreated msg)
{
    renderables.push_back(msg.renderable);
}

void Renderer::Callback_OnRenderableDestroyed(MsgOnRenderableDestroyed msg)
{
    renderables.erase(std::remove(renderables.begin(), renderables.end(), msg.renderable), renderables.end());
}

void Renderer::Render()
{
    for (auto renderable : renderables)
    {
        renderable->Render(this);
    }
}

int Renderer::GetRenderableCount() const
{
    return renderables.size();
}

void DummyRenderer::Clear()
{
    return;
}

void DummyRenderer::Render(const WorldRepresentation& representation, const vec2di& position) const
{
    return;
}