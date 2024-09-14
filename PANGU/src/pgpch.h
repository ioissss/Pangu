#pragma once

//预编译头，包含所有不需要改动的头文件，通过预编译减少编译时间 

#include<utility>
#include<functional>
#include<memory>
#include<string>
#include<stdint.h>
#include<sstream>
#include<unordered_map>
#include<unordered_set>
#include<vector>
//#include<array>

#include"PANGU/Log.h"
#include"glm/glm.hpp"

#ifdef PANGU_PLATFORM_WINDOWS
#include<Windows.h>
#endif // PG_PLATFORM_WINDOWS
