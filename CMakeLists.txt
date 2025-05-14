cmake_minimum_required(VERSION 3.16)
project(MediaLibrary VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QT
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

# Files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/**/*.cpp src/**/*.h)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

enable_testing()
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS src/test*.cpp)

foreach(test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_include_directories(${test_name} PRIVATE src)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
