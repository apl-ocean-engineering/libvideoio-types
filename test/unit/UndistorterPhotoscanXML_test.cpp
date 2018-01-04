
#include <iostream>

#include <gtest/gtest.h>

#include "test_files.h"

#include "libvideoio/Undistorter/PhotoscanXML.h"

using namespace libvideoio;

using namespace std;

TEST(UndistorterPhotoscanXML, Load_d2_camera) {

  UndistorterPhotoscanXML undistorter( D2_CAMERA_XML );

  cout << "Original K:" << endl << undistorter.getOriginalK() << endl;

  cout << "Processed K:" << endl << undistorter.getK() << endl;


}
