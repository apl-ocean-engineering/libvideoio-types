
#include <iostream>

#include <gtest/gtest.h>

#include "test_files.h"
#include "libvideoio/Undistorter.h"

using namespace libvideoio;
using namespace std;

namespace {

TEST( UndistorterFactory, LoadCameraCalibration ) {

  std::shared_ptr<Undistorter> undistorter( UndistorterFactory::getUndistorterForFile( CAMERA_CALIBRATION_CFG ) );

  ASSERT_TRUE( (bool)undistorter );


  cout << "Original K:" << endl << undistorter->getOriginalK() << endl;

  cout << "Processed K:" << endl << undistorter->getK() << endl;
}

}
