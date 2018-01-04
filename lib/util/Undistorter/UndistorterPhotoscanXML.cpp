
#include "libvideoio/Undistorter.h"

#include <tinyxml2.h>

#include <sstream>
#include <fstream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

namespace libvideoio
{

  using namespace tinyxml2;

  // Sample input:
  //
  // <?xml version="1.0" encoding="UTF-8"?>
  // <calibration>
  //   <projection>frame</projection>
  //   <width>1920</width>
  //   <height>1080</height>
  //   <f>1430.15016509976</f>
  //   <cx>-24.1342060175983</cx>
  //   <cy>17.5452248329602</cy>
  //   <b2>-4.25145544487403</b2>
  //   <k1>-0.118322055927498</k1>
  //   <k2>0.293632083518507</k2>
  //   <p1>0.000330080086304322</p1>
  //   <p2>0.00182154893322038</p2>
  //   <date>2017-11-14T23:30:12Z</date>
  // </calibration>

UndistorterPhotoscanXML::UndistorterPhotoscanXML(const char* configFileName)
  :   _originalK( cv::Mat(3, 3, CV_64F, cv::Scalar(0)) ),
      _distCoeffs( cv::Mat(1,4, CV_64F, cv::Scalar(0)) ),
      _valid(true)
{

  XMLDocument doc;
  doc.LoadFile( configFileName );

  auto calibrationNode = doc.FirstChildElement( "calibration" );

  // TODO, add error checking
  {
    auto widthNode = calibrationNode->FirstChildElement("width");
    if( widthNode ) {
      _width = atoi( widthNode->GetText() );
    } else {
      _valid = false;
    }
  }

  {
    auto heightNode = calibrationNode->FirstChildElement("height");
    if( heightNode ) {
      _height = atoi( heightNode->GetText() );
    } else {
      _valid = false;
    }
  }

  double f=1.0, cx=0.0, cy=0.0;

  {
    auto focalNode = calibrationNode->FirstChildElement("f");
    if( focalNode ) {
      f = atof( focalNode->GetText() );
    } else {
      _valid = false;
    }
  }

  {
    auto cxNode = calibrationNode->FirstChildElement("cx");
    if( cxNode ) {
      cx = atof( cxNode->GetText() );
    } else {
      _valid = false;
    }
  }

  {
    auto cyNode = calibrationNode->FirstChildElement("cy");
    if( cyNode ) {
      f = atof( cyNode->GetText() );
    } else {
      _valid = false;
    }
  }

	_originalK.at<double>(0, 0) = f;
	_originalK.at<double>(1, 1) = f;
	_originalK.at<double>(2, 2) = 1;
	_originalK.at<double>(0, 2) = cx;
	_originalK.at<double>(1, 2) = cy;


  // This distortion elements are optional (no error if not found)
  {
    auto node = calibrationNode->FirstChildElement("b1");
    if( node ) {
    // What are b1 and b2?
    //  _b[0] = atof( node->GetText() );
    }
  }

  {
    auto node = calibrationNode->FirstChildElement("b2");
    if( node ) {
    //  _b[1] = atof( node->GetText() );
    }
  }

  {
    auto node = calibrationNode->FirstChildElement("k1");
    if( node ) {
      _distCoeffs.at<double>(0,0) = atof( node->GetText() );
    }
  }

  {
    auto node = calibrationNode->FirstChildElement("k2");
    if( node ) {
      _distCoeffs.at<double>(0,1) = atof( node->GetText() );
    }
  }

  {
    auto node = calibrationNode->FirstChildElement("p1");
    if( node ) {
      _distCoeffs.at<double>(0,2) = atof( node->GetText() );
    }
  }

  {
    auto node = calibrationNode->FirstChildElement("p2");
    if( node ) {
      _distCoeffs.at<double>(0,3) = atof( node->GetText() );
    }
  }


	if (_valid) {
		_K = cv::getOptimalNewCameraMatrix(_originalK, _distCoeffs,
                  cv::Size(_width, _height),
                  0, cv::Size(_width, _height), nullptr, false);

		cv::initUndistortRectifyMap(_originalK, _distCoeffs, cv::Mat(), _K,
				                cv::Size(_width, _height), CV_16SC2, _map1, _map2);

    //
		// originalK_.at<double>(0, 0) /= in_width;
		// originalK_.at<double>(0, 2) /= in_width;
		// originalK_.at<double>(1, 1) /= in_height;
		// originalK_.at<double>(1, 2) /= in_height;
	}

	_originalK = _originalK.t();
	_K = _K.t();
}

UndistorterPhotoscanXML::~UndistorterPhotoscanXML()
{
}

void UndistorterPhotoscanXML::undistort(const cv::Mat& image, cv::OutputArray result) const
{
	 cv::remap(image, result, _map1, _map2, cv::INTER_LINEAR);
}


}
