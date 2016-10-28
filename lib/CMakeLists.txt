# Set source files
file(GLOB VIDEOIO_SOURCE_FILES *.cpp
        util/*.cpp
        util/Undistorter/*.cpp )

if( DEFINED USE_ZED )
  file(GLOB_RESURCE ZED_SOURCES util/Zed/*.cpp)
  list(APPEND VIDEOIO_SOURCE_FILES ${ZED_SOURCES} )
endif()


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# build shared library.
add_library(libvideoio SHARED ${VIDEOIO_SOURCE_FILES})
target_link_libraries(libvideoio
  ${LIBLOGGER_LIBS}
  ${Boost_LIBRARIES}
  ${OpenCV_LIBS}
)
