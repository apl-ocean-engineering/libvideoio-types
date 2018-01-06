include_directories( ${CMAKE_SOURCE_DIR}/lib )

file( GLOB UNIT_TEST_SRCS *_test.cpp )

# set( TEST_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../data" )
# add_definitions( -DTEST_DATA_DIR=${TEST_DATA_DIR} )

# NO_TEMPLATE means  "I wrote my own main()"

gtest_begin(videoio NO_TEMPLATE)
    fips_files(
      ${UNIT_TEST_SRCS}
      main.cpp
    )
    fips_deps(videoio)

    include_directories( ${TEST_DATA_DIR} )
gtest_end()

# Don't use ctest, instead just execture the Google test binaries
# add_custom_target( unit_test
#                     COMMAND ./videoio_test
#                     WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/bin
#                     DEPENDS videoio_test )
