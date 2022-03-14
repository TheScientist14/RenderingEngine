cmake_minimum_required(VERSION 3.21)
project(moteur)

include(cmake/imgui.cmake)
include(cmake/glew.cmake)


add_subdirectory(dep/SDL dep/SDL)

set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)
set(IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/imgui)
#set_property(TARGET moteur PROPERTY CXX_STANDARD 17)

add_executable(moteur
		main.cpp
		BaseApp.cpp
		BaseApp.h
		ScriptablePipeline/AppTriangle.cpp
		ScriptablePipeline/AppTriangle.h
		Shaders/loadShader.cpp Shaders/loadShader.h
		helper/find_exe_path.cpp
		helper/find_exe_path.h
		ScriptablePipeline/AppCube.cpp
		ScriptablePipeline/AppCube.h
		helper/stb_image.h helper/stb_image.cpp ScriptablePipeline/App.cpp ScriptablePipeline/App.h ScriptablePipeline/EngineObjects/Geometry.cpp ScriptablePipeline/EngineObjects/Geometry.h ScriptablePipeline/EngineObjects/Texture.cpp ScriptablePipeline/EngineObjects/Texture.h ScriptablePipeline/EngineObjects/Camera.cpp ScriptablePipeline/EngineObjects/Camera.h ScriptablePipeline/EngineObjects/EngineObject.cpp ScriptablePipeline/EngineObjects/EngineObject.h ScriptablePipeline/EngineObjects/Transform.cpp ScriptablePipeline/EngineObjects/Transform.h ScriptablePipeline/EngineObjects/GameObject.cpp ScriptablePipeline/EngineObjects/GameObject.h)
target_include_directories(moteur PRIVATE
	${SDL_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
	${IMGUI_INCLUDE_DIR}
)
target_link_libraries(moteur PRIVATE SDL2-static SDL2main opengl32 glew )