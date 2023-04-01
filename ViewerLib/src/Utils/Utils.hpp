#pragma once

#include <fstream>
#include <string>
#include <type_traits>

namespace VL
{
    namespace Utils
    {
        template <typename E>
        constexpr typename std::underlying_type<E>::type to_underlying(E e) noexcept {
            return static_cast<typename std::underlying_type<E>::type>(e);
        }

        std::string readFile(const std::string& path);
    }
}

