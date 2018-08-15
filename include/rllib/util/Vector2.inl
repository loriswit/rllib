template<typename T>
constexpr Vector2<T>::Vector2(T X, T Y) :
        x{X}, y{Y}
{
}

template<typename T>
std::ostream & operator<<(std::ostream & stream, const Vector2<T> & vector)
{
    return stream << '{' << vector.x << ", " << vector.y << '}';
}
