// Precompiled Header for Bell Engine Use
// --------------------------------------

#ifndef BPCH_H
#define BPCH_H


// ----- Common Engine Includes -----
// ----------------------------------

#include "Bell/Log.h"

// ----- Common C++ Includes -----
// -------------------------------

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// ----- Common Platform Specific Includes -----
// ---------------------------------------------

#ifdef B_PLATFORM_WINDOWS
    #include <Windows.h>
#endif

#endif // !BPCH_H