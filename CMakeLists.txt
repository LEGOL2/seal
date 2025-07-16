cmake_minimum_required(VERSION 4.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(seal LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG "3.0.1"
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_library(${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME} PROPERTY COMPILE_WARNING_AS_ERROR ON)
# target_sources(${PROJECT_NAME} PRIVATE src/seal.cpp)
add_subdirectory(src)
target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(DIRECTORY include/seal DESTINATION include)

add_executable(app main.cpp)
target_link_libraries(app PRIVATE ${PROJECT_NAME})
