#pragma once

#ifdef _WIN64
	#define PLATFORM_WINDOWS 1	
#else
	#error "Only Windows x64 platform is supported."
#endif

#if _DEBUG
	#ifdef PLATFORM_WINDOWS
		#define debugBreak() __debugbreak()
	#else
		#error "Only Windows x64 platform is supported for debugging."
	#endif

	#define ASSERTIONS_ENABLED 1
#endif

#if ASSERTIONS_ENABLED
	// check the expression and fail if it is false
	#define ASSERT(expr, msg) \
	if (expr) { } \
	else \
	{ \
		std::cerr << #msg << " EXPRESSION: " << #expr << " IN FILE: " << __FILE__ << " AT LINE: " << __LINE__ << "\n"; \
		debugBreak(); \
	}
#else
	#define ASSERT(expr) // evaluates to nothing
#endif

#define STACK_ALLOCATOR_SIZE 2048