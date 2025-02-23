// Copyright (c) 2025, Marco Nikander

#pragma once
#include <cassert>
#include <concepts>
#include <utility> // forward
#include "../src/datatypes.hpp"

namespace seq {
namespace proto {
namespace con {

// tests that the successor is capable of receiving
template<typename S>
concept Receiver = requires(typename S::Input&& value, S& successor){
    { successor.receive(std::forward<typename S::Input>(value)) } -> std::same_as<Status>;
};

}
}
}
