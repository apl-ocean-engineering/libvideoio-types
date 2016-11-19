#pragma once

#include <string>
#include <map>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

#include "logger/LogFields.h"

namespace libvideoio {


class VideoOutput {
public:
	VideoOutput( const std::string &filename, float fps );
	bool write( const cv::Mat &img );

protected:

	fs::path _file;
	bool _active;

	std::unique_ptr< cv::VideoWriter > _writer;
	float _fps;

};


}
