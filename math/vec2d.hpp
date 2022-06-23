#ifndef VEC2D_H
#define VEC2D_H

namespace roguelike
{
    template<typename T> 
    class Vec2D
    {
    public:
        Vec2D(T x, T y) : x(0), y(0) {}

        T GetX() const { return x; }
        T GetY() const { return y; }

        T Length() const
        {
            // Needs to change. There's no guarantee sqrt
            // can run on T.
            return sqrt(x * x + y * y);
        }

        Vec2D<T> operator+(const Vec2D<T>& value) const
        {
            return Vec2D<T>(x + value.x, y + value.y);
        }

        Vec2D<T> operator*(const T& value) const
        {
            return Vec2D<T>(x * value, y * value);
        }

        Vec2D<T> operator-(const Vec2D<T>& value) const
        {
            return Vec2D<T>(x - value.x, y - value.y);
        }

        bool operator==(const Vec2D<T>& value) const
        {
            return x == value.x && y == value.y;
        }

    private:
        T x;
        T y;
    };

    typedef Vec2D<int> vec2di;
    typedef Vec2D<float> vec2df;

    #endif
}