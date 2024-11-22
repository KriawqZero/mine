cmake_minimum_required(VERSION 3.29)
project(mine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Encontrar e incluir OpenGL
find_package(OpenGL REQUIRED)

# Incluir diretórios para GLFW
include_directories(${CMAKE_SOURCE_DIR}/vendor/OpenGL/include
                    ${CMAKE_SOURCE_DIR}/source/include
                    ${CMAKE_SOURCE_DIR}/vendor/stb_image
                    ${CMAKE_SOURCE_DIR}/vendor/imgui
                    ${CMAKE_SOURCE_DIR}/vendor/imgui/backends)
link_directories(${CMAKE_SOURCE_DIR}/vendor/OpenGL/lib)

add_custom_target(glutdlllib
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/vendor/OpenGL/lib/glut32.dll ${CMAKE_BINARY_DIR}
)

# required .lib files to be copied into compiler's proper directory
set(OpenGlLibs glut32)

include(FetchContent)
FetchContent_Declare(
        glm
        GIT_REPOSITORY	https://github.com/g-truc/glm.git
        GIT_TAG 	    bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
)
FetchContent_MakeAvailable(glm)

# Definir os arquivos fonte
set(SOURCE_FILES sources/main.cpp

                 sources/Game/Game.cpp
                 sources/Game/Game.hpp

                 sources/World/Block/Block.cpp
                 sources/World/Block/Block.hpp

                 sources/debug/colors.cpp
                 sources/debug/colors.h

                 sources/GameHelpers/Camera/Camera.cpp
                 sources/GameHelpers/Camera/Camera.hpp

                 sources/World/Sphere/Sphere.cpp
                 sources/World/Sphere/Sphere.hpp

                 sources/GameHelpers/Miscellaneous/GameHelper.cpp
                 sources/GameHelpers/Miscellaneous/GameHelper.hpp

                 sources/Texture/Texture.cpp
                 sources/Texture/Texture.hpp

                 sources//World/Primitive/Primitive.cpp
                 sources/World/Primitive/Primitive.hpp

                 sources/GameHelpers/Callbacks/Callbacks.cpp
                 sources/GameHelpers/Callbacks/Callbacks.hpp

                 sources/World/Terrain/Terrain.cpp
                 sources/World/Terrain/Terrain.hpp

                 sources/World/WorldGen/Chunk.cpp
                 sources/World/WorldGen/Chunk.hpp

                 sources/debug/ImGui.cpp
                 sources/debug/ImGui.hpp)

set(RESOURCE_FILES resources/resources.rc)
set(IMGUI_FILES vendor/imgui/backends/imgui_impl_glfw.cpp
                vendor/imgui/backends/imgui_impl_glfw.h
                vendor/imgui/backends/imgui_impl_opengl2.cpp
                vendor/imgui/backends/imgui_impl_opengl2.h
                vendor/imgui/backends/imgui_impl_opengl3.cpp
                vendor/imgui/backends/imgui_impl_opengl3.h
                vendor/imgui/imgui.cpp
                vendor/imgui/imgui.h
                vendor/imgui/imgui_demo.cpp
                vendor/imgui/imgui_draw.cpp
                vendor/imgui/imgui_internal.h
                vendor/imgui/imgui_tables.cpp
                vendor/imgui/imgui_widgets.cpp)

add_executable(mine ${SOURCE_FILES} ${RESOURCE_FILES} ${IMGUI_FILES})

# Ligar bibliotecas necessárias
target_link_libraries(mine ${OPENGL_LIBRARIES} ${OpenGlLibs} glfw3 opengl32 glm::glm)
add_dependencies(mine glutdlllib)