include_directories( ${CMAKE_SOURCE_DIR}/lib )

file( GLOB UNIT_TEST_SRCS *_test.cpp )

gtest_begin(videoio)
    fips_files(
            ${UNIT_TEST_SRCS}
    )
    fips_deps(videoio)
gtest_end()

# Don't use ctest, instead just execture the Google test binaries
# add_custom_target( unit_test
#                     COMMAND ./videoio_test
#                     WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/bin
#                     DEPENDS videoio_test )
