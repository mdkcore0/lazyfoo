set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LUtil.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LTexture.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/LOpenGL.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LUtil.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LTexture.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LFRect.h
)

set(EXECUTABLE_NAME ${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} ${SOURCES})


include(FindPkgConfig)

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    include_directories(${OpenGL_INCLUDE_DIRS})
    link_directories(${OpenGL_LIBRARIES_DIRS})
    add_definitions(${OpenGL_DEFINITIONS})
else()
    message(ERROR " OpenGL not found!")
endif()

if(NOT OPENGL_GLU_FOUND)
    message(ERROR " GLU not found!")
endif()


find_package(GLUT REQUIRED)
if(GLUT_FOUND)
    include_directories(${GLUT_INCLUDE_DIRS})
    link_directories(${GLUT_LIBRARIES_DIRS})
    add_definitions(${GLUT_DEFINITIONS})
else()
    message(ERROR " GLUT not found!")
endif()

include(FindPkgConfig)
pkg_search_module(freeglut REQUIRED freeglut)
if(freeglut_FOUND)
    include_directories(${freeglut_STATIC_INCLUDE_DIRS})
    link_directories(${freeglut_STATIC_LIBRARY_DIRS})
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${freeglut_STATIC_CFLAGS_OTHER}")
    add_definitions(${freeglut_STATIC_CFLAGS_OTHER})
endif()


find_package(DevIL REQUIRED)
if(IL_FOUND)
    include_directories(${IL_INCLUDE_DIRS})
else()
    message(ERROR " IL not found!")
endif()


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../images DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../)


target_link_libraries(${EXECUTABLE_NAME}
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
    ${IL_LIBRARIES}
    ${ILU_LIBRARIES}
)
