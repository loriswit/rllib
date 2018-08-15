template<typename T>
constexpr Vector3<T>::Vector3(T X, T Y, T Z) :
        x{X}, y{Y}, z{Z}
{
}

template<typename T>
std::ostream & operator<<(std::ostream & stream, const Vector3<T> & vector)
{
    return stream << '{' << vector.x << ", " << vector.y << ", " << vector.z << '}';
}
