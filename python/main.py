import numpy as np
import cv2 as cv
from math import cos, sin, pi
import time

from playground_camera_model.camera_model import CameraModel
from playground_camera_model.matrix_functions import Matrix_Functions
from playground_camera_model.window import Window
#from playground_camera_model.cube import Cube



class Engine:

    def __init__(self):

        self.camera_model = CameraModel(0.00452, 0.00254, 0.004, 1280, 720, 1280/2, 720/2)
        self.window = Window()
        
        self.start_time = time.time()
        self.frame_count = 0

    @staticmethod  
    def create_point(x: float, y: float, z: float) -> np.array:
        return np.array([
            [x],
            [y],
            [z],
            [1]
        ])

    @staticmethod
    def DEG_TO_RAD(deg: float) -> float:
        return deg*(pi/180.0)
    

    def fps_setter(self):
        #Calculate FPS
        self.frame_count += 1
        elapsed_time = time.time() - self.start_time
        fps = self.frame_count / elapsed_time
        cv.putText(self.camera_model.camera_image, f"FPS: {fps:.0f}", (10, 30), cv.FONT_HERSHEY_PLAIN, 1.2, (0, 255, 0), 1)


    def main(self):


        #cube1 = Cube.cube_creator(width, heigt, pos_x, pos_y, pos_z)


        # Init points of cube
        Cube_cubeP0 = self.create_point(-1, 1, -1)
        Cube_cubeP1 = self.create_point(-1, -1, -1)
        Cube_cubeP2 = self.create_point(1, -1, -1)
        Cube_cubeP3 = self.create_point(1, 1, -1)

        Cube_cubeP4 = self.create_point(-1, 1, 1)
        Cube_cubeP5 = self.create_point(-1, -1, 1)
        Cube_cubeP6 = self.create_point(1, -1, 1)
        Cube_cubeP7 = self.create_point(1, 1, 1)

        c_roll = 270.0
        c_pitch = 0.0
        c_yaw = 270.0

        while True:

            c_roll += self.window.ego_mouse_control.get_delta_pitch()
            c_yaw += -self.window.ego_mouse_control.get_delta_yaw()

            # Update homogeneous transformation matrices
            V_T_C = Matrix_Functions.create_homogeneous_transformation_matrix(
                (self.window.get_camera_system_translation_x() - 10000) / 1000.0,
                (self.window.get_camera_system_translation_y() - 10000) / 1000.0,
                (self.window.get_camera_system_translation_z() - 10000) / 1000.0,
                self.DEG_TO_RAD(c_roll),
                self.DEG_TO_RAD(c_pitch),
                self.DEG_TO_RAD(c_yaw),
                1
            )

            C_T_V = np.linalg.inv(V_T_C)

            V_T_Cube = Matrix_Functions.create_homogeneous_transformation_matrix(
                (self.window.get_cube_system_translation_x() - 10000) / 1000.0,
                (self.window.get_cube_system_translation_y() - 10000) / 1000.0,
                (self.window.get_cube_system_translation_z() - 10000) / 1000.0,
                self.DEG_TO_RAD(self.window.get_cube_system_rotation_roll() / 10.0),
                self.DEG_TO_RAD(self.window.get_cube_system_rotation_pitch() / 10.0),
                self.DEG_TO_RAD(self.window.get_cube_system_rotation_yaw() / 10.0),
                self.window.get_cube_system_scale()
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

            self.camera_model.reset_camera_image()

            # Points
            self.camera_model.draw_camera_image_point(C_cubeP0)
            self.camera_model.draw_camera_image_point(C_cubeP1)
            self.camera_model.draw_camera_image_point(C_cubeP2)
            self.camera_model.draw_camera_image_point(C_cubeP3)

            self.camera_model.draw_camera_image_point(C_cubeP4)
            self.camera_model.draw_camera_image_point(C_cubeP5)
            self.camera_model.draw_camera_image_point(C_cubeP6)
            self.camera_model.draw_camera_image_point(C_cubeP7)

            # Lines
            self.camera_model.draw_camera_image_line(C_cubeP0, C_cubeP1)
            self.camera_model.draw_camera_image_line(C_cubeP1, C_cubeP2)
            self.camera_model.draw_camera_image_line(C_cubeP2, C_cubeP3)
            self.camera_model.draw_camera_image_line(C_cubeP3, C_cubeP0)

            self.camera_model.draw_camera_image_line(C_cubeP4, C_cubeP5)
            self.camera_model.draw_camera_image_line(C_cubeP5, C_cubeP6)
            self.camera_model.draw_camera_image_line(C_cubeP6, C_cubeP7)
            self.camera_model.draw_camera_image_line(C_cubeP7, C_cubeP4)

            self.camera_model.draw_camera_image_line(C_cubeP0, C_cubeP4)
            self.camera_model.draw_camera_image_line(C_cubeP1, C_cubeP5)
            self.camera_model.draw_camera_image_line(C_cubeP2, C_cubeP6)
            self.camera_model.draw_camera_image_line(C_cubeP3, C_cubeP7)


            self.camera_model.fill_poly([C_cubeP0, C_cubeP1, C_cubeP2])

            self.fps_setter()
            self.window.window_show(self.camera_model)


engine = Engine()
engine.main()