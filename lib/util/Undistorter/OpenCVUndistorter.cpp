
#include "libvideoio/Undistorter.h"

#include <tinyxml2.h>

#include <sstream>
#include <fstream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

namespace libvideoio
{

  OpenCVUndistorter::OpenCVUndistorter( const cv::Mat &k,
											const cv::Mat &distCoeff,
											const ImageSize &origSize )
    : _originalK( k ),
      _distCoeffs( distCoeff ),
      _inputSize( origSize ),
      _outputSize( origSize ),
      _valid( true )
{

  _K = cv::getOptimalNewCameraMatrix(_originalK, _distCoeffs,
                _inputSize(),
                1,
                _outputSize(), nullptr, false);

  cv::initUndistortRectifyMap(_originalK, _distCoeffs, cv::Mat(), _K,
                      _outputSize(), CV_16SC2, _map1, _map2);

  //
  // originalK_.at<double>(0, 0) /= in_width;
  // originalK_.at<double>(0, 2) /= in_width;
  // originalK_.at<double>(1, 1) /= in_height;
  // originalK_.at<double>(1, 2) /= in_height;

}

OpenCVUndistorter::~OpenCVUndistorter()
{}

void OpenCVUndistorter::undistort(const cv::Mat& image, cv::OutputArray result) const
{
	 cv::remap(image, result, _map1, _map2, cv::INTER_LINEAR);
}


}
