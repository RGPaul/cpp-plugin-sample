//
//  main.cpp
//
//  Created by Ralph-Gordon Paul on 5. Apr 2019
//  Copyright (c) 2019 Ralph-Gordon Paul. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>

#include "Plugin.hpp"

std::vector<std::shared_ptr<appcom::Plugin>> plugins;

boost::program_options::variables_map readArgs(const int argc, const char** argv);

std::shared_ptr<appcom::Plugin> loadPlugin(const std::string& path);

int main(const int argc, const char** argv)
{
    // boost::filesystem::path libraryPath = "";

    boost::program_options::variables_map vm = readArgs(argc, argv);

    if (vm.count("plugin"))
    {
        std::vector<std::string> pluginPaths = vm["plugin"].as<std::vector<std::string>>();

        for (const std::string& pluginPath : pluginPaths)
        {
            std::cout << "Load plugin file: " << pluginPath << std::endl;

            std::shared_ptr<appcom::Plugin> plugin = loadPlugin(pluginPath);
            plugins.emplace_back(plugin);

            std::cout << "Plugin name: " << plugin->getName() << std::endl;
        }
    }
    else
    {
        std::cout << "No plugin specified." << std::endl;
    }

    for (auto it = plugins.begin(); it != plugins.end();)
    {
        it = plugins.erase(it);
    }

    return EXIT_SUCCESS;
}

boost::program_options::variables_map readArgs(const int argc, const char** argv)
{
    namespace po = boost::program_options;

    // declare variable map that will be filled with given args
    po::variables_map vm;

    // Setup option description
    po::options_description description("Allowed options");
    description.add_options()("help", "print help message")("plugin", po::value<std::vector<std::string>>(),
                                                            "use specified plugin");

    // parse args into vm
    po::store(po::parse_command_line(argc, argv, description), vm);
    po::notify(vm);

    // check if the help parameter was specified
    if (vm.count("help"))
    {
        std::cout << description << std::endl;
        std::exit(EXIT_SUCCESS);
    }

    return vm;
}

std::shared_ptr<appcom::Plugin> loadPlugin(const std::string& path)
{
    std::shared_ptr<appcom::Plugin> plugin = std::make_shared<appcom::Plugin>(path);

    plugin->onLoad();

    return plugin;
}
