# Set source files
file(GLOB VIDEOIO_SOURCE_FILES *.cpp **/*.cpp **/**/*.cpp )
include_directories(
  ${CMAKE_SOURCE_DIR}/include
)

# build shared library.
add_library( videoio SHARED ${VIDEOIO_SOURCE_FILES})
target_link_libraries( videoio
  ${Boost_LIBRARIES}
  ${OpenCV_LIBS}
  ${CONAN_LIBS}
)
