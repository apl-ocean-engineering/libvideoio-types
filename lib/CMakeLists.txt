# Set source files
file(GLOB VIDEOIO_SOURCE_FILES **/*.cpp **/**/*.cpp )
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# build shared library.
add_library( videoio SHARED ${VIDEOIO_SOURCE_FILES})
target_link_libraries( videoio
  ${Boost_LIBRARIES}
  ${OpenCV_LIBS}
  ${CONAN_LIBS}
)
