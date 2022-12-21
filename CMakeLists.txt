cmake_minimum_required(VERSION 3.14)

project(Pong LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/Pong)

set(INC_PATH ${PROJECT_SOURCE_DIR}/_include_libs)

set(SDL2_DIR ${INC_PATH}/SDL2-2.24.2)
set(SDL2_ttf_DIR ${INC_PATH}/SDL2_ttf-2.20.1)
set(SDL2_image_DIR ${INC_PATH}/SDL2_image-2.6.2)


add_executable(Pong
	${PROJECT_SOURCE_DIR}/main.cpp
	${PROJECT_SOURCE_DIR}/Ball.h
	${PROJECT_SOURCE_DIR}/Ball.cpp
	${PROJECT_SOURCE_DIR}/GameManager.h
	${PROJECT_SOURCE_DIR}/GameManager.cpp
	${PROJECT_SOURCE_DIR}/GameState.h
	${PROJECT_SOURCE_DIR}/Player.h
	${PROJECT_SOURCE_DIR}/Player.cpp
	${PROJECT_SOURCE_DIR}/SDLScene.h
	${PROJECT_SOURCE_DIR}/SDLScene.cpp
	${PROJECT_SOURCE_DIR}/TextureLoader.h
	${PROJECT_SOURCE_DIR}/TextureLoader.cpp
)

if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  set(SDL2_LIBRARIES "${SDL2_DIR}/lib/x64/SDL2.lib;${SDL2_DIR}/lib/x64/SDL2main.lib")
  set(SDL2_ttf_LIBRARIES "${SDL2_ttf_DIR}/lib/x64/SDL2_ttf.lib")
  set(SDL2_image_LIBRARIES "${SDL2_image_DIR}/lib/x64/SDL2_image.lib")
  set(SDL_DLLS "${SDL2_DIR}/lib/x64/SDL2.dll;${SDL2_ttf_DIR}/lib/x64/SDL2_ttf.dll;${SDL2_image_DIR}/lib/x64/SDL2_image.dll")
else ()
  set(SDL2_LIBRARIES "${SDL2_DIR}/lib/x86/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/lib/x86/SDL2main.lib")
  set(SDL2_ttf_LIBRARIES "${SDL2_ttf_DIR}/lib/x86/SDL2_ttf.lib")
  set(SDL2_image_LIBRARIES "${SDL2_image_DIR}/lib/x86/SDL2_image.lib")
    set(SDL_DLLS "${SDL2_DIR}/lib/x86/SDL2.dll;${SDL2_ttf_DIR}/lib/x86/SDL2_ttf.dll;${SDL2_image_DIR}/lib/x86/SDL2_image.dll")
endif ()

target_link_libraries(Pong ${SDL2_LIBRARIES})
target_link_libraries(Pong ${SDL2_ttf_LIBRARIES})
target_link_libraries(Pong ${SDL2_image_LIBRARIES})

include_directories(Pong ${SDL2_DIR}/include)
include_directories(Pong ${SDL2_ttf_DIR}/include)
include_directories(Pong ${SDL2_image_DIR}/include)

add_custom_command(TARGET Pong POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${SDL_DLLS} ${PROJECT_BINARY_DIR}
)

add_custom_command(TARGET Pong POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/asset ${PROJECT_BINARY_DIR}/asset
)

add_custom_command(TARGET Pong POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/fonts ${PROJECT_BINARY_DIR}/fonts
)