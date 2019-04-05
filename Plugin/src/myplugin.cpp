//
//  myplugin.cpp
//
//  Created by Ralph-Gordon Paul on 5. Apr 2019
//  Copyright (c) 2019 Ralph-Gordon Paul. All rights reserved.
//

#include "myplugin.hpp"

#include <iostream>

const char* appcom::plugin::getName()
{
    return "Sample Plugin";
}

void appcom::plugin::onLoad()
{
    std::cout << "Plugin onLoad!" << std::endl;
}

void appcom::plugin::onUnload()
{
    std::cout << "Plugin onUnload!" << std::endl;
}
