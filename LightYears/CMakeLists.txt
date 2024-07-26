add_executable(${LIGHT_YEARS_GAME_NAME_TARGET}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Application.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Application.cpp
)

target_include_directories(${LIGHT_YEARS_GAME_NAME_TARGET}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)