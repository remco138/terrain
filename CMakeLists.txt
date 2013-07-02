SET (CMAKE_CXX_COMPILER             "clang")
SET (CMAKE_CXX_FLAGS                "-std=c++11 -g -O0 ")
SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
set(SFML_ROOT "libs/sfml")

cmake_minimum_required (VERSION 2.6)
project(terrain)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/libs/sfml/cmake/Modules")


add_subdirectory("libs/sfml")
file(GLOB_RECURSE SOURCES src false src/*.cpp)
find_package(SFML 2 COMPONENTS REQUIRED)

include_directories( ${GLEW_INCLUDE_DIR}   "${PROJECT_SOURCE_DIR}/libs/sfml/src" "${SFML_INCLUDE_DIR}" )

#set(CMAKE_INSTALL_PREFIX .)

add_executable(terrain ${SOURCES} )


#target_link_libraries( ${LIBRARY_NAME} terrain)

target_link_libraries(${SFML_LIBRARIES} ${SFML_LIBRARY} terrain GL stdc++ sfml-system sfml-window sfml-graphics -lm GLU ${GLEW_LIBRARY})
install( TARGETS terrain  DESTINATION bin )

