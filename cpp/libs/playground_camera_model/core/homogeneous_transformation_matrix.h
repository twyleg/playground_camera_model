// Copyright (C) 2024 twyleg
#pragma once

#include <opencv2/opencv.hpp>

namespace playground_camera_model::homogeneous_transformation_matrix {

class Matrix: public cv::Mat{

public:

	struct Parameter {
		double transX;
		double transY;
		double transZ;
		double rotRoll;
		double rotPitch;
		double rotYaw;
	};

	Matrix(const Parameter&);
	Matrix(cv::MatExpr);

	Parameter mParameter;
};


class Point3d: public cv::Mat {

public:

	Point3d();
	Point3d(double x, double y, double z);
	Point3d(cv::MatExpr);


	double getX() const { return at<double>(0); }
	double getY() const { return at<double>(1); }
	double getZ() const { return at<double>(2); }
};

}
