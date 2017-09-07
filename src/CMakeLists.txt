cmake_minimum_required(VERSION 3.4.3)
project(lctoxy_exe CXX)

include_directories(${lctoxy_SOURCE_DIR})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${GSL_INCLUDE_DIR})
if (MSVC)
    link_directories($ENV{BOOST_LIBRARYDIR})
endif()

add_executable(lctoxy lctoxy.cpp)
target_link_libraries (
    lctoxy 
    ${Boost_LIBRARIES}
) 

install(
    TARGETS lctoxy 
    RUNTIME DESTINATION bin
    CONFIGURATIONS Release
)
