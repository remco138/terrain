SET (CMAKE_CXX_COMPILER             "clang++")
SET (CMAKE_CXX_FLAGS                "-Wall -std=c++11")
SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
set(SFML_ROOT src/libs/sfml)
cmake_minimum_required (VERSION 2.6)
project(terrain)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/src/libs/sfml/cmake/Modules")


    
#set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2 REQUIRED)
find_package(GLEW REQUIRED)

include_directories( ${GLEW_INCLUDE_DIR}   "${PROJECT_SOURCE_DIR}/src/libs/sfml/src" "${SFML_INCLUDE_DIR}" )

file(GLOB_RECURSE SOURCES src false *.cpp)

set(CMAKE_INSTALL_PREFIX .)

add_executable(terrain ${SOURCES} )
target_link_libraries(terrain ${GLEW_LIBRARY} ${SFML_LIBRARY})
install( TARGETS terrain DESTINATION bin )

