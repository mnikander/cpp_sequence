#pragma once
#include <cstdint>
#include <vector>

namespace seq {

// primitive aliases
using b8   = bool;
using c8   = char;
using i32  = int;
using i64  = int64_t;
using f32  = float;
using f64  = double;

// vector aliases
using vb8  = std::vector<bool>;
using vc8  = std::vector<char>;
using vi32 = std::vector<int>;
using vi64 = std::vector<int64_t>;
using vf32 = std::vector<float>;
using vf64 = std::vector<double>;

// like an enum, but I really do want it to be a `bool` under the surface
using Status = bool;
constexpr Status OK   = true;
constexpr Status HALT = false;

}
