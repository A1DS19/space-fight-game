cmake_minimum_required(VERSION 3.29.3)
project(LightYears
    VERSION 1.0.0
    DESCRIPTION "A game about space battles"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIGHT_YEARS_GAME_NAME_TARGET LightYearsGame)

add_subdirectory(LightYears)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
    GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(SFML)

target_link_libraries(${LIGHT_YEARS_GAME_NAME_TARGET} PUBLIC sfml-graphics sfml-window sfml-system sfml-audio)
