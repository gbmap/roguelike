
#include <catch.hpp>
#include <chrono>
#include "../roguelike/world.hpp"
#include "../roguelike/entity.hpp"
#include "../roguelike/commands/world_command.hpp"

using namespace roguelike;
using namespace std::literals::chrono_literals;

std::string random_char()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100, 150);
    return std::string(1, char(dis(gen)));
}

vec2di random_pos()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);
    return vec2di(dis(gen), dis(gen));
}

TEST_CASE("Instantie world.", "[World]")
{
    World world;
}

TEST_CASE("Instantiate one entity.", "[Spawn]")
{
    World world;
    Entity *entity = new Entity({"@", {255, 255, 255}, {0, 0, 0}}, {0, 0});
    world.SpawnEntity(entity);

    REQUIRE(world.GetEntity(0) == entity);
    REQUIRE(world.GetEntityCount() == 1);
}

TEST_CASE("Instantiate entity.", "[SpawnMultiple]")
{
    World world;
    EntityVector entities;
    for (int i = 0; i < 10; ++i)
    {
        Entity *entity = new Entity({random_char(), {255, 255, 255}, {0, 0, 0}}, random_pos());
        world.SpawnEntity(entity);
        entities.push_back(entity);
    }

    for (int i = 0; i < 10; ++i)
    {
        Entity *a = entities[i];
        Entity *b = world.GetEntity(i);
        REQUIRE(a == b);
    }

    REQUIRE(world.GetEntityCount() == 10);
}

TEST_CASE("Spawn one command spawns one entity.", "[SpawnCommandOne]")
{
    World world;
    EntityVector entities;
    auto now = std::chrono::system_clock::now();
    std::thread t_handle_command([&]() {
        while (true) {
            world.GetCommandPoll()->PopCommand()->Execute(world);
        }
    });
    t_handle_command.detach();

    Entity *entity = new Entity({random_char(), {255, 255, 255}, {0, 0, 0}}, random_pos());
    world.GetCommandPoll()->QueueCommand(
        new commands::WorldSpawnEntityCommand(entity)
    );

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    REQUIRE(world.GetEntityCount() == 1);
}

TEST_CASE("Spawn entities through commands.", "[SpawnCommand]")
{
    World world;
    EntityVector entities;
    auto now = std::chrono::system_clock::now();
    std::thread t_handle_command([&]() {
        while (true) {
            world.GetCommandPoll()->PopCommand()->Execute(world);
        }
    });
    t_handle_command.detach();

    std::thread t1([&]() {
        while (std::chrono::system_clock::now() - now < std::chrono::milliseconds(1000)) {
            Entity *entity = new Entity({random_char(), {255, 255, 255}, {0, 0, 0}}, random_pos());
            world.GetCommandPoll()->QueueCommand(
                new commands::WorldSpawnEntityCommand(entity)
            );
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        } 
    });
    t1.join();
    REQUIRE(world.GetEntityCount() > 0);
}

TEST_CASE("Update one entity logic.", "[UpdateLogicOne]")
{
    World world;
    EntityVector entities;
    std::thread t_handle_command([&]() {
        while (true) {
            world.GetCommandPoll()->PopCommand()->Execute(world);
        }
    });
    t_handle_command.detach();

    Entity *entity = new Entity({random_char(), {255, 255, 255}, {0, 0, 0}}, random_pos());
    world.GetCommandPoll()->QueueCommand(
        new commands::WorldSpawnEntityCommand(entity)
    );


    // Wait for entity to be spawned.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    REQUIRE(world.GetEntityCount() > 0);
    REQUIRE_NOTHROW(world.UpdateEntityLogic());
}


TEST_CASE("Update multiple entities logic.", "[UpdateLogicMultiple]") {
    World world;
    EntityVector entities;
    std::thread t_handle_command([&]() {
        while (true) {
            world.GetCommandPoll()->PopCommand()->Execute(world);
        }
    });
    t_handle_command.detach();

    std::thread t1([&]() {
        auto now = std::chrono::system_clock::now();
        while (std::chrono::system_clock::now() - now < std::chrono::seconds(1)) {
            Entity *entity = new Entity({random_char(), {255, 255, 255}, {0, 0, 0}}, random_pos());
            world.GetCommandPoll()->QueueCommand(
                new commands::WorldSpawnEntityCommand(entity)
            );
            std::this_thread::sleep_for(1ms);
        }
    });
    t1.join();

    // Wait spawn.
    std::this_thread::sleep_for(200ms);
    REQUIRE(world.GetEntityCount() > 0);

    int n = GENERATE(1);
    for (int i = 0; i < n; i++) {
        REQUIRE_NOTHROW(world.UpdateEntityLogic());
    }
}