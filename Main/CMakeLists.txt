#
#  CMakeLists.txt
#
#  Created by Ralph-Gordon Paul on 13.06.2017
#  Copyright (c) 2017 appcom interactive GmbH. All rights reserved.
#

cmake_minimum_required (VERSION 3.6)
project (myapp)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# For Visual Studio Code
include(CMakeToolsHelpers OPTIONAL)

# debug flags
set(CMAKE_C_FLAGS_DEBUG "-DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG")

# we prefer libraries over frameworks
set(CMAKE_FIND_FRAMEWORK LAST)

# on unix systems, the dependencies might be installed under /usr/local/lib /usr/local/include
if(UNIX)
  set(CMAKE_PREFIX_PATH "/usr/local/")
  set(CMAKE_INCLUDE_PATH "/usr/local/include/" CACHE FILEPATH "Path to headers (include) for third party libraries")
  set(CMAKE_LIBRARY_PATH "/usr/local/lib/" CACHE FILEPATH "Path to third party libraries")
  include_directories(BEFORE ${CMAKE_INCLUDE_PATH})
  link_directories(${CMAKE_LIBRARY_PATH})
endif()

# on windows systems, the dependencies might be installed under C:/lib and C:/include
if (WIN32)
  set(CMAKE_INCLUDE_PATH "C:/include" CACHE FILEPATH "Path to headers (include) for third party libraries")
  set(CMAKE_LIBRARY_PATH "C:/lib" CACHE FILEPATH "Path to third party libraries")
  include_directories(BEFORE ${CMAKE_INCLUDE_PATH})
  link_directories(${CMAKE_LIBRARY_PATH})
endif()

# setup clang compiler options
if((CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
  message("Setting clang options")
#  set (CMAKE_CXX_FLAGS "-std=c++17 -stdlib=libc++")
endif()

### link external libraries ###

# Boost - https://www.boost.org
find_package(Boost COMPONENTS filesystem log system)

### create executable ###
add_executable(myapp
               src/main.cpp
               src/Plugin.cpp)

### link libraries ###
# target_link_directories(myapp PUBLIC ${Boost_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# for Linux, BSD, Solaris, Minix - add posix thread library
if(UNIX AND NOT APPLE)
  target_link_libraries(myapp dl pthread)
endif()

# installation 
install(TARGETS myapp
    RUNTIME DESTINATION bin)
