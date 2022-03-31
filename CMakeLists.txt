cmake_minimum_required(VERSION 3.21)
project(moteur)


include(cmake/glew.cmake)

add_subdirectory(dep/SDL dep/SDL)

set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)


add_executable(moteur
		main.cpp
		BaseApp.cpp
		BaseApp.h
#		ScriptablePipeline/AppTriangle.cpp
#		ScriptablePipeline/AppTriangle.h
		Shaders/loadShader.cpp Shaders/loadShader.h
		helper/find_exe_path.cpp
		helper/find_exe_path.h
#		ScriptablePipeline/AppCube.cpp
#		ScriptablePipeline/AppCube.h
		helper/stb_image.h
		#helper/stb_image.cpp
		ScriptablePipeline/App.cpp
		ScriptablePipeline/App.h
		ScriptablePipeline/EngineObjects/Geometry.cpp
		ScriptablePipeline/EngineObjects/Geometry.h
		ScriptablePipeline/EngineObjects/Texture.cpp
		ScriptablePipeline/EngineObjects/Texture.h
		ScriptablePipeline/EngineObjects/Camera.cpp
		ScriptablePipeline/EngineObjects/Camera.h
		ScriptablePipeline/EngineObjects/EngineObject.cpp
		ScriptablePipeline/EngineObjects/EngineObject.h
		ScriptablePipeline/EngineObjects/Transform.cpp
		ScriptablePipeline/EngineObjects/Transform.h
		ScriptablePipeline/EngineObjects/GameObject.cpp
		ScriptablePipeline/EngineObjects/GameObject.h
		helper/ModelLoader.cpp
		helper/ModelLoader.h
        Minecraft/ChunkGeneration.cpp
        Minecraft/ChunkGeneration.h
		helper/FastNoiseLite.h
		ScriptablePipeline/EngineObjects/RenderingContext.cpp
		ScriptablePipeline/EngineObjects/RenderingContext.h
		Minecraft/Cube.cpp
		Minecraft/Cube.h
		Minecraft/Quad.cpp
		Minecraft/Quad.h
		ScriptablePipeline/EngineObjects/Skybox.cpp
		ScriptablePipeline/EngineObjects/Skybox.h
		ScriptablePipeline/EngineObjects/RenderedObject.cpp
		ScriptablePipeline/EngineObjects/RenderedObject.h)

set(IMGUI_USE_OGL3 true)
include(cmake/imgui.cmake)
include(cmake/assimp.cmake)

add_custom_target(copy_shaders COMMAND ${CMAKE_COMMAND}
		-E copy_directory ${CMAKE_SOURCE_DIR}/Shaders $<TARGET_FILE_DIR:moteur>/Shaders)
add_custom_target(copy_images COMMAND ${CMAKE_COMMAND}
		-E copy_directory ${CMAKE_SOURCE_DIR}/Images $<TARGET_FILE_DIR:moteur>/Images)
add_custom_target(copy_models COMMAND ${CMAKE_COMMAND}
		-E copy_directory ${CMAKE_SOURCE_DIR}/Models $<TARGET_FILE_DIR:moteur>/Models)

add_dependencies(moteur copy_shaders)
add_dependencies(moteur copy_images)
add_dependencies(moteur copy_models)
set_property(TARGET moteur PROPERTY CXX_STANDARD 17)

target_include_directories(moteur PRIVATE
		${SDL_INCLUDE_DIR}
		${GLM_INCLUDE_DIR}
		${IMGUI_INCLUDE_DIR}
		${ASSIMP_INCLUDE_DIR}
		)

target_link_libraries(moteur PRIVATE SDL2-static SDL2main opengl32 glew imgui assimp)
