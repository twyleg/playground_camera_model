import numpy as np
from math import cos, sin, pi


class Matrix_Functions:

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
