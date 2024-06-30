// Copyright (C) 2024 twyleg
#include <unistd.h>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include <playground_camera_model/core/camera_model.h>
#include <playground_camera_model/core/gnuplot.h>
#include <playground_camera_model/core/homogeneous_transformation_matrix.h>

#define DEG_TO_RAD(x) (x*(M_PI/180.0))

GnuPlot *gnuPlot;

int main(int argc, char** argv){


	int32_t cameraSystemTranslationX = 10000;
	int32_t cameraSystemTranslationY = 10000;
	int32_t cameraSystemTranslationZ = 11000;

	int32_t cameraSystemRotationRoll = 2500;
	int32_t cameraSystemRotationPitch = 0;
	int32_t cameraSystemRotationYaw = 2700;

	int32_t cubeSystemTranslationX = 14000;
	int32_t cubeSystemTranslationY = 10000;
	int32_t cubeSystemTranslationZ = 11000;

	int32_t cubeSystemRotationRoll =  0;
	int32_t cubeSystemRotationPitch = 0;
	int32_t cubeSystemRotationYaw =   0;


	/*
	 * Init camera model
	 */
	CameraModel cameraModel(0.00452, 0.00288, 0.004, 640, 480, 320, 240);

	/*
	 * Init homogeneous transformation matrices
	 */
	cv::Mat W_T_V 		= HtmFactory::createHomogeneousTransformationMatrix(0,0,0,0,0,0);
	cv::Mat V_T_C 		= HtmFactory::createHomogeneousTransformationMatrix(0,0,0,0,0,0);
	cv::Mat C_T_V 		= V_T_C.inv();
	cv::Mat V_T_Cube 	= HtmFactory::createHomogeneousTransformationMatrix(2,0,1,0,0,0);


	/*
	 * Init points of cube
	 */
	cv::Mat Cube_cubeP0 = HtmFactory::createPoint(-1, 1,-1);
	cv::Mat Cube_cubeP1 = HtmFactory::createPoint(-1,-1,-1);
	cv::Mat Cube_cubeP2 = HtmFactory::createPoint( 1,-1,-1);
	cv::Mat Cube_cubeP3 = HtmFactory::createPoint( 1, 1,-1);

	cv::Mat Cube_cubeP4 = HtmFactory::createPoint(-1, 1,1);
	cv::Mat Cube_cubeP5 = HtmFactory::createPoint(-1,-1,1);
	cv::Mat Cube_cubeP6 = HtmFactory::createPoint( 1,-1,1);
	cv::Mat Cube_cubeP7 = HtmFactory::createPoint( 1, 1,1);

	cv::Mat V_cubeP0(4,1,CV_64F);
	cv::Mat V_cubeP1(4,1,CV_64F);
	cv::Mat V_cubeP2(4,1,CV_64F);
	cv::Mat V_cubeP3(4,1,CV_64F);

	cv::Mat V_cubeP4(4,1,CV_64F);
	cv::Mat V_cubeP5(4,1,CV_64F);
	cv::Mat V_cubeP6(4,1,CV_64F);
	cv::Mat V_cubeP7(4,1,CV_64F);

	cv::Mat C_cubeP0(4,1,CV_64F);
	cv::Mat C_cubeP1(4,1,CV_64F);
	cv::Mat C_cubeP2(4,1,CV_64F);
	cv::Mat C_cubeP3(4,1,CV_64F);

	cv::Mat C_cubeP4(4,1,CV_64F);
	cv::Mat C_cubeP5(4,1,CV_64F);
	cv::Mat C_cubeP6(4,1,CV_64F);
	cv::Mat C_cubeP7(4,1,CV_64F);

	/*
	 * Create gui
	 */
	cv::namedWindow("image window", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("gnuplot window", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("camera settings", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("cube settings", cv::WINDOW_AUTOSIZE);

	cv::createTrackbar("X", "camera settings", &cameraSystemTranslationX, 20000);
	cv::createTrackbar("Y", "camera settings", &cameraSystemTranslationY, 20000);
	cv::createTrackbar("Z", "camera settings", &cameraSystemTranslationZ, 20000);
	cv::createTrackbar("Roll", "camera settings", &cameraSystemRotationRoll, 3600);
	cv::createTrackbar("Pitch", "camera settings", &cameraSystemRotationPitch, 3600);
	cv::createTrackbar("Yaw", "camera settings", &cameraSystemRotationYaw, 3600);

	cv::createTrackbar("X", "cube settings", &cubeSystemTranslationX, 20000);
	cv::createTrackbar("Y", "cube settings", &cubeSystemTranslationY, 20000);
	cv::createTrackbar("Z", "cube settings", &cubeSystemTranslationZ, 20000);
	cv::createTrackbar("Roll", "cube settings", &cubeSystemRotationRoll, 3600);
	cv::createTrackbar("Pitch", "cube settings", &cubeSystemRotationPitch, 3600);
	cv::createTrackbar("Yaw", "cube settings", &cubeSystemRotationYaw, 3600);

	/*
	 * Visualize some stuff with gnuplot
	 */
	gnuPlot = new GnuPlot();
	gnuPlot->open();
	cv::Mat gnuplotImage;

	while(true){


		/*
		 *  Update homogeneous transformation matrices
		 */
		V_T_C = HtmFactory::createHomogeneousTransformationMatrix(
				(cameraSystemTranslationX-10000)/1000.0,
				(cameraSystemTranslationY-10000)/1000.0,
				(cameraSystemTranslationZ-10000)/1000.0,
				DEG_TO_RAD(cameraSystemRotationRoll/10.0),
				DEG_TO_RAD(cameraSystemRotationPitch/10.0),
				DEG_TO_RAD(cameraSystemRotationYaw/10.0));

		C_T_V = V_T_C.inv();

		V_T_Cube = HtmFactory::createHomogeneousTransformationMatrix(
				(cubeSystemTranslationX-10000)/1000.0,
				(cubeSystemTranslationY-10000)/1000.0,
				(cubeSystemTranslationZ-10000)/1000.0,
				DEG_TO_RAD(cubeSystemRotationRoll/10.0),
				DEG_TO_RAD(cubeSystemRotationPitch/10.0),
				DEG_TO_RAD(cubeSystemRotationYaw/10.0));

		/*
		 * Transform and draw cube points and lines on image
		 */

		C_cubeP0 = C_T_V * V_T_Cube * Cube_cubeP0;
		C_cubeP1 = C_T_V * V_T_Cube * Cube_cubeP1;
		C_cubeP2 = C_T_V * V_T_Cube * Cube_cubeP2;
		C_cubeP3 = C_T_V * V_T_Cube * Cube_cubeP3;

		C_cubeP4 = C_T_V * V_T_Cube * Cube_cubeP4;
		C_cubeP5 = C_T_V * V_T_Cube * Cube_cubeP5;
		C_cubeP6 = C_T_V * V_T_Cube * Cube_cubeP6;
		C_cubeP7 = C_T_V * V_T_Cube * Cube_cubeP7;

		cameraModel.resetCameraImage();

		// Points
		cameraModel.drawCameraImagePoint(C_cubeP0);
		cameraModel.drawCameraImagePoint(C_cubeP1);
		cameraModel.drawCameraImagePoint(C_cubeP2);
		cameraModel.drawCameraImagePoint(C_cubeP3);

		cameraModel.drawCameraImagePoint(C_cubeP4);
		cameraModel.drawCameraImagePoint(C_cubeP5);
		cameraModel.drawCameraImagePoint(C_cubeP6);
		cameraModel.drawCameraImagePoint(C_cubeP7);

		// Lines
		cameraModel.drawCameraImageLine(C_cubeP0,C_cubeP1);
		cameraModel.drawCameraImageLine(C_cubeP1,C_cubeP2);
		cameraModel.drawCameraImageLine(C_cubeP2,C_cubeP3);
		cameraModel.drawCameraImageLine(C_cubeP3,C_cubeP0);

		cameraModel.drawCameraImageLine(C_cubeP4,C_cubeP5);
		cameraModel.drawCameraImageLine(C_cubeP5,C_cubeP6);
		cameraModel.drawCameraImageLine(C_cubeP6,C_cubeP7);
		cameraModel.drawCameraImageLine(C_cubeP7,C_cubeP4);

		cameraModel.drawCameraImageLine(C_cubeP0,C_cubeP4);
		cameraModel.drawCameraImageLine(C_cubeP1,C_cubeP5);
		cameraModel.drawCameraImageLine(C_cubeP2,C_cubeP6);
		cameraModel.drawCameraImageLine(C_cubeP3,C_cubeP7);

		cv::imshow("image window",cameraModel.getCameraImage());

//		/*
//		 * Transform and draw cube points in 3D
//		 */
//		V_cubeP0 = V_T_Cube * Cube_cubeP0;
//		V_cubeP1 = V_T_Cube * Cube_cubeP1;
//		V_cubeP2 = V_T_Cube * Cube_cubeP2;
//		V_cubeP3 = V_T_Cube * Cube_cubeP3;
//
//		V_cubeP4 = V_T_Cube * Cube_cubeP4;
//		V_cubeP5 = V_T_Cube * Cube_cubeP5;
//		V_cubeP6 = V_T_Cube * Cube_cubeP6;
//		V_cubeP7 = V_T_Cube * Cube_cubeP7;
//
//		// Everything from here to stopMultiplot() will be ploted on the same graphic
//		gnuPlot->startMultiplot();
//
//		// Set axis scale
//		gnuPlot->setRangeX(-5, 5);
//		gnuPlot->setRangeY(-5, 5);
//		gnuPlot->setRangeZ(-5, 5);
//
//		// Draw coordinate systems
//		gnuPlot->drawCoordinateSystem(W_T_V, 1.5);
//		gnuPlot->drawCoordinateSystem(V_T_C, 1.5);
//
//		gnuPlot->drawPoint(V_cubeP0, "blue");
//		gnuPlot->drawPoint(V_cubeP1, "blue");
//		gnuPlot->drawPoint(V_cubeP2, "blue");
//		gnuPlot->drawPoint(V_cubeP3, "blue");
//
//		gnuPlot->drawPoint(V_cubeP4, "blue");
//		gnuPlot->drawPoint(V_cubeP5, "blue");
//		gnuPlot->drawPoint(V_cubeP6, "blue");
//		gnuPlot->drawPoint(V_cubeP7, "blue");
//
//		// Lines
//		gnuPlot->drawLine(V_cubeP0, V_cubeP1, "blue");
//		gnuPlot->drawLine(V_cubeP1, V_cubeP2, "blue");
//		gnuPlot->drawLine(V_cubeP2, V_cubeP3, "blue");
//		gnuPlot->drawLine(V_cubeP3, V_cubeP0, "blue");
//
//		gnuPlot->drawLine(V_cubeP4, V_cubeP5, "blue");
//		gnuPlot->drawLine(V_cubeP5, V_cubeP6, "blue");
//		gnuPlot->drawLine(V_cubeP6, V_cubeP7, "blue");
//		gnuPlot->drawLine(V_cubeP7, V_cubeP4, "blue");
//
//		gnuPlot->drawLine(V_cubeP0, V_cubeP4, "blue");
//		gnuPlot->drawLine(V_cubeP1, V_cubeP5, "blue");
//		gnuPlot->drawLine(V_cubeP2, V_cubeP6, "blue");
//		gnuPlot->drawLine(V_cubeP3, V_cubeP7, "blue");
//
//		gnuPlot->stopMultiplot();
//
//		bool escape = false;
//		while (!escape) {
//			try {
//				gnuplotImage = cv::imread("/tmp/gnuplot.png",
//						CV_LOAD_IMAGE_COLOR);
//				cv::imshow("gnuplot window", gnuplotImage);
//				escape = true;
//			} catch (cv::Exception& e) {
//				escape = false;
//				usleep(1000 * 1);
//			}
//		}




		/*
		 * Wait for a short while
		 */
		cv::waitKey(10);


	}


}



//	/*
//	 * Do some transformations
//	 */
//
//	// Create to two 4x4 matrices for transformations
//	cv::Mat W_T_V(4,4,CV_64F);
//	cv::Mat V_T_C(4,4,CV_64F);
//
//	// Create trasnformation matrices
//	createTransformationMatrix(W_T_V, 0,0,0,0,0,0);
//	createTransformationMatrix(V_T_C, 0,0,2,DEG_TO_RAD(-110),DEG_TO_RAD(0),DEG_TO_RAD(-90));
//
//	// Create a point C_point in camera system
//	cv::Mat C_point(4,1,CV_64F);
//	C_point.at<double>(0) = 1;	// Set X
//	C_point.at<double>(1) = 0;	// Set Y
//	C_point.at<double>(2) = 1;	// Set Z
//	C_point.at<double>(3) = 1;	// set scale factor to one
//
//	// Transfrom point from camera to vehicle system
//	cv::Mat V_point = V_T_C * C_point;
//
//	// Print the point vector
//	std::cout << V_point << std::endl;
//
//
//
//
//	/*
//	 * Visualize some stuff with gnuplot
//	 */
//	gnuPlot = new GnuPlot();
//	gnuPlot->open();
//
//	// Everything from here to stopMultiplot() will be ploted on the same graphic
//	gnuPlot->startMultiplot();
//
//	// Set axis scale
//	gnuPlot->setRangeX(-5,5);
//	gnuPlot->setRangeY(-5,5);
//	gnuPlot->setRangeZ(-5,5);
//
//	// Draw coordinate systems
//	drawCoordinateSystem(W_T_V,1.5);
//	drawCoordinateSystem(V_T_C,1.5);
//
//	// Plot the point
//	gnuPlot->drawPoint(V_point,"blue");
//
//	gnuPlot->stopMultiplot();



