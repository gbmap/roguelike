#include "entity_yml_parser.hpp"

#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>

#include "../../data.hpp"
#include "../entity.hpp"

namespace roguelike
{

    Entity* EntityYMLParser::Parse(std::string yaml)
    {
        YAML::Node node = YAML::Load(yaml);

        std::string symbol = node["representation"]["character"].as<std::string>();

        YAML::Node yml_color = node["representation"]["color"];
        color_t foreground_color;
        foreground_color.r = yml_color[0].as<uint8_t>();
        foreground_color.g = yml_color[1].as<uint8_t>();
        foreground_color.b = yml_color[2].as<uint8_t>();

        YAML::Node yml_bg_color = node["representation"]["background_color"];
        color_t background_color;
        background_color.r = yml_bg_color[0].as<uint8_t>();
        background_color.g = yml_bg_color[1].as<uint8_t>();
        background_color.b = yml_bg_color[2].as<uint8_t>();

        WorldRepresentation world_representation(
            symbol, foreground_color, background_color
        );

        return new Entity(world_representation, roguelike::vec2di(0, 0));
    }

    Entity* EntityYMLParser::ParseFile(std::string filename)
    {
        std::ifstream input_stream(filename);
        std::stringstream buffer;
        buffer << input_stream.rdbuf();
        return Parse(buffer.str());
    }
}