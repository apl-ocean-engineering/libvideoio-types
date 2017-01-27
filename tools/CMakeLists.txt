
include_directories(
  ${VIDEOIO_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# set(CMAKE_CXX_FLAGS
#    "${CMAKE_CXX_FLAGS} -ggdb"
# )

add_executable( Recorder Recorder.cpp)
target_link_libraries( Recorder videoio ${CMAKE_THREAD_LIBS_INIT} )
set_target_properties( Recorder PROPERTIES COMPILE_FLAGS "-ggdb")


# # build image node
# add_executable(LSD LSD.cpp
#   LSD/GuiThread.cpp
#   LSD/InputThread.cpp)
# target_link_libraries( LSD lsdslam )
