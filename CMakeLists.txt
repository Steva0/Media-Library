cmake_minimum_required(VERSION 3.16)

project(MediaLibraryBuild VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC ON)



set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)



# Raccoglie tutti i file .cpp e .h nella cartella src/

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/**/*.cpp src/**/*.h)



# Crea l'eseguibile principale

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE src)



# Imposta la cartella output dell'eseguibile (per renderlo visibile facilmente)

set_target_properties(${PROJECT_NAME} PROPERTIES

    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}

)



# Abilita il supporto ai test

enable_testing()



# Aggiungi i test eseguibili (puoi creare src/test1.cpp, src/test2.cpp, ecc.)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS src/test*.cpp)



foreach(test_src ${TEST_SOURCES})

    get_filename_component(test_name ${test_src} NAME_WE)

    add_executable(${test_name} ${test_src})

    target_include_directories(${test_name} PRIVATE src)

    add_test(NAME ${test_name} COMMAND ${test_name})

endforeach()
