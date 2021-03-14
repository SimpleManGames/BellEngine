// Precompiled Header for Bell Engine Use
// --------------------------------------

#ifndef _BPCH_H
#define _BPCH_H

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

#define _WINSOCKAPI_
#ifdef B_PLATFORM_WINDOWS
#include <Windows.h>
#endif

// ----- Common Engine Includes -----
// ----------------------------------

#include "Bell/Base/Log.h"
#include "Bell/Base/Debug/Assert.h"
#include "Bell/Debug/Instrumentor.h"

#endif // !_BPCH_H