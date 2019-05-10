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
#else  // defined(_WIN32)
#include <dlfcn.h>
#endif

namespace appcom
{
class Plugin
{
  private:
    typedef const char* (*getNameType)();
    typedef void (*onLoadType)();
    typedef void (*onUnloadType)();

  public:
    explicit Plugin(std::string fileName);
    ~Plugin();

    // accessors
    const char* getName() const;

    // methods
    void onLoad() const;

  private:
    Plugin() = delete;
    Plugin(const Plugin& other) = delete;

    getNameType _getName {nullptr};
    onLoadType _onLoad {nullptr};
    onUnloadType _onUnload {nullptr};

#if defined(_WIN32)
    HINSTANCE _lib;
#else  // defined(_WIN32)
    void* _lib;
#endif
};
}  // namespace appcom
