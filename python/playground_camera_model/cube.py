import numpy as np
from matrix_functions import Matrix_Functions

class Cube:

    def __init__(self):

        self.W_T_V = Matrix_Functions.create_homogeneous_transformation_matrix(0, 0, 0, 0, 0, 0)
        self.V_T_C = Matrix_Functions.create_homogeneous_transformation_matrix(0, 0, 0, 0, 0, 0)
        self.C_T_V = np.linalg.inv(self.V_T_C)
        self.V_T_Cube = Matrix_Functions.create_homogeneous_transformation_matrix(2, 0, 1, 0, 0, 0)


    def cube_creator(self, width, heigt, pos_x, pos_y, pos_z, scale, ):

        

        # Init points of cube
        Cube_cubeP0 = self.create_point(-1, 1, -1)
        Cube_cubeP1 = self.create_point(-1, -1, -1)
        Cube_cubeP2 = self.create_point(1, -1, -1)
        Cube_cubeP3 = self.create_point(1, 1, -1)

        Cube_cubeP4 = self.create_point(-1, 1, 1)
        Cube_cubeP5 = self.create_point(-1, -1, 1)
        Cube_cubeP6 = self.create_point(1, -1, 1)
        Cube_cubeP7 = self.create_point(1, 1, 1)

