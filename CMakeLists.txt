cmake_minimum_required(VERSION 2.8)

project(MapEditor)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=gnu++11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

file(GLOB_RECURSE SRCS src/*.cpp src/*.h)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${OPENGL_INCLUDES}
	${GLUT_INCLUDES}
	${SDL2_INCLUDES}
	${SDL2_image_INCLUDE_DIR}
)
add_executable(MapEditor main.cpp ${SRCS})
target_link_libraries(MapEditor ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES}
${SDL2_LIBRARIES} ${SDL2_image_LIBRARY})

