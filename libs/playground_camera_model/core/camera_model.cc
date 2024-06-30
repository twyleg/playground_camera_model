// Copyright (C) 2024 twyleg
#include "camera_model.h"


CameraModel::CameraModel(double sensorWidth, double sensorHeight, double focalLength, uint32_t resolutionX, uint32_t resolutionY, uint32_t u0, uint32_t v0){

	this->sensorWidth = sensorWidth;
	this->sensorHeight = sensorHeight;
	this->focalLength = focalLength;
	this->resolutionX = resolutionX;
	this->resolutionY = resolutionY;
	this->u0 = u0;
	this->v0 = v0;

	/*
	 * Create camera image resolutionX * resolutionY with 3 Channels for RGB
	 */
	cameraImage.create(resolutionY,resolutionX,CV_8UC3);
	cameraImage = cv::Scalar(255,255,255);

	/*
	 * Create camera transformation matrix I_T_C
	 */
	double rhoWidth = sensorWidth / resolutionX;
	double rhoHeight = sensorHeight / resolutionY;

	double matrixK_data[3*3] = {(1/rhoWidth), 	0, 				u0,
	                            0,				(1/rhoHeight), 	v0,
	                            0,				0,				1};

	double matrixC_data[3*4] = {focalLength,	0,				0,		0,
								0,				focalLength,	0,		0,
								0,				0,				1,		0};

	cv::Mat matrixK(3,3,CV_64F,matrixK_data);
	cv::Mat matrixC(3,4,CV_64F,matrixC_data);

	I_T_C.create(3,4,CV_64F);

	I_T_C = matrixK * matrixC;


}


void CameraModel::drawCameraImagePoint(cv::Mat &C_point){

	cv::Mat I_point = I_T_C * C_point;

//	std::cout << "I_point: " << I_point << std::endl;
//	std::cout << (int)I_point.at<double>(0) << std::endl;
//	std::cout << (int)I_point.at<double>(1) << std::endl;
//	std::cout << (int)I_point.at<double>(2) << std::endl;
    int32_t u = I_point.at<double>(0) / I_point.at<double>(2);
    int32_t v = I_point.at<double>(1) / I_point.at<double>(2);

    cv::Point point(u,v);

    cv::circle(cameraImage,point,5,cv::Scalar(255,0,0),2);

}

void CameraModel::drawCameraImageLine(cv::Mat &C_point0, cv::Mat &C_point1){

	cv::Mat I_point0 = I_T_C * C_point0;
	cv::Mat I_point1 = I_T_C * C_point1;

    int32_t u0 = I_point0.at<double>(0) / I_point0.at<double>(2);
    int32_t v0 = I_point0.at<double>(1) / I_point0.at<double>(2);

    int32_t u1 = I_point1.at<double>(0) / I_point1.at<double>(2);
    int32_t v1 = I_point1.at<double>(1) / I_point1.at<double>(2);

    cv::Point point0(u0,v0);
    cv::Point point1(u1,v1);

    cv::line(cameraImage,point0,point1,cv::Scalar(255,0,0),1);

}

void CameraModel::resetCameraImage(){

	cameraImage = cv::Scalar(255,255,255);

}

cv::Mat &CameraModel::getCameraImage(){
	return cameraImage;
}
