#include "VideoOutput.h"

namespace libvideoio {

	VideoOutput::VideoOutput( const std::string &filename, float fps )
		: _file( filename ),
			_active( false ),
			_writer(),
			_fps( fps )
	{
		if( !_file.empty() ) {
			LOG(INFO) << "Recording to video file " << _file.string();
			_active = true;
		}
	}

	// bool write( logger::FieldHandle_t handle, const Mat &img, int frame = -1 )
	bool VideoOutput::write( const cv::Mat &img )
	{
		if( !_active ) return true;

		// Eager-create the writer
		if( !_writer ) {
			LOG(INFO) << "Opening video at " << _fps << " fps with size " << img.cols << " x " << img.rows;
			_writer.reset( new cv::VideoWriter(_file.string(), CV_FOURCC('A','V','C','1'), _fps, cv::Size(img.cols, img.rows)));

			if( ! _writer->isOpened() )
				LOG(FATAL) << "Unable to open video writer.";
		}

	LOG(INFO) << "writing...";
	_writer->write( img );

		return true;
	}


}
