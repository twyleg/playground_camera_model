// Copyright (C) 2024 twyleg
#include "homogeneous_transformation_matrix.h"


namespace playground_camera_model::homogeneous_transformation_matrix {

namespace {

cv::Mat createHomogeneousTransformationMatrix(const Matrix::Parameter& p){


	double rotationMatrixRollData[4*4] =  {	1,	0,					0,					0,
											0,	cos(p.rotRoll),		-sin(p.rotRoll),	0,
											0,	sin(p.rotRoll),		cos(p.rotRoll),		0,
											0,	0,					0,					1};

	double rotationMatrixPitchData[4*4] = {	cos(p.rotPitch),	0,	sin(p.rotPitch),	0,
											0,					1,	0,					0,
											-sin(p.rotPitch),	0,	cos(p.rotPitch),	0,
											0,					0,	0,					1};

	double rotationMatrixYawData[4*4] =  {	cos(p.rotYaw),		-sin(p.rotYaw),		0,	0,
											sin(p.rotYaw),		cos(p.rotYaw),		0,	0,
											0,					0,					1,	0,
											0,					0,					0,	1};

	double translationMatrixData[4*4] =  {	1,	0,	0,	p.transX,
											0,	1,	0,	p.transY,
											0,	0,	1,	p.transZ,
											0,	0,	0,	1};

	cv::Mat rotationMatrixRoll(4,4,CV_64F,rotationMatrixRollData);
	cv::Mat rotationMatrixPitch(4,4,CV_64F,rotationMatrixPitchData);
	cv::Mat rotationMatrixYaw(4,4,CV_64F,rotationMatrixYawData);
	cv::Mat translationMatrix(4,4,CV_64F,translationMatrixData);

	return (translationMatrix * ((rotationMatrixYaw*rotationMatrixPitch)*rotationMatrixRoll));
}

}


Matrix::Matrix(const Parameter& parameter)
	: cv::Mat(createHomogeneousTransformationMatrix(parameter)),
	  mParameter(parameter)
{}

Matrix::Matrix(cv::MatExpr matExpr)
	: cv::Mat(matExpr)
{}


Point3d::Point3d()
	: cv::Mat(4,1,CV_64F)
{}

Point3d::Point3d(double x, double y, double z)
	: cv::Mat(4,1,CV_64F)
{
	at<double>(0) = x;
	at<double>(1) = y;
	at<double>(2) = z;
	at<double>(3) = 1;
}

Point3d::Point3d(cv::MatExpr matExpr)
	: cv::Mat(matExpr)
{}


}
