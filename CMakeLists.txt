cmake_minimum_required(VERSION 2.8.7)
project(libvideo_tools)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(Boost COMPONENTS filesystem system REQUIRED)
find_package(Eigen3 REQUIRED )

## Default OpenCV version
set( OPENCV_VERSION 2.4 )
list(APPEND OPENCV_COMPONENTS core highgui imgproc video calib3d)

EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
message( STATUS "Architecture: ${ARCHITECTURE}" )
if( ${ARCHITECTURE} STREQUAL "aarch64" )

	# This is needed to work around a problem in Jetpack 2.3 / Cuda 8.0
	SET( CUDA_USE_STATIC_CUDA_RUNTIME OFF )

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


# if(APPLE)
# 	set( CMAKE_MACOSX_RPATH OFF )
# endif()
#
#
# include( ${PROJECT_SOURCE_DIR}/cmake/BuildLibLogger.cmake )
# message( ${LIBLOGGER_INCLUDE_DIRS})

## Set global include paths
set( VIDEOIO_INCLUDE_DIRS
	${CMAKE_SOURCE_DIR}/include/libvideoio
	${CONAN_INCLUDE_DIR}
  ${OpenCV_INCLUDE_DIRS}
	${EIGEN3_INCLUDE_DIR} )

include_directories( ${VIDEOIO_INCLUDE_DIRS} )

add_subdirectory("lib/")
add_subdirectory("tools/")

option( BUILD_UNIT_TESTS "Build unit tests" OFF )
if( BUILD_UNIT_TESTS )
  ## Build a local copy of gtest (as per the GTest FAQ)
  # include( ${CMAKE_SOURCE_DIR}/cmake/BuildGTestLibraries.cmake )

  add_subdirectory( test/unit/ )

endif()


add_custom_target( deps DEPENDS ${EXTERNAL_PROJECTS} )
