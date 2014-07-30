cmake_minimum_required(VERSION 2.8.11)

PROJECT(Projeto)

SET(NOME_EXECUTAVEL gl)

SET (Projeto_SOURCES 
	glview.cpp
	lightwindow.cpp
	main.cpp
	mainwindow.cpp 
	materialwindow.cpp
	transformationswindow.cpp
)
SET(Projeto_HEADERS
	defines.h
	glview.h
	lightwindow.h
	mainwindow.h
	materialwindow.h
	transformationswindow.h
)
SET(Projeto_FORMS
	lightwindow.ui
	mainwindow.ui
	materialwindow.ui
	transformationswindow.ui
)

set( CMAKE_CXX_FLAGS "-wformat" )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
add_definitions(-DGLEW_STATIC)
include_directories(${Qt5Widgets_INCLUDES})
add_definitions(${Qt5Widgets_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
qt5_wrap_ui(UI_HEADERS ${Projeto_FORMS})
ADD_EXECUTABLE(${NOME_EXECUTAVEL} ${Projeto_SOURCES} ${UI_HEADERS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${NOME_EXECUTAVEL} ${Qt5Widgets_LIBRARIES} ${Qt5OpenGL_LIBRARIES} ${OPENGL_LIBRARIES})

