cmake_minimum_required(VERSION 3.9)
project(untitled)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_PREFIX_PATH "/Applications/Qt/5.10.1/clang_64")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(include)
link_directories(lib)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SRC src/*.cpp src/*.h)
add_executable(untitled ${SRC})
qt5_use_modules(untitled Widgets OpenGL)
target_link_libraries(untitled ${QT_LIBRARIES} ${OPENGL_LIBRARIES} imebra)

add_custom_command(
        TARGET untitled POST_BUILD
        COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
)