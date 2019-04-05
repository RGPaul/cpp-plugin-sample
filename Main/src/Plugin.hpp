//
//  Plugin.hpp
//
//  Created by Ralph-Gordon Paul on 5. Apr 2019
//  Copyright (c) 2019 Ralph-Gordon Paul. All rights reserved.
//

#pragma once

#include <string>

namespace appcom
{
class Plugin
{
public:
    explicit Plugin(std::string fileName);
    ~Plugin();

private:
    Plugin() = delete;
    Plugin(const Plugin &other) = delete;

    typedef const char*(*getNameType)();
    typedef void(*onLoadType)();
    typedef void(*onUnloadType)();

    getNameType _getName;
    onLoadType _onLoad;
    onUnloadType _onUnload;
};
} // namespace appcom
