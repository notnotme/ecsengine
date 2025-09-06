cmake_minimum_required(VERSION 3.28)

project(ecsengine VERSION 0.5.0 DESCRIPTION "Simple game engine using EntityX")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(GNUInstallDirs)

# Source files
# ========================================
add_library(ecsengine STATIC
    src/Audio/AudioPlayer.cpp
    src/Asset/Font/FontAsset.cpp
    src/Asset/Font/FontLoadable.cpp
    src/Asset/SpriteSheet/SpriteSheetAsset.cpp
    src/Asset/SpriteSheet/SpriteSheetLoadable.cpp
    src/Asset/Texture/TextureAsset.cpp
    src/Asset/Texture/TextureLoadable.cpp
    src/Asset/AssetManager.cpp
    src/Behavior/Node/BindTexture.cpp
    src/Behavior/Node/ClearBuffer.cpp
    src/Behavior/Node/CreateQuad.cpp
    src/Behavior/Node/CreateSprite.cpp
    src/Behavior/Node/CreateText.cpp
    src/Behavior/Node/Delay.cpp
    src/Behavior/Node/FadeIn.cpp
    src/Behavior/Node/FadeOut.cpp
    src/Behavior/Node/GameEnd.cpp
    src/Behavior/Node/PredefinedResult.cpp
    src/Behavior/Node/TransitionTo.cpp
    src/Behavior/Node/SetFriction.cpp
    src/Behavior/Node/SetTextureUnit.cpp
    src/Behavior/Node/SetTint.cpp
    src/Behavior/Node/SetVelocity.cpp
    src/Behavior/Node/StartPlayer.cpp
    src/Behavior/Node/WaitPlayer.cpp
    src/Behavior/ParallelNode.cpp
    src/Behavior/SequenceNode.cpp
    src/Game/Scene/Scene.cpp
    src/Game/Scene/TransitionScene.cpp
    src/Game/Transition/FadeOutFadeIn.cpp
    src/Game/Game.cpp
    src/Renderer/QuadProgram.cpp
    src/Renderer/RendererUtil.cpp
    src/Renderer/Shader.cpp
    src/Renderer/SpriteProgram.cpp
    src/System/BehaviorSystem.cpp
    src/System/MovementSystem.cpp
    src/System/SpriteSystem.cpp
    src/GameWindow.cpp
)

# Public header
# ========================================
set_target_properties(ecsengine PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER include/ecsengine.h
)

# PkgConfig support
# ========================================
configure_file(ecsengine.pc.in ecsengine.pc @ONLY)
target_include_directories(ecsengine PRIVATE include)

install(TARGETS ecsengine
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/ecsengine.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

# Dependencies
# ========================================
find_package(PkgConfig REQUIRED)

# SDL2
# libsdl2-dev
find_package(SDL2 REQUIRED)
target_link_libraries(ecsengine
        PUBLIC
        SDL2::SDL2main
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>, SDL2::SDL2, SDL2::SDL2-static>
)

# SDL2_image
# libsdl2-image-dev
find_package(SDL2_image REQUIRED)
target_link_libraries(ecsengine
        PUBLIC
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>, SDL2_image::SDL2_image, SDL2_image::SDL2_image-static>
)

# SDL2_ttf
# libsdl2-ttf-dev
find_package(SDL2_ttf REQUIRED)
target_link_libraries(ecsengine
        PUBLIC
        $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>, SDL2_ttf::SDL2_ttf, SDL2_ttf::SDL2_ttf-static>
)

# OpenGL
# libsdl2-dev
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
target_link_libraries(ecsengine
        PUBLIC
        OpenGL::GL
)

# TBB
# libtbb-dev
find_package(TBB CONFIG REQUIRED)
target_link_libraries(ecsengine
        PUBLIC
        TBB::tbb
)

# glad
# vcpkg install glad
find_package(glad CONFIG REQUIRED)
target_link_libraries(ecsengine
        PUBLIC
        glad::glad
)

# EntityX
# vcpkg install entityx
pkg_check_modules(ENTITYX REQUIRED entityx)
target_include_directories(ecsengine
        PUBLIC
        ${ENTITYX_INCLUDE_DIRS})
target_link_libraries(ecsengine
        PUBLIC
        ${ENTITYX_LINK_LIBRARIES}
)


# libopenmpt
# libopenmpt-dev
find_package(libopenmpt CONFIG REQUIRED)
target_link_libraries(ecsengine
        PUBLIC
        libopenmpt::libopenmpt)

# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()