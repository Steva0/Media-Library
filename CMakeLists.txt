cmake_minimum_required(VERSION 3.16)

project(MediaLibrary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Trova Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

# Includi tutti i file .cpp e .h dentro src e sottocartelle
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/**/*.cpp src/**/*.h)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)

# Output in ./build
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
