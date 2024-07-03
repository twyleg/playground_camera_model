import numpy as np
import cv2 as cv


from math import cos, sin, pi

from playground_camera_model.camera_model import CameraModel


def create_homogeneous_transformation_matrix(translation_x: float, translation_y: float, translation_z: float,
                                             rotation_roll: float, rotation_pitch: float, rotation_yaw: float) -> np.array:

    rotation_matrix_roll = np.array([
        [1,	                    0,					0,					0],
        [0,	                    cos(rotation_roll),	-sin(rotation_roll),0],
        [0,	                    sin(rotation_roll),	cos(rotation_roll),	0],
        [0,	                    0,					0,					1]
    ])

    rotation_matrix_pitch = np.array([
        [cos(rotation_pitch),	0,	                sin(rotation_pitch),0],
        [0,					    1,	                0,					0],
        [-sin(rotation_pitch),  0,	                cos(rotation_pitch),0],
        [0,					    0,	                0,					1]
    ])

    rotation_matrix_yaw = np.array([
        [cos(rotation_yaw),	    -sin(rotation_yaw),	0,	                0],
        [sin(rotation_yaw),     cos(rotation_yaw),	0,	                0],
        [0,					    0,					1,	                0],
        [0,					    0,					0,	                1]
    ])

    translation_matrix = np.array([
        [1,	0,	0,  translation_x],
        [0,	1,	0,	translation_y],
        [0,	0,	1,	translation_z],
        [0,	0,	0,	1]
    ])

    return np.matmul(translation_matrix, np.matmul(np.matmul(rotation_matrix_yaw, rotation_matrix_pitch), rotation_matrix_roll))


def create_point(x: float, y: float, z: float) -> np.array:
    return np.array([
        [x],
        [y],
        [z],
        [1]
    ])


def DEG_TO_RAD(deg: float) -> float:
    return deg*(pi/180.0)


