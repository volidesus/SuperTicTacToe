cmake_minimum_required(VERSION 3.10)
project(supertictactoe VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(RAYLIB_INCLUDE_DIR "D:/vcpkg/installed/x64-windows/include")
set(RAYLIB_LIBRARY "D:/vcpkg/installed/x64-windows/lib/raylib.lib")

include_directories(${RAYLIB_INCLUDE_DIR})

add_executable(${PROJECT_NAME}
    main.c
    draw.c
    bot.c
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB_LIBRARY})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
