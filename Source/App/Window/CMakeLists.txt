cmake_minimum_required(VERSION 3.7)

set(name Window)
project(${name})

message(STATUS ******* Building Window )

find_package(OpenGL REQUIRED)

#add_definitions(-DKAI_PLATFORM_OSX)
# macOS set(frameworks OpenGL Cocoa IOKit CoreVideo)

##foreach(framework ${frameworks})
#set(${framework}_FIND_QUIETLY true) # doesn't seem to work?
#find_package(${framework})
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework ${framework}")
#endforeach()

include_directories(/opt/local/include ${KAI_HOME}/External)
link_directories(/opt/local/lib)


include_directories(${KAI_HOME}/External/imgui/examples/libs)
link_directories(${KAI_HOME}/External/imgui/examples/libs/glfw/lib-vc2010-64)

set(SOURCE_ROOT ${SOURCE_HOME}/App/${name}/Source/*.cpp)
file(GLOB_RECURSE SOURCE_FILES ${SOURCE_ROOT})

target_link_libraries(Executor Core PiLang RhoLang ImGui)

add_executable(${name} ${SOURCE_FILES})

# OpenGl
target_link_libraries(${name} glfw)

cotire(${name})
