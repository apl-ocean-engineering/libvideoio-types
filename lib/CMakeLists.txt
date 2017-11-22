# Set source files
file(GLOB VIDEOIO_SOURCE_FILES *.cpp **/*.cpp **/**/*.cpp )
include_directories(
  ${CMAKE_SOURCE_DIR}/include
)

# build shared library.
fips_begin_module( videoio )
  fips_files( ${VIDEOIO_SOURCE_FILES})
  fips_libs( ${Boost_LIBRARIES} ${OpenCV_LIBS} ${ZLIB_LIBRARIES} )
  fips_deps( logger g3log )
fips_end_module()
