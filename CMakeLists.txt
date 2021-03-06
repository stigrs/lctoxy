cmake_minimum_required(VERSION 3.4.3)
project(lctoxy CXX)

# By default, ChemApps is install in the HOME directory.
if(WIN32)
    set(CMAKE_INSTALL_PREFIX "C:/Users/$ENV{USERNAME}")
else()
    set(CMAKE_INSTALL_PREFIX $ENV{HOME})
endif()

# Export compile commands.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enforce C++14 standard (needed for GSL).
set(CMAKE_CXX_STANDARD 14)

# Set release compiler options.
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wpedantic -Wall -Wshadow -Wextra -Wno-missing-braces -Werror")
endif()
if(APPLE)
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -framework Accelerate")
endif()
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "/std:c++14 /W4 /WX /GR /EHsc /MT /O2")
endif()

# Set debugging compiler options.
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pg -Wpedantic -Wall -Wshadow -Wextra -Wno-missing-braces -Werror")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -pg")
endif()
if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "/std:c++14 /EHsc /W4 /WX /MT /GR /Zi /Od")
endif()

# Set definitions.
set(lctoxy_DEFINITIONS_DEBUG -DGSL_THROW_ON_CONTRACT_VIOLATION)
set(lctoxy_DEFINITIONS_RELEASE -DNDEBUG -DARMA_NO_DEBUG -DGSL_THROW_ON_CONTRACT_VIOLATION)
add_compile_options(
    "$<$<CONFIG:Debug>:${lctoxy_DEFINITIONS_DEBUG}>"
    "$<$<CONFIG:Release>:${lctoxy_DEFINITIONS_RELEASE}>" 
)

# Boost library is required.
if(MSVC)
    set(Boost_USE_STATIC_LIBS ON)
endif()
find_package(Boost 1.65.0 COMPONENTS program_options REQUIRED)

# GSL library is required.
find_path(GSL_INCLUDE_DIR gsl HINTS $ENV{HOME}/include /usr/include /usr/local/include)

add_subdirectory(src)
