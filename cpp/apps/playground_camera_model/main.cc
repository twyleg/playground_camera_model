// Copyright (C) 2024 twyleg
#include <unistd.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include <playground_camera_model/core/camera_model.h>
#include <playground_camera_model/core/homogeneous_transformation_matrix.h>

namespace HTM = playground_camera_model::homogeneous_transformation_matrix;

double deg_to_rad(double deg){
	return deg * (M_PI / 180.0);
}

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


	// Init camera model
	playground_camera_model::CameraModel cameraModel(0.00452, 0.00288, 0.004, 640, 480, 320, 240);

	// Init homogeneous transformation matrices
	HTM::Matrix W_T_V 		= HTM::Matrix({0,0,0, 0,0,0});
	HTM::Matrix V_T_C 		= HTM::Matrix({0,0,0, 0,0,0});
	HTM::Matrix C_T_V 		= V_T_C.inv();
	HTM::Matrix V_T_Cube 	= HTM::Matrix({2,0,1, 0,0,0});


	// Init points of cube
	HTM::Point3d Cube_cubeP0(-1, 1,-1);
	HTM::Point3d Cube_cubeP1(-1,-1,-1);
	HTM::Point3d Cube_cubeP2( 1,-1,-1);
	HTM::Point3d Cube_cubeP3( 1, 1,-1);

	HTM::Point3d Cube_cubeP4(-1, 1,1);
	HTM::Point3d Cube_cubeP5(-1,-1,1);
	HTM::Point3d Cube_cubeP6( 1,-1,1);
	HTM::Point3d Cube_cubeP7( 1, 1,1);

	HTM::Point3d V_cubeP0;
	HTM::Point3d V_cubeP1;
	HTM::Point3d V_cubeP2;
	HTM::Point3d V_cubeP3;

	HTM::Point3d V_cubeP4;
	HTM::Point3d V_cubeP5;
	HTM::Point3d V_cubeP6;
	HTM::Point3d V_cubeP7;

	HTM::Point3d C_cubeP0;
	HTM::Point3d C_cubeP1;
	HTM::Point3d C_cubeP2;
	HTM::Point3d C_cubeP3;

	HTM::Point3d C_cubeP4;
	HTM::Point3d C_cubeP5;
	HTM::Point3d C_cubeP6;
	HTM::Point3d C_cubeP7;

	// Create gui
	cv::namedWindow("image window", cv::WINDOW_AUTOSIZE);
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


	while(true){

		HTM::Matrix::Parameter vehicle_to_camera_parameter{
			(cameraSystemTranslationX-10000)/1000.0,
			(cameraSystemTranslationY-10000)/1000.0,
			(cameraSystemTranslationZ-10000)/1000.0,
			deg_to_rad(cameraSystemRotationRoll/10.0),
			deg_to_rad(cameraSystemRotationPitch/10.0),
			deg_to_rad(cameraSystemRotationYaw/10.0)
		};

		HTM::Matrix::Parameter vehicle_to_cube_parameter{
			(cubeSystemTranslationX-10000)/1000.0,
			(cubeSystemTranslationY-10000)/1000.0,
			(cubeSystemTranslationZ-10000)/1000.0,
			deg_to_rad(cubeSystemRotationRoll/10.0),
			deg_to_rad(cubeSystemRotationPitch/10.0),
			deg_to_rad(cubeSystemRotationYaw/10.0)
		};

		// Update homogeneous transformation matrices
		V_T_C = HTM::Matrix(vehicle_to_camera_parameter);
		C_T_V = V_T_C.inv();
		V_T_Cube = HTM::Matrix(vehicle_to_cube_parameter);

		// Transform and draw cube points and lines on image
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
		cameraModel.drawCameraImageLine(C_cubeP0, C_cubeP1);
		cameraModel.drawCameraImageLine(C_cubeP1, C_cubeP2);
		cameraModel.drawCameraImageLine(C_cubeP2, C_cubeP3);
		cameraModel.drawCameraImageLine(C_cubeP3, C_cubeP0);

		cameraModel.drawCameraImageLine(C_cubeP4, C_cubeP5);
		cameraModel.drawCameraImageLine(C_cubeP5, C_cubeP6);
		cameraModel.drawCameraImageLine(C_cubeP6, C_cubeP7);
		cameraModel.drawCameraImageLine(C_cubeP7, C_cubeP4);

		cameraModel.drawCameraImageLine(C_cubeP0, C_cubeP4);
		cameraModel.drawCameraImageLine(C_cubeP1, C_cubeP5);
		cameraModel.drawCameraImageLine(C_cubeP2, C_cubeP6);
		cameraModel.drawCameraImageLine(C_cubeP3, C_cubeP7);

		cv::imshow("image window", cameraModel.getCameraImage());

		// Wait for a short while
		cv::waitKey(10);
	}


}
