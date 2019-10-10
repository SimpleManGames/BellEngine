// Precompiled Header for Bell Engine Use
// --------------------------------------

#ifndef _BPCH_H
#define _BPCH_H


// ----- Common Engine Includes -----
// ----------------------------------

#include "Bell/Core/Log.h"

// ----- Common C++ Includes -----
// -------------------------------

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <array>

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

#endif // !_BPCH_H