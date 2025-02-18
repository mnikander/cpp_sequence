#pragma once
#include <cstdint>
#include <vector>

// several useful datatypes which are const by default

namespace seq {

// primitive aliases
using b8           = const bool;
using c8           = const char;
using i32          = const int;
using i64          = const int64_t;
using f32          = const float;
using f64          = const double;
using mutable_b8   = bool;
using mutable_c8   = char;
using mutable_i32  = int;
using mutable_i64  = int64_t;
using mutable_f32  = float;
using mutable_f64  = double;

// vector aliases
using vb8          = const std::vector<bool>;
using vc8          = const std::vector<char>;
using vi32         = const std::vector<int>;
using vi64         = const std::vector<int64_t>;
using vf32         = const std::vector<float>;
using vf64         = const std::vector<double>;
using mutable_vb8  = std::vector<bool>;
using mutable_vc8  = std::vector<char>;
using mutable_vi32 = std::vector<int>;
using mutable_vi64 = std::vector<int64_t>;
using mutable_vf32 = std::vector<float>;
using mutable_vf64 = std::vector<double>;

}
