//
//  Plugin.hpp
//
//  Created by Ralph-Gordon Paul on 5. Apr 2019
//  Copyright (c) 2019 Ralph-Gordon Paul. All rights reserved.
//

#pragma once

#include <string>

#if defined(_WIN32)
  #include <Windows.h>
#else // defined(_WIN32)
  #include <dlfcn.h>
#endif

namespace appcom
{
class Plugin
{
private:
    typedef const char*(*getNameType)();
    typedef void(*onLoadType)();
    typedef void(*onUnloadType)();

public:
    explicit Plugin(std::string fileName);
    ~Plugin();

    // accessors
    getNameType getName() const;
    onLoadType onLoad() const;
    onUnloadType onUnload() const;

private:
    Plugin() = delete;
    Plugin(const Plugin &other) = delete;

    getNameType _getName;
    onLoadType _onLoad;
    onUnloadType _onUnload;

#if defined(_WIN32)
    HINSTANCE _lib;
#else // defined(_WIN32)
    void* _lib;
#endif
};
} // namespace appcom
