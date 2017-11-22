
fips_begin_app( recorder cmdline )
  fips_files( Recorder.cpp )
  fips_libs( videoio ${CMAKE_THREAD_LIBS_INIT} )
  # set_target_properties( recorder PROPERTIES COMPILE_FLAGS "-ggdb")

  include_directories(
    ${VIDEOIO_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
  )
fips_end_app()
