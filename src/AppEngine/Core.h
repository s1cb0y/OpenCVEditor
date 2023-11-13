#pragma once

// TODO shift those into precompiled header
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <functional>
#include <memory>
#include <sstream>

#include "AppEngine/Log.h"
#include "AppEngine/PlatformDetection.h"

#define BIT(x) (1 << x)

#define BIND_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#ifdef APP_DEBUG
	#if defined(APP_PLATFORM_WINDOWS)
		#define APP_DEBUGBREAK() __debugbreak()
	#elif defined(APP_PLATFORM_LINUX)
		#include <signal.h>
		#define APP_DEBUGBREAK() raise(SIGTRAP)
	#elif defined(APP_PLATFORM_MACOS)
      #define APP_DEBUG_BREAK asm {trap} 
   #else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define APP_ENABLE_ASSERTS
#else
	#define APP_DEBUGBREAK()
#endif

#ifndef APP_DEBUG
   #define APP_ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
   #define APP_ASSERT(condition, message) 
#endif


