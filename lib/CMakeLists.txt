# Set source files
file(GLOB VIDEOIO_SOURCE_FILES *.cpp )


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# build shared library.
add_library(libvideoio SHARED ${VIDEOIO_SOURCE_FILES})
# target_link_libraries(camhd_motrack
#   ${Boost_LIBRARIES}
# )
