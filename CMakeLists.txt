cmake_minimum_required(VERSION 3.16)

project(MediaLibraryBuild VERSION 1.0 LANGUAGES CXX)

# Qt5: automatizza moc, uic, rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Raccoglie tutti i file .cpp e .h nella cartella src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h)

# Crea l'eseguibile principale
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE src)

# Trova e linka le librerie Qt necessarie
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Widgets Qt5::Gui)

# Imposta la cartella output dell'eseguibile
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Abilita il supporto ai test
enable_testing()

# Test (facoltativi)
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS src/test*.cpp)

foreach(test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_include_directories(${test_name} PRIVATE src)
    target_link_libraries(${test_name} PRIVATE Qt5::Core Qt5::Widgets Qt5::Gui)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
