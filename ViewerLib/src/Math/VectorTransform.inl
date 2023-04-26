namespace VL 
{
    template<typename T, std::size_t S>
    constexpr T dot(const Vector<T, S>& v1, const Vector<T, S>& v2)
    {
        auto v1ToArray = v1.toArray();
        auto v2ToArray = v2.toArray();
        return std::inner_product(v1ToArray.begin(), v1ToArray.end(), v2ToArray.begin(), T{});
    }
    template<typename T>
    constexpr Vector<T, 3> cross(const Vector<T, 3>& v1, const Vector<T, 3>& v2)
    {
        return Vector<T, 3>(std::array{
            v1[1] * v2[2] - v1[2] * v2[1],
            v1[2] * v2[0] - v1[0] * v2[2],
            v1[0] * v2[1] - v1[1] * v2[0],
        });
    };

    template<typename T, std::size_t S>
    constexpr auto length(const Vector<T, S>& v)
    {
        return std::sqrt(dot(v, v));
    };

    template<typename T, std::size_t S>
    constexpr Vector<T, S> normalize(const Vector<T, S>& v)
    {
        auto l = length(v);
        auto vToArray = v.toArray();
        std::array<T, S> result;
        std::transform(vToArray.begin(), vToArray.end(), result.begin(), [l](T val) {
            return val / l;
        });

        return Vector<T, S>(result);
    };
}