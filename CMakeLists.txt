# CMakeList.txt : CMake project for OpenEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project(OpenEngine VERSION 1.0 DESCRIPTION "C++ OpenGL Game Engine")

find_package(OpenGL REQUIRED)

include_directories(includes ${CMAKE_CURRENT_SOURCE_DIR}/includes)
include_directories(misc ${CMAKE_CURRENT_SOURCE_DIR}/misc)
include_directories(engine ${CMAKE_CURRENT_SOURCE_DIR}/Engine)

add_library(

	ASWLLib STATIC

	# Math
	${CMAKE_CURRENT_SOURCE_DIR}/misc/ASWL/math.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/misc/ASWL/math.cpp

	# Utilities
	${CMAKE_CURRENT_SOURCE_DIR}/misc/ASWL/utilities.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/misc/ASWL/utilities.cpp
)

add_library(

	EngineLib STATIC

	# Main
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/engine.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/engine.cpp

	# Physics
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Physics/collision.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Physics/collision.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Physics/rigidbody.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Physics/rigidbody.cpp

	# Math
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Math/math.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Math/math.cpp

	# Audio
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Audio/audio.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Audio/audio.cpp

	# Input
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Input/keyboard.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Input/keyboard.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Input/keymap.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Input/keymap.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Input/mouse.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Input/mouse.cpp

	# User-Interface
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/UI/button.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/UI/button.cpp

	# Graphics
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/graphics.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/graphics.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/2D/buffer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/2D/buffer.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/2D/orthocam.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/2D/orthocam.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/2D/renderer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/2D/renderer.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/2D/shader.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/2D/shader.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/2D/splashscreen.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/2D/splashscreen.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/2D/sprite.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/2D/sprite.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/2D/spritesheet.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/2D/spritesheet.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/2D/texture.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/2D/texture.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/2D/vertexarray.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/OpenEngine/Graphics/2D/vertexarray.cpp
)

# Add source to the project's executable.
add_executable(OpenEngine "main.cpp")

# Link Libraries
target_link_libraries(OpenEngine PRIVATE ASWLLib)
target_link_libraries(OpenEngine PRIVATE EngineLib)

# -> Assimp ???
# -> GLAD
add_library(GLAD STATIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/GLAD/src/glad.c)
target_link_libraries(OpenEngine PRIVATE GLAD)
# -> GLFW3
target_link_libraries(OpenEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib)
# -> GLM
# header files only, no library to link
# -> irrKlang
target_link_libraries(OpenEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/irrKlang.lib)
# -> STBI
add_library(STBI STATIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/STBI/stb_image.cpp)
target_link_libraries(OpenEngine PRIVATE STBI)
