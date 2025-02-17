cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(projeto_cg)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#Flags do makefile
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fno-stack-protector -g -O2")

#Includes
include_directories(include)

#Preferência para GLVND
set(OpenGL_GL_PREFERENCE "GLVND")

#OPENGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

#Bibliotecas necessárias
add_library(Triangles OBJECT src/figuras/Triangles.cpp)
add_library(Ficheiro OBJECT src/ficheiro3d/Ficheiro.cpp)
add_library(TinyXML OBJECT src/tinyxml/tinyxml.cpp src/tinyxml/tinyxmlparser.cpp src/tinyxml/tinyxmlerror.cpp src/tinyxml/tinystr.cpp)
add_library(World OBJECT src/engine/World.cpp)
add_library(processaXML OBJECT src/engine/processaXML.cpp)

#Generator
add_executable(generator src/gerador/gerador.cpp 
                         $<TARGET_OBJECTS:Triangles> 
                         $<TARGET_OBJECTS:Ficheiro>)

#Engine
add_executable(engine src/engine/engine.cpp 
                      $<TARGET_OBJECTS:Triangles> 
                      $<TARGET_OBJECTS:Ficheiro>
					  $<TARGET_OBJECTS:TinyXML>
					  $<TARGET_OBJECTS:World>
					  $<TARGET_OBJECTS:processaXML>)

if(NOT OPENGL_FOUND)
    message(ERROR "OpenGL not found!")
endif(NOT OPENGL_FOUND)

if  (WIN32)

	message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
	set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")
	
	if (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
		message(ERROR ": GLUT not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")	
	
	
	include_directories(${TOOLKITS_FOLDER}/glut )
	target_link_libraries(engine ${OPENGL_LIBRARIES} 
										  ${TOOLKITS_FOLDER}/glut/glut32.lib)
	target_link_libraries(generator)

	if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" )
		file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
	endif(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" )	
	
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
	
else (WIN32) #Linux and Mac

	set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} Wno-deprecated")
	find_package(GLUT REQUIRED)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})
	
	target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
	target_link_libraries(generator)
    
    if(NOT GLUT_FOUND)
	   message(ERROR ": GLUT not found!")
	endif(NOT GLUT_FOUND)
	
endif(WIN32)
# --- Verifica se está no Mac ---
if(APPLE)
    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)

    include_directories(${OpenGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
    target_link_libraries(engine ${OpenGL_LIBRARIES} ${GLUT_LIBRARIES})
    target_link_libraries(generator ${OpenGL_LIBRARIES} ${GLUT_LIBRARIES})

    if(NOT GLUT_FOUND)
        message(ERROR ": GLUT não encontrado!")
    endif()
endif()