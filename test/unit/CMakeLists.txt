include_directories( ${GTEST_INCLUDE_DIRS}
                     ${CMAKE_SOURCE_DIR}/lib )

file( GLOB UNIT_TEST_SRCS *_test.cpp )

add_executable( videoio_test
              ${UNIT_TEST_SRCS} )

link_directories( ${GTEST_LIBRARY_DIR} )

target_link_libraries( videoio_test
          ${CONAN_LIBS}
          videoio )

# Don't use ctest, instead just execture the Google test binaries
add_custom_target( unit_test
                    COMMAND ./videoio_test
                    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/bin
                    DEPENDS videoio_test )
