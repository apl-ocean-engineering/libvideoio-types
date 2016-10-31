# Set source files
file(GLOB VIDEOIO_SOURCE_FILES *.cpp
        util/*.cpp
        util/Undistorter/*.cpp )

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# build shared library.
add_library(libvideoio SHARED ${VIDEOIO_SOURCE_FILES})
target_link_libraries(libvideoio
  ${LIBLOGGER_LIBS}
  ${Boost_LIBRARIES}
  ${OpenCV_LIBS}
  ${G3LOG_LIB}
)
