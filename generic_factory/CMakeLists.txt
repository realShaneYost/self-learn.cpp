set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(TARGET_NAME app)
cmake_minimum_required(VERSION 4.0)
project(${TARGET_NAME} LANGUAGES CXX)
file(GLOB SOURCES CONFIGURE_DEPENDS *.cpp)
add_executable(${TARGET_NAME} ${SOURCES})
target_include_directories(
    ${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
find_package(Threads REQUIRED)
target_link_libraries(
    ${TARGET_NAME} PRIVATE
    Threads::Threads
)
target_compile_options(
    ${TARGET_NAME} PRIVATE
    -Wall -Wextra -Wpedantic -Werror
)

