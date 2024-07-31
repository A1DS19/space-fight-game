add_library(${LIGHT_YEARS_ENGINE_TARGET_NAME} STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Application.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Application.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/EntryPoint.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/EntryPoint.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Core.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Core.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/World.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/World.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Actor.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Actor.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Object.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Object.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/AssetManager.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/AssetManager.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/MathUtils.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/MathUtils.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/PhysicsSystem.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/PhysicsSystem.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Delegate.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Delegate.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/include/VFX/Particle.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/VFX/Particle.cpp
)

target_include_directories(${LIGHT_YEARS_ENGINE_TARGET_NAME}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

include(FetchContent)
set(SFML_LIB_NAME SFML)

FetchContent_Declare(
  ${SFML_LIB_NAME}
  GIT_REPOSITORY https://github.com/SFML/SFML
  GIT_TAG 2.5.1
  GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(${SFML_LIB_NAME})

target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-graphics sfml-window sfml-system sfml-audio)

set(BOX2D_LIB_NAME Box2D)

FetchContent_Declare(
  ${BOX2D_LIB_NAME}
  GIT_REPOSITORY https://github.com/erincatto/box2d
  GIT_TAG v2.4.1
  GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(${BOX2D_LIB_NAME})

target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC box2d)