cmake_minimum_required(VERSION 3.20)
project(mine LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Opcional: Ninja -> cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug

# GLAD via FetchContent
include(FetchContent)
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v2.0.4
)
FetchContent_MakeAvailable(glad)

# GLM via FetchContent (ou use glm-devel do Fedora e remova esta seção)
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e
)
FetchContent_MakeAvailable(glm)

find_package(OpenGL REQUIRED)       # fornece OpenGL::GL
find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)

# GLFW do sistema
find_package(glfw3 REQUIRED)

# Fontes
set(SOURCE_FILES
  src/main.cpp
  src/Game/Game.cpp
  src/Game/Game.hpp
  src/World/Block/Block.cpp
  src/World/Block/Block.hpp
  src/debug/colors.cpp
  src/debug/colors.h
  src/GameHelpers/Camera/Camera.cpp
  src/GameHelpers/Camera/Camera.hpp
  src/World/Sphere/Sphere.cpp
  src/World/Sphere/Sphere.hpp
  src/GameHelpers/Miscellaneous/GameHelper.cpp
  src/GameHelpers/Miscellaneous/GameHelper.hpp
  src/Texture/Texture.cpp
  src/Texture/Texture.hpp
  src/World/Primitive/Primitive.cpp      # corrigido: remove "//"
  src/World/Primitive/Primitive.hpp
  src/GameHelpers/Callbacks/Callbacks.cpp
  src/GameHelpers/Callbacks/Callbacks.hpp
  src/World/Terrain/Terrain.cpp
  src/World/Terrain/Terrain.hpp
  src/World/WorldGen/Chunk.cpp
  src/World/WorldGen/Chunk.hpp
  src/debug/ImGui.cpp
  src/debug/ImGui.hpp
)

# ImGui (use apenas backends GL3 + GLFW no Linux)
set(IMGUI_FILES
  vendor/imgui/imgui.cpp
  vendor/imgui/imgui_demo.cpp
  vendor/imgui/imgui_draw.cpp
  vendor/imgui/imgui_tables.cpp
  vendor/imgui/imgui_widgets.cpp
  vendor/imgui/backends/imgui_impl_glfw.cpp
  vendor/imgui/backends/imgui_impl_opengl3.cpp
)

add_executable(mine
  ${SOURCE_FILES}
  ${IMGUI_FILES}
)

# Includes do projeto
target_include_directories(mine PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/vendor/imgui
  ${CMAKE_SOURCE_DIR}/vendor/imgui/backends
)

# Definições para ImGui OpenGL3 backend com GLAD
target_compile_definitions(mine PRIVATE
  IMGUI_IMPL_OPENGL_LOADER_GLAD
  # Ajuste o GLSL almejado conforme sua pipeline
  IMGUI_IMPL_OPENGL_ES3=0
)

# Linkagem
target_link_libraries(mine PRIVATE
  glad::glad
  glfw
  OpenGL::GL
  Threads::Threads
  glm::glm
)

# Em alguns ambientes pode precisar de dl
find_library(LIB_DL dl)
if(LIB_DL)
  target_link_libraries(mine PRIVATE ${LIB_DL})
endif()

