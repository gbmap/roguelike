#include <catch.hpp>
#include <yaml-cpp/yaml.h>
#include "../data.hpp"
#include "../roguelike/entity.hpp"
#include "../roguelike/entity_parser/entity_yml_parser.hpp"

TEST_CASE("YAML::Node::as<T>()", "[YAML]")
{
    YAML::Node node = YAML::Load("key: value");
    REQUIRE(node["key"].as<std::string>() == "value");
}

TEST_CASE("Create entity from YML file", "[YAML]")
{
    YAML::Node node = YAML::LoadFile("data/grass.yml");
    REQUIRE(node["name"].as<std::string>() == "grass");
    REQUIRE(node["representation"]["type"].as<std::string>() == "static");
    REQUIRE(node["representation"]["character"].as<std::string>() == ".");
    YAML::Node color = node["representation"]["color"];
    REQUIRE(color[0].as<int>() == 0);
    REQUIRE(color[1].as<int>() == 255);
    REQUIRE(color[2].as<int>() == 0);

    std::string symbol = node["representation"]["character"].as<std::string>();
    YAML::Node yml_color = node["representation"]["color"];

    roguelike::color_t foreground_color;
    foreground_color.r = yml_color[0].as<uint8_t>();
    foreground_color.g = yml_color[1].as<uint8_t>();
    foreground_color.b = yml_color[2].as<uint8_t>();

    roguelike::color_t background_color;
    YAML::Node yml_bg_color = node["representation"]["background_color"];
    background_color.r = yml_bg_color[0].as<uint8_t>();
    background_color.g = yml_bg_color[1].as<uint8_t>();
    background_color.b = yml_bg_color[2].as<uint8_t>();

    roguelike::WorldRepresentation world_representation(
        symbol, foreground_color, background_color
    );
    roguelike::Entity entity = roguelike::Entity(world_representation, roguelike::vec2di(0, 0));
    REQUIRE(entity.GetRepresentation().GetSymbol() == ".");
    REQUIRE(entity.GetRepresentation().GetForegroundColor().r == 0);
    REQUIRE(entity.GetRepresentation().GetForegroundColor().g == 255);
    REQUIRE(entity.GetRepresentation().GetForegroundColor().b == 0);
    REQUIRE(entity.GetRepresentation().GetBackgroundColor().r == 0);
    REQUIRE(entity.GetRepresentation().GetBackgroundColor().g == 0);
    REQUIRE(entity.GetRepresentation().GetBackgroundColor().b == 0);
}

TEST_CASE("Create entity from EntityYMLParser")
{
    roguelike::Entity* entity = roguelike::EntityYMLParser().ParseFile("data/grass.yml");
    REQUIRE(entity->GetRepresentation().GetSymbol() == ".");
    REQUIRE(entity->GetRepresentation().GetForegroundColor().r == 0);
    REQUIRE(entity->GetRepresentation().GetForegroundColor().g == 255);
    REQUIRE(entity->GetRepresentation().GetForegroundColor().b == 0);
    REQUIRE(entity->GetRepresentation().GetBackgroundColor().r == 0);
    REQUIRE(entity->GetRepresentation().GetBackgroundColor().g == 0);
    REQUIRE(entity->GetRepresentation().GetBackgroundColor().b == 0);
}