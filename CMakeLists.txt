cmake_minimum_required(VERSION 2.8.7)
project(libvideo_tools)
include(ExternalProject)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

## Configure other external packages
find_package(Boost COMPONENTS filesystem system REQUIRED)
find_package(TCLAP REQUIRED )
find_package(ZLIB REQUIRED )
find_package(Eigen3 REQUIRED )

set( EXTERNAL_PROJECTS  )
include( ${PROJECT_SOURCE_DIR}/cmake/BuildG3Log.cmake )

## Default OpenCV version
set( OPENCV_VERSION 2.4 )
list(APPEND OPENCV_COMPONENTS core highgui imgproc video calib3d)

EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
message( STATUS "Architecture: ${ARCHITECTURE}" )
if( ${ARCHITECTURE} STREQUAL "aarch64" )

	## For compilation on Jetson TX1
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv8-a") # -DENABLE_NEON" )

elseif( ${ARCHITECTURE} STREQUAL "x86_64" )

  # -DENABLE_SSE enables Jakob's original SSE optimizations in his code,
	# it has nothing to do with compiler behavior
  set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -msse4.1 -msse3 -msse2 -msse -march=native -DENABLE_SSE" )
endif()

## C++ flags applied to all builds
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

## Configure OpenCV ##

find_package(OpenCV ${OPENCV_VERSION} COMPONENTS ${OPENCV_COMPONENTS} REQUIRED)


if(APPLE)
	set( CMAKE_MACOSX_RPATH OFF )
endif()


include( ${PROJECT_SOURCE_DIR}/cmake/BuildLibLogger.cmake )
message( ${LIBLOGGER_INCLUDE_DIRS})

## Set global include paths
set( VIDEOIO_INCLUDE_DIRS
	${G3LOG_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/include/libvideo_tools
  ${OpenCV_INCLUDE_DIRS}
	${EIGEN3_INCLUDE_DIR}
 	${LIBLOGGER_INCLUDE_DIRS} )

message( ${VIDEOIO_INCLUDE_DIRS} )

include_directories( ${VIDEOIO_INCLUDE_DIRS} )

add_subdirectory("lib/")
add_subdirectory("tools/")

option( BUILD_UNIT_TESTS "Build unit tests" ON )
if( BUILD_UNIT_TESTS )
  ## Build a local copy of gtest (as per the GTest FAQ)
  include( ${CMAKE_SOURCE_DIR}/cmake/BuildGTestLibraries.cmake )

  add_subdirectory( test/unit/ )

endif()


add_custom_target( deps DEPENDS ${EXTERNAL_PROJECTS} )
