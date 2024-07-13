import cv2 as cv
from typing import Tuple

class EgoMouseControl:

    def __init__(self, pixel_per_deg: float = 1 / 0.25):
        self.pixel_per_deg = pixel_per_deg
        self.clicked = False
        self.mouse_pos: Tuple[int, int] | None = None

        self.delta_pitch = 0.0
        self.delta_yaw = 0.0

        cv.setMouseCallback("image window", self.mouse_callback)

    def mouse_callback(self, action, x, y, flags, *userdata):

        if action == 1:
            self.clicked = True
            self.mouse_pos = (x, y)
        elif action == 4:
            self.clicked = False
            self.delta_pitch = 0.0
            self.delta_yaw = 0.0

        if self.clicked:
            delta_x = x - self.mouse_pos[0]
            delta_y = -(y - self.mouse_pos[1])
            self.mouse_pos = (x, y)

            self.delta_pitch = delta_y / self.pixel_per_deg
            self.delta_yaw = delta_x / self.pixel_per_deg

    def get_delta_pitch(self) -> float:
        tmp = self.delta_pitch
        self.delta_pitch = 0.0
        return tmp

    def get_delta_yaw(self) -> float:
        tmp = self.delta_yaw
        self.delta_yaw = 0.0
        return tmp


class Window:

    def __init__(self):

        self.camera_system_translation_x = 0
        self.camera_system_translation_y = 0
        self.camera_system_translation_z = 0
        self.camera_system_rotation_roll = 0
        self.camera_system_rotation_pitch = 0
        self.camera_system_rotation_yaw = 0
        
        self.cube_system_translation_x = 0
        self.cube_system_translation_y = 0
        self.cube_system_translation_z = 0
        self.cube_system_rotation_roll = 0
        self.cube_system_rotation_pitch = 0
        self.cube_system_rotation_yaw = 0

        self.cube_system_scale = 0

        self.camera_window_name = "camera settings"
        self.cube_window_name = "cube settings"

        self.window_creator()
    
    def window_creator(self):
        # Create gui
        cv.namedWindow("image window", cv.WINDOW_AUTOSIZE)
        cv.namedWindow("camera settings", cv.WINDOW_AUTOSIZE)
        cv.namedWindow("cube settings", cv.WINDOW_AUTOSIZE)

        cv.createTrackbar("X", "camera settings", 0, 20000, self.nothing)
        cv.createTrackbar("Y", "camera settings", 0, 20000, self.nothing)
        cv.createTrackbar("Z", "camera settings", 0, 20000, self.nothing)
        cv.createTrackbar("Roll", "camera settings", 0, 3600, self.nothing)
        cv.createTrackbar("Pitch", "camera settings", 0, 3600, self.nothing)
        cv.createTrackbar("Yaw", "camera settings", 0, 3600, self.nothing)

        cv.createTrackbar("X", "cube settings", 0, 20000, self.nothing)
        cv.createTrackbar("Y", "cube settings", 0, 20000, self.nothing)
        cv.createTrackbar("Z", "cube settings", 0, 20000, self.nothing)
        cv.createTrackbar("Roll", "cube settings", 0, 3600, self.nothing)
        cv.createTrackbar("Pitch", "cube settings", 0, 3600, self.nothing)
        cv.createTrackbar("Yaw", "cube settings", 0, 3600, self.nothing)
        cv.createTrackbar("Scale", "cube settings", 1, 10, self.nothing)

        self.camera_system_translation_x = cv.setTrackbarPos("X", "camera settings", 10000)
        self.camera_system_translation_y = cv.setTrackbarPos("Y", "camera settings", 10000)
        self.camera_system_translation_z = cv.setTrackbarPos("Z", "camera settings", 11000)
        self.camera_system_rotation_roll = cv.setTrackbarPos("Roll", "camera settings", 2700)
        self.camera_system_rotation_pitch = cv.setTrackbarPos("Pitch", "camera settings", 0)
        self.camera_system_rotation_yaw = cv.setTrackbarPos("Yaw", "camera settings", 2700)

        self.cube_system_translation_x = cv.setTrackbarPos("X", "cube settings", 14000)
        self.cube_system_translation_y = cv.setTrackbarPos("Y", "cube settings", 10000)
        self.cube_system_translation_z = cv.setTrackbarPos("Z", "cube settings", 11000)
        self.cube_system_rotation_roll = cv.setTrackbarPos("Roll", "cube settings", 0)
        self.cube_system_rotation_pitch = cv.setTrackbarPos("Pitch", "cube settings", 0)
        self.cube_system_rotation_yaw = cv.setTrackbarPos("Yaw", "cube settings", 0)
        self.cube_system_scale = cv.setTrackbarPos("Scale", "cube settings", 1)

        self.ego_mouse_control = EgoMouseControl()



    def window_show(self, class_cam):
        cv.imshow("image window", class_cam.camera_image)
        cv.waitKey(10)

    def get_camera_system_translation_x(self):
        return cv.getTrackbarPos("X", self.camera_window_name)

    def get_camera_system_translation_y(self):
        return cv.getTrackbarPos("Y", self.camera_window_name)

    def get_camera_system_translation_z(self):
        return cv.getTrackbarPos("Z", self.camera_window_name)

    def get_camera_system_rotation_roll(self):
        return cv.getTrackbarPos("Roll", self.camera_window_name)

    def get_camera_system_rotation_pitch(self):
        return cv.getTrackbarPos("Pitch", self.camera_window_name)

    def get_camera_system_rotation_yaw(self):
        return cv.getTrackbarPos("Yaw", self.camera_window_name)

    def get_cube_system_translation_x(self):
        return cv.getTrackbarPos("X", self.cube_window_name)

    def get_cube_system_translation_y(self):
        return cv.getTrackbarPos("Y", self.cube_window_name)

    def get_cube_system_translation_z(self):
        return cv.getTrackbarPos("Z", self.cube_window_name)

    def get_cube_system_rotation_roll(self):
        return cv.getTrackbarPos("Roll", self.cube_window_name)

    def get_cube_system_rotation_pitch(self):
        return cv.getTrackbarPos("Pitch", self.cube_window_name)

    def get_cube_system_rotation_yaw(self):
        return cv.getTrackbarPos("Yaw", self.cube_window_name)
    
    def get_cube_system_scale(self):
        return cv.getTrackbarPos("Scale", self.cube_window_name)

    @staticmethod
    def nothing(x):
        pass
