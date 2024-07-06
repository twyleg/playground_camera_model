# Copyright (C) 2024 twyleg
import numpy as np
import cv2 as cv
from typing import List


class CameraModel:
    def __init__(self, sensor_width: float, sensor_height: float, focal_length: float, resolution_x: int, resolution_y: int, u0: int, v0: int):
        self.sensor_width: float = sensor_width
        self.sensor_height: float = sensor_height
        self.focal_length: float = focal_length
        self.resolution_x: int = resolution_x
        self.resolution_y: int = resolution_y
        self.u0: int = u0
        self.v0: int = v0

        self.camera_image = np.zeros((resolution_y, resolution_x, 3), dtype=np.uint8)
        self.reset_camera_image()

        # Create camera transformation matrix I_T_C
        rho_width = sensor_width / resolution_x
        rho_height = sensor_height / resolution_y

        matrix_k = np.array([
            [1/rho_width,   0,              u0],
            [0,             1/rho_height,   v0],
            [0,             0,               1],
        ])

        matrix_c = np.array([
            [focal_length,  0,              0,  0],
            [0,             focal_length,   0,  0],
            [0,             0,              1,  0],
        ])

        self.I_T_C = matrix_k @ matrix_c

    def draw_camera_image_point(self, C_point: np.array) -> None:

        I_point = np.matmul(self.I_T_C, C_point)
        u = int(I_point[0] / I_point[2])
        v = int(I_point[1] / I_point[2])

        cv.circle(self.camera_image, (u, v), 5, (255,0,0), 2)

    def draw_camera_image_line(self, C_point0: np.array, C_point1: np.array) -> None:

        I_point0 = self.I_T_C @ C_point0
        I_point1 = self.I_T_C @ C_point1

        u0 = int(I_point0[0] / I_point0[2])
        v0 = int(I_point0[1] / I_point0[2])

        u1 = int(I_point1[0] / I_point1[2])
        v1 = int(I_point1[1] / I_point1[2])

        cv.line(self.camera_image, (u0, v0), (u1, v1), (255,0,0), 1)

    def fill_poly(self, C_points: List[np.array]) -> None:
        I_points = []

        for C_point in C_points:
            I_point = self.I_T_C @ C_point
            
            u0 = int(I_point[0] / I_point[2])
            v0 = int(I_point[1] / I_point[2])

            I_points.append((u0, v0))

        poly_points = np.array(I_points)

        cv.fillPoly(self.camera_image, [poly_points], (255,0,0))

    def reset_camera_image(self) -> None:
        self.camera_image.fill(255)
