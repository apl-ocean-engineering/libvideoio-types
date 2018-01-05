/**
* This file was once part of LSD-SLAM.
*
* Copyright 2013 Jakob Engel <engelj at in dot tum dot de> (Technical University of Munich)
* For more information see <http://vision.in.tum.de/lsdslam>
*
* LSD-SLAM is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* LSD-SLAM is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with LSD-SLAM. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <opencv2/core/core.hpp>

#include "libvideoio/Camera.h"
#include "libvideoio/ImageSize.h"

#include "libvideoio/Undistorter.h"


namespace libvideoio {

// Parses the XML camera parameters file exported by Photoscan.
// Here's a sample:
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
//
// class PhotoscanXMLUndistorterFactory {
// public:
// 	static
// };


class UndistorterPhotoscanXML : public Undistorter
{
public:

	UndistorterPhotoscanXML(const std::string &configFileName);
	~UndistorterPhotoscanXML();

	// Remove the copy operators
	UndistorterPhotoscanXML(const UndistorterPhotoscanXML&) = delete;
	UndistorterPhotoscanXML& operator=(const UndistorterPhotoscanXML&) = delete;

	/**
	 * Undistorts the given image and returns the result image.
	 */
	void undistort(const cv::Mat &image, cv::OutputArray result) const;

	/**
	 * Returns the intrinsic parameter matrix of the undistorted images.
	 */
	const cv::Mat getK() const { return _K; }

	virtual const Camera getCamera() const  { return Camera(getK()); }

	/**
	 * Returns the intrinsic parameter matrix of the original images,
	 */
	const cv::Mat getOriginalK() const { return _originalK; }

	/**
	 * Returns the width of the undistorted images in pixels.
	 */
	int getOutputWidth() const  { return _width; }

	/**
	 * Returns the height of the undistorted images in pixels.
	 */
	int getOutputHeight() const { return _height; }


	/**
	 * Returns the width of the input images in pixels.
	 */
	int getInputWidth() const   { return _width; }

	/**
	 * Returns the height of the input images in pixels.
	 */
	int getInputHeight() const  { return _height; }

	/**
	 * Returns if the undistorter was initialized successfully.
	 */
	bool isValid() const   { return _valid; }

private:

	cv::Mat _K, _originalK;
	cv::Mat _distCoeffs;

	int _width, _height;

	// These are standard OpenCV tangential model distortions
	//float _b[2]

	// float inputCalibration[10];
	// float outputCalibration;
	// int out_width, out_height;
	// int in_width, in_height;

	cv::Mat _map1, _map2;

	/// Is true if the undistorter object is valid (has been initialized with
	/// a valid configuration)
	bool _valid;
};

}
