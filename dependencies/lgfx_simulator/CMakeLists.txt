cmake_minimum_required(VERSION 3.5)
project(lgfx)

set(LGFX_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../LovyanGFX)
if(NOT EXISTS "${LGFX_ROOT_DIR}")
    message(FATAL_ERROR "LGFX_ROOT_DIR (${LGFX_ROOT_DIR}) does not exist!")
endif()

add_definitions(-DLGFX_SDL)

cmake_policy(SET CMP0077 NEW)
set(CMAKE_CXX_STANDARD 17)

file(GLOB LGFX_SIMU_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS
    ${LGFX_ROOT_DIR}/src/lgfx/Fonts/efont/*.c
    ${LGFX_ROOT_DIR}/src/lgfx/Fonts/IPA/*.c
    ${LGFX_ROOT_DIR}/src/lgfx/utility/*.c
    ${LGFX_ROOT_DIR}/src/lgfx/v1/*.cpp
    ${LGFX_ROOT_DIR}/src/lgfx/v1/misc/*.cpp
    ${LGFX_ROOT_DIR}/src/lgfx/v1/panel/Panel_Device.cpp
    ${LGFX_ROOT_DIR}/src/lgfx/v1/panel/Panel_FrameBufferBase.cpp
    ${LGFX_ROOT_DIR}/src/lgfx/v1/platforms/sdl/*.cpp
)

add_library(${PROJECT_NAME}_lib ${LGFX_SIMU_SRCS})
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${LGFX_ROOT_DIR}/src)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    find_package(SDL2 REQUIRED SDL2)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME}_lib -lpthread ${SDL2_LIBRARIES})
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    find_package(SDL2 CONFIG REQUIRED)

    target_link_libraries(${PROJECT_NAME}_lib
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    )
    # # Windows環境の場合;
    # # SDL2を配置したパス内のincludeのパスを指定する;
    # target_include_directories(LGFX_SDL PUBLIC "C:/SDL2/include")

    # # SDL2を配置したパス内の.libファイルのパスを指定する;
    # target_link_libraries(LGFX_SDL PUBLIC "C:/SDL2/lib/x64/SDL2.lib")


    # add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    # add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    # add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>")

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    find_package(SDL2 REQUIRED COMPONENTS SDL2)
    target_link_libraries(${PROJECT_NAME}_lib PRIVATE SDL2::SDL2)
ENDIF ()

option(LGFX_SIMULATOR_BUILD "simulator example" ON)

# Example
if(LGFX_SIMULATOR_BUILD)
    add_subdirectory(example/fps_show)
    add_subdirectory(example/random)
endif()

# # CTest
# enable_testing()
# add_test(basic example/basic)

