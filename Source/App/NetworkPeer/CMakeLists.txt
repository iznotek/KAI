cmake_minimum_required(VERSION 3.7)

project(Peer)

set(SOURCE_ROOT ${SOURCE_HOME}/App/NetworkPeer/*.cpp)
file(GLOB_RECURSE SOURCE_FILES ${SOURCE_ROOT})

link_libraries(Executor Core PiLang RhoLang RakNetLibStatic)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/Bin")
add_executable(Peer ${SOURCE_FILES})
