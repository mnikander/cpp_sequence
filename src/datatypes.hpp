#pragma once
#include <cstdint>
#include <vector>

// several useful datatypes which are const by default

namespace seq {

// primitive aliases
using b8       = const bool;
using c8       = const char;
using i32      = const int;
using i64      = const int64_t;
using f32      = const float;
using f64      = const double;
using mut_b8   = bool;
using mut_c8   = char;
using mut_i32  = int;
using mut_i64  = int64_t;
using mut_f32  = float;
using mut_f64  = double;

// vector aliases
using vb8      = const std::vector<bool>;
using vc8      = const std::vector<char>;
using vi32     = const std::vector<int>;
using vi64     = const std::vector<int64_t>;
using vf32     = const std::vector<float>;
using vf64     = const std::vector<double>;
using mut_vb8  = std::vector<bool>;
using mut_vc8  = std::vector<char>;
using mut_vi32 = std::vector<int>;
using mut_vi64 = std::vector<int64_t>;
using mut_vf32 = std::vector<float>;
using mut_vf64 = std::vector<double>;

}
