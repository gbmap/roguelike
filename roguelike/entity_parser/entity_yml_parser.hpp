

#pragma once
#include <string>

namespace roguelike
{
    class Entity;
    class EntityYMLParser
    {
    public:
        Entity* Parse(std::string yaml);
        Entity* ParseFile(std::string filename);
    };
}