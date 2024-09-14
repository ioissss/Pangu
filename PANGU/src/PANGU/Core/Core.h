#pragma once
#include<memory>
#ifdef PANGU_PLATFORM_WINDOWS
#if PANGU_DYNAMIC_LINK
	#ifdef PANGU_BUILD_DLL
		#define PANGU_API __declspec(dllexport)
	#else
		#define PANGU_API __declspec(dllimport)
	#endif
#else
#define PANGU_API
#define PANGU_API
#endif
#else
#error "PANGU support windows only now!"
#endif // PANGU_PLATFORM_WINDOWS

#define BIT(bit) 1 << bit

#ifdef PANGU_ENABLE_ASSERTS
#define PG_ASSERT(x,...) {if(!x){PG_ERROR("Assertion Failed: {0}",__VA_ARGS__); __debugbreak(); }}
#define PG_CORE_ASSERT(x,...){if(!x){PG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);__debugbreak(); }}
#else
#define PG_ASSERT(x,...) 
#define PG_CORE_ASSERT(x,...)
#endif // PANGU_ENABLE_ASSERTS

#define PG_BIND_FN(Fn) std::bind(&Fn,this,std::placeholders::_1)

const unsigned int MAX_SHADERS_NUM = 10;

namespace PANGU {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}