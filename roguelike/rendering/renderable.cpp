#include "renderable.hpp"
#include "../message_router.hpp"

MsgOnRenderableCreated::MsgOnRenderableCreated(Renderable* r) : renderable(r) {}
MsgOnRenderableDestroyed::MsgOnRenderableDestroyed(Renderable* r) : renderable(r) {}

Renderable::Renderable()
{
    auto router = MessageRouter::GetInstance();
    router->RaiseMessage<MsgOnRenderableCreated>(MsgOnRenderableCreated(this));
}

Renderable::~Renderable()
{
    auto router = MessageRouter::GetInstance();
    router->RaiseMessage<MsgOnRenderableDestroyed>(MsgOnRenderableDestroyed(this));
}


void DummyRenderable::Render(Renderer* renderer)
{
    return;
}