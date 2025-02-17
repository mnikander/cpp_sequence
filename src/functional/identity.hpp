#pragma once

#include <utility> // forward

namespace seq {

struct Identity {
    template <typename T>
    constexpr auto operator()(T&& v) const noexcept -> decltype(std::forward<T>(v))
    {
        return std::forward<T>(v);
    }

    template <typename E, typename T>
    constexpr void operator()(E emit, T&& v) const noexcept
    {
        emit(std::forward<T>(v));
    }
};

}
