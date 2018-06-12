#include <g3log/g3log.hpp>

#include "libvideoio/ImageSource.h"

namespace libvideoio {

  int ImageSource::getImage( int i, cv::Mat &mat ) {
    int ret = getRawImage(i,mat);
    if( _outputType <0 || mat.type() == _outputType ) return ret;


    // Else attempt automatic conversion

    return ret;
  }


}
