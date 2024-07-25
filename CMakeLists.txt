cmake_minimum_required(VERSION 3.29.3)
project(LigthYears
    VERSION 1.0.0
    DESCRIPTION "A game about space battles"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIGHT_YEARS_GAME_NAME_TARGET LightYearsGame)

add_subdirectory(LightYears)