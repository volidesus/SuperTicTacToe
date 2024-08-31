cmake_minimum_required(VERSION 3.10)
project(supertictactoe VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories("D:/Raylib-5.0/include")
link_directories("D:/Raylib-5.0/lib")

add_executable(${PROJECT_NAME}
    main.cpp
    draw.cpp
    bot.cpp
)

target_link_libraries(${PROJECT_NAME} raylib.lib)
target_link_libraries(${PROJECT_NAME} winmm.lib)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)