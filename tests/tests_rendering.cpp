#include <catch.hpp>
#include "../roguelike/message_router.hpp"
#include "../roguelike/rendering/renderer.hpp"


TEST_CASE("Creating renderable raises OnRenderableCreated", "[OnRenderableCreated]")
{
    auto router = MessageRouter::GetInstance();
    int value = 0;

    auto handler = std::function<void(MsgOnRenderableCreated)>([&value](MsgOnRenderableCreated m) { value = 999; });
    router->AddHandler<MsgOnRenderableCreated>(handler);

    Renderable* renderable = new DummyRenderable();
    REQUIRE(value == 999);

    router->Clear();
}

TEST_CASE("Creating renderable increases renderables count", "[OnRenderableCreated]")
{
    DummyRenderer r;
    Renderable* renderable = new DummyRenderable();

    REQUIRE(r.GetRenderableCount() == 1);

    MessageRouter::GetInstance()->Clear();
}