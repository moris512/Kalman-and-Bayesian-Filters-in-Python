//CPP Version of Chapter 1 G-H Filter
#include <iostream>    // Standard I/O streams
#include <vector>      // For std::vector
#include <string>      // For std::string
#include <map>         // For std::map
#include <set>         // For std::set
#include <tuple>       // For std::tuple and structured bindings (C++17)
#include <fstream>     // For file I/O
#include <stdexcept>   // For exceptions
#include <algorithm>   // For standard algorithms
#include <ranges>      // For C++20 ranges (optional)
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;
int main() {
    plt::plot({1,3,2,4});
    plt::show();
}