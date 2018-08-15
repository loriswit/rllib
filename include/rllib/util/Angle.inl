namespace rl
{

constexpr Angle::Angle(float a) noexcept : angle{a}
{
}

constexpr Angle::operator float() const noexcept
{
    return angle;
}

constexpr Angle::operator float &() noexcept
{
    return angle;
}

inline std::ostream & operator<<(std::ostream & stream, const Angle & angle)
{
    return stream << angle / PI * 180 << " degrees";
}

} // namespace rl

constexpr rl::Angle operator "" _deg(long double angle)
{
    return angle / 180 * rl::PI;
}

constexpr rl::Angle operator "" _deg(unsigned long long angle)
{
    return static_cast<long double>(angle) / 180 * rl::PI;
}
