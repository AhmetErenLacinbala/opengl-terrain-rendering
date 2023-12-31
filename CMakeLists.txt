cmake_minimum_required(VERSION 3.22)
project(terrarian-render)

set(CMAKE_CXX_STANDARD 17)

# Paths
set(PROJECT_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)

# Packages
find_package(glfw3 3.2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

# Include Directories
set(GENERAL_INCLUDE "/usr/include")

set(PROJECT_INCLUDE_DIR
    ${PROJECT_DIR}/include
    ${GENERAL_INCLUDE}
    ${GLEW_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIR}
    ${GLUT_INCLUDE_DIRS}
)

# Sources
set(OGL_DEV ${PROJECT_DIR}/include/ogl_dev)  # Path to ogl_dev directory

set(PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/technique.cpp
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/terrain_technique.cpp
    ${PROJECT_SOURCE_DIR}/terrain.cpp
    ${PROJECT_SOURCE_DIR}/triangle_list.cpp
    ${PROJECT_SOURCE_DIR}/vertexArrayObject.cpp
    ${PROJECT_SOURCE_DIR}/shader.cpp
    ${PROJECT_SOURCE_DIR}/mesh.cpp
    ${PROJECT_SOURCE_DIR}/shaderProgram.cpp
    ${PROJECT_SOURCE_DIR}/scene.cpp
    ${PROJECT_SOURCE_DIR}/ResourceManager.cpp
    ${PROJECT_SOURCE_DIR}/cube.cpp
    ${OGL_DEV}/ogldev_basic_glfw_camera.cpp
    ${OGL_DEV}/ogldev_glfw.cpp
    ${OGL_DEV}/ogldev_util.cpp
    ${OGL_DEV}/math_3d.cpp
    # Add any new source files here
)

# Executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

file(COPY ${CMAKE_SOURCE_DIR}/src/terrain.vs
          ${CMAKE_SOURCE_DIR}/src/terrain.fs
          ${CMAKE_SOURCE_DIR}/src/heightmap.save
     DESTINATION ${CMAKE_BINARY_DIR})

# Include directories for the target
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE_DIR})

# Libraries
target_link_libraries(${PROJECT_NAME} 
    glfw 
    GLEW::GLEW
    ${ASSIMP_LIBRARY}
    ${GLUT_LIBRARIES}
    ${OPENGL_LIBRARIES}
)


