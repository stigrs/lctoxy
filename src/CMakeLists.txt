cmake_minimum_required(VERSION 3.4.3)
project(lctoxy_exe CXX)

include_directories(${lctoxy_SOURCE_DIR})
include_directories(${Boost_INCLUDE_DIRS})
if (MSVC)
    link_directories($ENV{BOOST_LIBRARYDIR})
endif()

add_executable(lctoxy lctoxy.cpp)
target_link_libraries (
    ${program} 
    ${Boost_LIBRARIES}
) 

install(
    TARGETS ${PROGRAMS}
    RUNTIME DESTINATION bin
    CONFIGURATIONS Release
)