if __name__ == "__main__":
    print("Started")

    camera_model = CameraModel(0.00452, 0.00288, 0.004, 640, 480, 320, 240)
    print(camera_model.I_T_C)

    W_T_V = create_homogeneous_transformation_matrix(0, 0, 0, 0, 0, 0)
    V_T_C = create_homogeneous_transformation_matrix(0, 0, 0, 0, 0, 0)
    C_T_V = np.linalg.inv(V_T_C)
    V_T_Cube = create_homogeneous_transformation_matrix(2, 0, 1, 0, 0, 0)

    # Init points of cube
    Cube_cubeP0 = create_point(-1, 1, -1)
    Cube_cubeP1 = create_point(-1, -1, -1)
    Cube_cubeP2 = create_point(1, -1, -1)
    Cube_cubeP3 = create_point(1, 1, -1)

    Cube_cubeP4 = create_point(-1, 1, 1)
    Cube_cubeP5 = create_point(-1, -1, 1)
    Cube_cubeP6 = create_point(1, -1, 1)
    Cube_cubeP7 = create_point(1, 1, 1)

    V_cubeP0(4, 1, CV_64F)
    V_cubeP1(4, 1, CV_64F)
    V_cubeP2(4, 1, CV_64F)
    V_cubeP3(4, 1, CV_64F)

    V_cubeP4(4, 1, CV_64F)
    V_cubeP5(4, 1, CV_64F)
    V_cubeP6(4, 1, CV_64F)
    V_cubeP7(4, 1, CV_64F)

    C_cubeP0(4, 1, CV_64F)
    C_cubeP1(4, 1, CV_64F)
    C_cubeP2(4, 1, CV_64F)
    C_cubeP3(4, 1, CV_64F)

    C_cubeP4(4, 1, CV_64F)
    C_cubeP5(4, 1, CV_64F)
    C_cubeP6(4, 1, CV_64F)
    C_cubeP7(4, 1, CV_64F)

    # Create gui
    cv.namedWindow("image window", cv.WINDOW_AUTOSIZE)
    cv.namedWindow("camera settings", cv.WINDOW_AUTOSIZE)
    cv.namedWindow("cube settings", cv.WINDOW_AUTOSIZE)


    def nothing(x):
        pass

    cv.createTrackbar("X", "camera settings", 0, 20000, nothing)
    cv.createTrackbar("Y", "camera settings", 0, 20000, nothing)
    cv.createTrackbar("Z", "camera settings", 0, 20000, nothing)
    cv.createTrackbar("Roll", "camera settings", 0, 3600, nothing)
    cv.createTrackbar("Pitch", "camera settings", 0, 3600, nothing)
    cv.createTrackbar("Yaw", "camera settings", 0, 3600, nothing)

    cv.createTrackbar("X", "cube settings", 0, 20000, nothing)
    cv.createTrackbar("Y", "cube settings", 0, 20000, nothing)
    cv.createTrackbar("Z", "cube settings", 0, 20000, nothing)
    cv.createTrackbar("Roll", "cube settings", 0, 3600, nothing)
    cv.createTrackbar("Pitch", "cube settings", 0, 3600, nothing)
    cv.createTrackbar("Yaw", "cube settings", 0, 3600, nothing)


    while True:
        camera_system_translation_x = cv.getTrackbarPos("x", "camera settings")
        camera_system_translation_y = cv.getTrackbarPos("y", "camera settings")
        camera_system_translation_z = cv.getTrackbarPos("z", "camera settings")
        camera_system_rotation_roll = cv.getTrackbarPos("roll", "camera settings")
        camera_system_rotation_pitch = cv.getTrackbarPos("pitch", "camera settings")
        camera_system_rotation_yaw = cv.getTrackbarPos("yaw", "camera settings")

        cube_system_translation_x = cv.getTrackbarPos("x", "cube settings")
        cube_system_translation_y = cv.getTrackbarPos("y", "cube settings")
        cube_system_translation_z = cv.getTrackbarPos("z", "cube settings")
        cube_system_rotation_roll = cv.getTrackbarPos("roll", "cube settings")
        cube_system_rotation_pitch = cv.getTrackbarPos("pitch", "cube settings")
        cube_system_rotation_yaw = cv.getTrackbarPos("yaw", "cube settings")

        # Update homogeneous transformation matrices
        V_T_C = create_homogeneous_transformation_matrix(
            (camera_system_translation_x - 10000) / 1000.0,
            (camera_system_translation_y - 10000) / 1000.0,
            (camera_system_translation_z - 10000) / 1000.0,
            DEG_TO_RAD(camera_system_rotation_roll / 10.0),
            DEG_TO_RAD(camera_system_rotation_pitch / 10.0),
            DEG_TO_RAD(camera_system_rotation_yaw / 10.0)
        )

        C_T_V = np.linalg.inv(V_T_C)

        V_T_Cube = create_homogeneous_transformation_matrix(
            (cube_system_translation_x - 10000) / 1000.0,
            (cube_system_translation_y - 10000) / 1000.0,
            (cube_system_translation_z - 10000) / 1000.0,
            DEG_TO_RAD(cube_system_rotation_roll / 10.0),
            DEG_TO_RAD(cube_system_rotation_pitch / 10.0),
            DEG_TO_RAD(cube_system_rotation_yaw / 10.0)
        )

        # Transform and draw cube points and lines on image
        C_cubeP0 = C_T_V @ V_T_Cube @ Cube_cubeP0
        C_cubeP1 = C_T_V @ V_T_Cube @ Cube_cubeP1
        C_cubeP2 = C_T_V @ V_T_Cube @ Cube_cubeP2
        C_cubeP3 = C_T_V @ V_T_Cube @ Cube_cubeP3

        C_cubeP4 = C_T_V @ V_T_Cube @ Cube_cubeP4
        C_cubeP5 = C_T_V @ V_T_Cube @ Cube_cubeP5
        C_cubeP6 = C_T_V @ V_T_Cube @ Cube_cubeP6
        C_cubeP7 = C_T_V @ V_T_Cube @ Cube_cubeP7

        camera_model.reset_camera_image()

        # Points
        camera_model.draw_camera_image_point(C_cubeP0)
        camera_model.draw_camera_image_point(C_cubeP1)
        camera_model.draw_camera_image_point(C_cubeP2)
        camera_model.draw_camera_image_point(C_cubeP3)

        camera_model.draw_camera_image_point(C_cubeP4)
        camera_model.draw_camera_image_point(C_cubeP5)
        camera_model.draw_camera_image_point(C_cubeP6)
        camera_model.draw_camera_image_point(C_cubeP7)

        # Lines
        camera_model.draw_camera_image_line(C_cubeP0, C_cubeP1)
        camera_model.draw_camera_image_line(C_cubeP1, C_cubeP2)
        camera_model.draw_camera_image_line(C_cubeP2, C_cubeP3)
        camera_model.draw_camera_image_line(C_cubeP3, C_cubeP0)

        camera_model.draw_camera_image_line(C_cubeP4, C_cubeP5)
        camera_model.draw_camera_image_line(C_cubeP5, C_cubeP6)
        camera_model.draw_camera_image_line(C_cubeP6, C_cubeP7)
        camera_model.draw_camera_image_line(C_cubeP7, C_cubeP4)

        camera_model.draw_camera_image_line(C_cubeP0, C_cubeP4)
        camera_model.draw_camera_image_line(C_cubeP1, C_cubeP5)
        camera_model.draw_camera_image_line(C_cubeP2, C_cubeP6)
        camera_model.draw_camera_image_line(C_cubeP3, C_cubeP7)

        cv.imshow("image window", camera_model.camera_image)

        # Wait for a short while
        cv.waitKey(10)

