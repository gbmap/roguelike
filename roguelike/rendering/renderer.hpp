#pragma once

#include <functional>
#include <vector>
#include "renderable.hpp"
#include "../message_router.hpp"
#include "../../data.hpp"
#include "../../math/vec2d.hpp"

class MessageHandler;
using namespace roguelike;

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Callback_OnRenderableCreated(MsgOnRenderableCreated renderable);
    void Callback_OnRenderableDestroyed(MsgOnRenderableDestroyed renderable);

    virtual void Clear() = 0;
    virtual void Render(const WorldRepresentation& representation, const vec2di& position) const = 0;

    void Render();

    int GetRenderableCount() const;
private:
    std::vector<Renderable*> renderables;

    std::shared_ptr<MessageHandler> on_renderable_created;
    std::shared_ptr<MessageHandler> on_renderable_destroyed;

    std::function<void(MsgOnRenderableCreated)> on_renderable_created_handler;
    std::function<void(MsgOnRenderableDestroyed)> on_renderable_destroyed_handler;
};

class DummyRenderer : public Renderer
{
public:
    void Clear() override;
    void Render(const WorldRepresentation& representation, const vec2di& position) const override;
};