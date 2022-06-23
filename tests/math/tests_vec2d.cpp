
#include <catch.hpp>
#include "..\..\math\vec2d.hpp"

using namespace roguelike;


TEST_CASE("Test Vec2D<int> addition", "[Vec2D]")
{
    vec2di a(1, 2);	
    vec2di b(3, 4);

    REQUIRE(a+b == vec2di(4, 6));
}

TEST_CASE("Test Vec2D<int> subtraction", "[Vec2D]")
{
    vec2di a(1, 2);	
    vec2di b(3, 4);

    REQUIRE(a-b == vec2di(-2, -2));
}

TEST_CASE("Test Vec2D<int> scalar multiplication", "[Vec2D]")
{
    vec2di a(1, 2);	
    vec2di b(3, 4);

    REQUIRE(a*3 == vec2di(3, 6));
    REQUIRE(b*3 == vec2di(9, 12));
}