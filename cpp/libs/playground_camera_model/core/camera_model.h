// Copyright (C) 2024 twyleg
#pragma once
#include "homogeneous_transformation_matrix.h"

#include <cstdint>

#include <opencv2/opencv.hpp>

namespace playground_camera_model {

namespace HTM = playground_camera_model::homogeneous_transformation_matrix;

class CameraModel {

private:

	double mSensorWidth;
	double mSensorHeight;
	double mFocalLength;
	uint32_t mResolutionX;
	uint32_t mResolutionY;
	uint32_t mU0;
	uint32_t mV0;

	cv::Mat mCameraImage;

public:

	cv::Mat I_T_C;


	CameraModel(double sensorWidth,
				double sensorHeight,
				double focalLength,
				uint32_t resolutionX,
				uint32_t resolutionY,
				uint32_t u0,
				uint32_t v0);

	void drawCameraImagePoint(const HTM::Point3d&);
	void drawCameraImageLine(const HTM::Point3d&, const HTM::Point3d&);

	void resetCameraImage();
	cv::Mat& getCameraImage();

};

}
