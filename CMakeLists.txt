SET (CMAKE_CXX_COMPILER             "clang")
SET (CMAKE_CXX_FLAGS                "-std=c++11 -g -O0 ")
SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
set(SFML_ROOT "libs/sfml/")
set(GLEW_ROOT_DIR "libs/glew-1.9.0/")

cmake_minimum_required (VERSION 2.6)
project(terrain)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/libs/sfml/cmake/Modules")

ADD_DEFINITIONS( -DSFML_STATIC -DGLEW_STATIC )
SET( SFML_STATIC_LIBRARIES TRUE )
add_subdirectory("libs/sfml")
file(GLOB_RECURSE SOURCES src false src/*.cpp)
find_package(SFML 2 COMPONENTS REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)


ADD_DEFINITIONS(-DGLEW_STATIC )
include_directories( ${GLEW_INCLUDE_PATH}   "${PROJECT_SOURCE_DIR}/libs/sfml/src" "${SFML_INCLUDE_DIR}" )
ADD_DEFINITIONS( -DSFML_STATIC -DGLEW_STATIC )
#set(CMAKE_INSTALL_PREFIX .)

add_executable(terrain ${SOURCES} )

if(WIN32)
 SET_TARGET_PROPERTIES(terrain PROPERTIES COMPILE_FLAGS "/Od /ZI")
 SET_TARGET_PROPERTIES(terrain PROPERTIES LINK_FLAGS "/DEBUG /SUBSYSTEM:CONSOLE /SAFESEH:NO") 
endif(WIN32)


target_link_libraries(${SFML_LIBRARIES} ${SFML_LIBRARY} terrain sfml-system sfml-window sfml-graphics ${OPENGL_glu_LIBRARY} ${GLEW_LIBRARY})

install( TARGETS terrain DESTINATION bin )

