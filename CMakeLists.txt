cmake_minimum_required(VERSION 3.5)
if( NOT FIPS_IMPORT )
	get_filename_component(FIPS_ROOT_DIR "../fips" ABSOLUTE)
	include("${FIPS_ROOT_DIR}/cmake/fips.cmake")

	fips_setup(PROJECT libvideoio_types)
endif()

find_package( Eigen3 REQUIRED )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

## Set global include paths
fips_include_directories( include
					${EIGEN3_INCLUDE_DIR}
  				${OpenCV_INCLUDE_DIRS} )


if( NOT FIPS_IMPORT )
	if( FIPS_UNITTESTS )
	  fips_add_subdirectory( test/unit/ )
	endif()

	fips_finish()
endif()
