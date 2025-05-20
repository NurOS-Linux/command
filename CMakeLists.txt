cmake_minimum_required(VERSION 3.16)
project(aether_command VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Настройка компилятора clang
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")

find_package(Qt6 REQUIRED COMPONENTS Widgets Core)
find_package(PkgConfig REQUIRED)
pkg_check_modules(QTERMWIDGET REQUIRED qtermwidget6)

add_executable(aether_command
    main.cpp
)

target_link_libraries(aether_command PRIVATE
    Qt6::Widgets
    Qt6::Core
    ${QTERMWIDGET_LIBRARIES}
)

target_include_directories(aether_command PRIVATE
    ${QTERMWIDGET_INCLUDE_DIRS}
)

target_compile_definitions(aether_command PRIVATE
    QT_NO_CAST_FROM_ASCII
    QT_NO_CAST_TO_ASCII
)

# Дополнительные флаги для clang
target_compile_options(aether_command PRIVATE
    -Wall
    -Wextra
    -O2
    -pipe
)