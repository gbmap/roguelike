#include <catch.hpp>
#include "../roguelike/message_router.hpp"

class TestMessage {};

TEST_CASE("Get empty handler count", "[GetHandlerCount]")
{
    auto router = MessageRouter::GetInstance();
    REQUIRE(router->GetHandlerCount<TestMessage>() == 0);
}

TEST_CASE("Add handler", "[AddHandler]")
{
    auto router = MessageRouter::GetInstance();
    auto handler = std::function<void(TestMessage)>([](TestMessage m) {});
    router->AddHandler<TestMessage>(handler);

    REQUIRE(router->GetHandlerCount<TestMessage>() == 1);

    router->Clear<TestMessage>();
}

TEST_CASE("Remove handler", "[RemoveHandler]")
{
    auto router = MessageRouter::GetInstance();
    auto handler = std::function<void(TestMessage)>([](TestMessage m) {});

    REQUIRE(router->GetHandlerCount<TestMessage>() == 0);

    std::shared_ptr<MessageHandler> message_handler = router->AddHandler<TestMessage>(handler);
    router->RemoveHandler<TestMessage>(message_handler);

    REQUIRE(router->GetHandlerCount<TestMessage>() == 0);
    router->Clear<TestMessage>();
}

TEST_CASE("Raise message calls handler", "[RaiseMessage]")
{
    auto router = MessageRouter::GetInstance();
    int value = 0;

    auto handler = std::function<void(TestMessage)>([&value](TestMessage m) { value = 999; });
    router->AddHandler<TestMessage>(handler);

    TestMessage msg = TestMessage();
    router->RaiseMessage<TestMessage>(msg);
    REQUIRE(value == 999);
}

TEST_CASE("Casting handler", "[CastingHandler]")
{
    auto router = MessageRouter::GetInstance();
    int value = 0;

    auto handler = std::function<void(TestMessage)>([&value](TestMessage m) { value = 999; });
    void* handler_ptr = reinterpret_cast<void*>(&handler);

    MessageHandler* message_handler = new MessageHandler(handler_ptr);
    auto handler2 = reinterpret_cast<std::function<void(TestMessage)>*>(message_handler->handler);
    (*handler2)(TestMessage());

    REQUIRE(value == 999);
}