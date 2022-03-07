project(moteur)

add_executable(moteur main.cpp)

set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL/include)

add_subdirectory(dep/SDL dep/SDL)
target_include_directories(moteur PRIVATE ${SDL_INCLUDE_DIR})
target_link_libraries(moteur PRIVATE SDL2-static SDL2main opengl32)