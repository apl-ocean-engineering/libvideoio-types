
#include "gtest/gtest.h"

#include <libg3logger/g3logger.h>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  libg3log::G3Logger logWorker( argv[0] );

  return RUN_ALL_TESTS();
}
