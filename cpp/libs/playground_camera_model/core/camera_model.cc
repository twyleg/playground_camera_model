// Copyright (C) 2024 twyleg
#include "camera_model.h"

namespace playground_camera_model {


CameraModel::CameraModel(double sensorWidth, double sensorHeight, double focalLength, uint32_t resolutionX, uint32_t resolutionY, uint32_t u0, uint32_t v0)
	: mSensorWidth(sensorWidth),
	  mSensorHeight(sensorHeight),
	  mFocalLength(focalLength),
	  mResolutionX(resolutionX),
	  mResolutionY(resolutionY),
	  mU0(u0),
	  mV0(v0)
{

	// Create camera image resolutionX * resolutionY with 3 Channels for RGB
	mCameraImage.create(resolutionY,resolutionX,CV_8UC3);
	mCameraImage = cv::Scalar(255,255,255);

	// Create camera transformation matrix I_T_C
	const double rhoWidth = sensorWidth / resolutionX;
	const double rhoHeight = sensorHeight / resolutionY;

	double matrixK_data[3*3] = {(1/rhoWidth), 	0, 				static_cast<double>(u0),
								0,				(1/rhoHeight), 	static_cast<double>(v0),
								0,				0,				1};

	double matrixC_data[3*4] = {focalLength,		0,				0,		0,
								0,				focalLength,	0,		0,
								0,				0,				1,		0};

	const cv::Mat matrixK(3, 3, CV_64F, matrixK_data);
	const cv::Mat matrixC(3, 4, CV_64F, matrixC_data);

	I_T_C.create(3, 4, CV_64F);

	I_T_C = matrixK * matrixC;
}


void CameraModel::drawCameraImagePoint(const HTM::Point3d& C_point){

	const cv::Mat I_point = I_T_C * C_point;

	const int32_t u = I_point.at<double>(0) / I_point.at<double>(2);
	const int32_t v = I_point.at<double>(1) / I_point.at<double>(2);

	const cv::Point point(u,v);

	cv::circle(mCameraImage, point, 5, cv::Scalar(255,0,0), 2);

}

void CameraModel::drawCameraImageLine(const HTM::Point3d& C_point0, const HTM::Point3d& C_point1){

	const cv::Mat I_point0 = I_T_C * C_point0;
	const cv::Mat I_point1 = I_T_C * C_point1;

	const int32_t u0 = I_point0.at<double>(0) / I_point0.at<double>(2);
	const int32_t v0 = I_point0.at<double>(1) / I_point0.at<double>(2);

	const int32_t u1 = I_point1.at<double>(0) / I_point1.at<double>(2);
	const int32_t v1 = I_point1.at<double>(1) / I_point1.at<double>(2);

	const cv::Point point0(u0,v0);
	const cv::Point point1(u1,v1);

	cv::line(mCameraImage, point0, point1, cv::Scalar(255,0,0), 1);
}

void CameraModel::resetCameraImage(){

	mCameraImage = cv::Scalar(255,255,255);

}

cv::Mat& CameraModel::getCameraImage() {
	return mCameraImage;
}

}
