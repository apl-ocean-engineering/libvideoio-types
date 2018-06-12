
fips_begin_app( recorder cmdline )
  fips_files( Recorder.cpp )
  fips_deps( videoio g3logger )
fips_end_app()


fips_begin_app( undistort cmdline )
  fips_files( Undistort.cpp )
  fips_deps( videoio g3logger )
fips_end_app()
