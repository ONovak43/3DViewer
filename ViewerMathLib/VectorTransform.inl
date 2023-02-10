#pragma once

template<typename T, std::size_t S>
T VML::dot(const VML::Vector<T, S>& v1, const VML::Vector<T, S>& v2)
{
    auto v1ToArray = v1.toArray();
    auto v2ToArray = v2.toArray();
    return std::inner_product(v1ToArray.begin(), v1ToArray.end(), v2ToArray.begin(), T{});
};

template<typename T, std::size_t S>
auto VML::length(const VML::Vector<T, S>& v)
{
    return std::sqrt(VML::dot(v, v));
};

template<typename T, std::size_t S>
VML::Vector<T, S> VML::normalize(const VML::Vector<T, S>& v)
{
    auto length = VML::length(v);

    auto vToArray = v.toArray();
    std::array<T, S> result;
    std::transform(vToArray.begin(), vToArray.end(), result.begin(), [length](T val) {
        return val / length;
    });

    return VML::Vector<T, S>(result);
};
