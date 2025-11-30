cmake_minimum_required(VERSION 3.10)

project(Engine)

set(PROJECT_SOURCE_FILES
    source/Engine.h
    source/Engine.cpp
    source/Application.h
    source/Application.cpp
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
)

include_directories(source)
add_library(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

# 添加GLFW库
set(GLFW_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/GLFW/include")
set(GLFW_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/GLFW/lib")

# 添加glm库
set(GLM_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/GLM")

link_directories(${GLFW_LIB_DIR})# 链接的路径
# set(GLFW_LIB "glfw3.lib")
set(GLFW_LIB_FULL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/GLFW/lib/glfw3.lib")


target_include_directories(${PROJECT_NAME} 
    PUBLIC "${GLFW_INCLUDE_DIR}"
)
target_link_libraries(${PROJECT_NAME} 
    PRIVATE ${GLFW_LIB_FULL_PATH}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC "${GLM_INCLUDE_DIR}"
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

