//
//  myplugin.hpp
//
//  Created by Ralph-Gordon Paul on 5. Apr 2019
//  Copyright (c) 2019 Ralph-Gordon Paul. All rights reserved.
//

#pragma once

// on windows we need exports for creating the dll
#if defined(_WIN32)
  #define DLL_EXPORT __declspec(dllexport)
#else // defined(_WIN32)
  #define DLL_EXPORT
#endif

namespace appcom
{
namespace plugin
{
extern "C"
{
    DLL_EXPORT const char* getName();
    DLL_EXPORT void onLoad();
    DLL_EXPORT void onUnload();

} // extern "C"
} // namespace plugin
} // namespace appcom
