
#include <catch.hpp>
#include "..\..\math\vec2di.hpp"

using namespace roguelike;

TEST_CASE("Test Vec2Di addition", "[Vec2Di]")
{
    Vec2D<int> a(1, 2);	
    Vec2D<int> b(3, 4);

    REQUIRE(a+b == Vec2D<int>(4, 6));
}

TEST_CASE("Test Vec2Di subtraction", "[Vec2Di]")
{
    Vec2D<int> a(1, 2);	
    Vec2D<int> b(3, 4);

    REQUIRE(a-b == Vec2D<int>(-2, -2));
}

TEST_CASE("Test Vec2Di scalar multiplication", "[Vec2Di]")
{
    Vec2D<int> a(1, 2);	
    Vec2D<int> b(3, 4);

    REQUIRE(a*3 == Vec2D<int>(3, 6));
    REQUIRE(b*3 == Vec2D<int>(9, 12));
}