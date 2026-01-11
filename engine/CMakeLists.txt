cmake_minimum_required(VERSION 3.10)


project(Engine)

set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")

include_directories(${PROJECT_BINARY_DIR})
configure_file(
    ${PROJECT_SOURCE_DIR}/config.h.in
    ${PROJECT_BINARY_DIR}/config.h
)

set(PROJECT_SOURCE_FILES
    source/Engine.h
    source/Engine.cpp
    source/Application.h
    source/Application.cpp
    source/gui/Gui.h
    source/gui/Gui.cpp
    source/glad.c
    source/input/inputManager.h
    source/input/inputManager.cpp
    source/graphics/ShaderProgram.h
    source/graphics/ShaderProgram.cpp
    source/graphics/GraphicsAPI.h
    source/graphics/GraphicsAPI.cpp
    source/render/Material.h
    source/render/Material.cpp
    source/render/Mesh.h
    source/render/Mesh.cpp
    source/render/RenderQueue.h
    source/render/RenderQueue.cpp
    source/scene/GameObject.h
    source/scene/GameObject.cpp
    source/scene/scene.h
    source/scene/scene.cpp
    source/scene/Component.h
    source/scene/Component.cpp
    source/scene/components/MeshComponent.h
    source/scene/components/MeshComponent.cpp
    source/scene/components/CameraComponent.h
    source/scene/components/CameraComponent.cpp
    source/scene/components/PlayerControllerComponent.h
    source/scene/components/PlayerControllerComponent.cpp
    source/scene/components/LightComponent.h
    source/scene/components/LightComponent.cpp
    source/scene/components/AnimationComponent.h
    source/scene/components/AnimationComponent.cpp
    source/scene/components/PhysicsComponent.h
    source/scene/components/PhysicsComponent.cpp
    source/io/FileSystem.h
    source/io/FileSystem.cpp
    source/graphics/Texture.h
    source/graphics/Texture.cpp
    source/Common.h
    source/physics/Collider.h
    source/physics/Collider.cpp
    source/physics/PhysicsManager.h
    source/physics/PhysicsManager.cpp
    source/physics/RigidBody.h
    source/physics/RigidBody.cpp
)

include_directories(source)


# 添加ImGui
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui")
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp

    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/backends
)

add_library(${PROJECT_NAME} ${PROJECT_SOURCE_FILES} ${IMGUI_SOURCES})

# 添加GLFW库
set(GLFW_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/GLFW/include")
set(GLFW_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/GLFW/lib")

# 添加glm库
set(GLM_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/GLM")

link_directories(${GLFW_LIB_DIR})# 链接的路径
# set(GLFW_LIB "glfw3.lib")
set(GLFW_LIB_FULL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/GLFW/lib/glfw3.lib")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/stb_image)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/json)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/cgltf)

# Include Bullet as a 子系统
option(BUILD_UNIT_TESTS OFF)
option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_SHARED_LIBS OFF)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/bullet)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/bullet/src)

target_include_directories(${PROJECT_NAME} 
    PUBLIC "${GLFW_INCLUDE_DIR}"
)
target_link_libraries(${PROJECT_NAME} 
    PRIVATE ${GLFW_LIB_FULL_PATH}
    LinearMath
    BulletCollision
    BulletDynamics
)

target_include_directories(${PROJECT_NAME}
    PUBLIC "${GLM_INCLUDE_DIR}"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR}
    ${CMAKE_BINARY_DIR}/assets
)

if(WIN32)
    # Windows下GLFW通常依赖opengl32.lib
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
elseif(UNIX)
    # Linux下可能依赖GL、X11等（如果你的.lib是Linux平台的静态库，需对应调整）
    target_link_libraries(Game PRIVATE GL X11)
elseif(APPLE)
    # macOS下依赖OpenGL框架
    find_library(OPENGL_FRAMEWORK OpenGL)
    target_link_libraries(Game PRIVATE ${OPENGL_FRAMEWORK})
endif()