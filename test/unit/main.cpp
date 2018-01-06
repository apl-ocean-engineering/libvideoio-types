
#include "gtest/gtest.h"

#include "libvideoio/G3LogSinks.h"


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  // Initialize g3log
  auto worker = g3::LogWorker::createLogWorker();
  auto stderrHandle = worker->addSink(std::unique_ptr<ColorStderrSink>( new ColorStderrSink ),
                        &ColorStderrSink::ReceiveLogMessage);
  g3::initializeLogging(worker.get());

  return RUN_ALL_TESTS();
}
