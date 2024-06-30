// Copyright (C) 2024 twyleg
#pragma once

#include <opencv2/opencv.hpp>

class HomogeneousTransformationMatrixFactory;
typedef HomogeneousTransformationMatrixFactory HtmFactory;

class HomogeneousTransformationMatrixFactory{

private:


public:



	static cv::Mat createHomogeneousTransformationMatrix(
			double translationX,
			double translationY,
			double translationZ,
			double rotationRoll,
			double rotationPitch,
			double rotationYaw);


	static cv::Mat createPoint(double x, double y, double z);

};
