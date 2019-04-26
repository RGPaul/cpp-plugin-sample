//
//  Plugin.cpp
//
//  Created by Ralph-Gordon Paul on 5. Apr 2019
//  Copyright (c) 2019 Ralph-Gordon Paul. All rights reserved.
//

#include "Plugin.hpp"

appcom::Plugin::Plugin(std::string fileName)
{
#if defined(_WIN32)
  
    _lib = LoadLibrary(fileName.to_wstring().c_str());

    if (!_lib)
        throw "Couldn't load Plugin.";

    _getName = (getNameType)GetProcAddress(_lib, "getName");
    if (!_getName)
        throw "Couldn't found getName in Plugin.";

    _onLoad = (onLoadType)GetProcAddress(_lib, "onLoad");
    if (!_onLoad)
        throw "Couldn't found onLoad in Plugin.";

    _onUnload = (onUnloadType)GetProcAddress(_lib, "onUnload");
    if (!_onUnload)
        throw "Couldn't found onUnload in Plugin.";

#else // defined(_WIN32)

    _lib = dlopen(fileName.c_str(), RTLD_LAZY);

    if (!_lib)
        throw "Couldn't load Plugin.";

    // clear any existing error
    dlerror();

    char* error;

    _getName = (getNameType)dlsym(_lib, "getName");
    if ((error = dlerror()) != NULL)
        throw "Couldn't found getName in Plugin.";

    _onLoad = (onLoadType)dlsym(_lib, "onLoad");
    if ((error = dlerror()) != NULL)
        throw "Couldn't found onLoad in Plugin.";

    _onUnload = (onUnloadType)dlsym(_lib, "onUnload");
    if ((error = dlerror()) != NULL)
        throw "Couldn't found onUnload in Plugin.";

#endif
}
    
appcom::Plugin::~Plugin()
{
#if defined(_WIN32)

    if (_lib)
        FreeLibrary(_lib);

#else // defined(_WIN32)

    if (_lib)
        dlclose(_lib);

#endif
}

// accessors
appcom::Plugin::getNameType appcom::Plugin::getName() const { return _getName; }
appcom::Plugin::onLoadType appcom::Plugin::onLoad() const { return _onLoad; }
appcom::Plugin::onUnloadType appcom::Plugin::onUnload() const { return _onUnload; }
