from playground_camera_model.cube import Cube

class Structure_Generator:

    @staticmethod
    def ground(width, height, depth, size=1, start_x=0, start_y=0, start_z=0):
        """
        Generate a ground structure of cubes with the specified width, height, and depth.
        """
        cubes = []

        for z in range(height):
            for row in range(width):
                for col in range(depth):
                    pos_x = start_x + col * size*2
                    pos_y = start_y + row * size*2
                    pos_z = start_z + z * size*2
                    cub = Cube(size, pos_x, pos_y, pos_z)
                    cubes.append(cub)

        return cubes
    
    @staticmethod
    def tree(width, height, depth, size=1, start_x=0, start_y=0, start_z=0):

        cubes = []

        #3 height
        for y in range(3):
            pos_x = start_x
            pos_y = start_y
            pos_z = start_z + y * size*2
            cub = Cube(size, pos_x, pos_y, pos_z)
            cubes.append(cub)

        width1 = width  # Assuming width is defined somewhere
        depth1 = depth  # Assuming depth is defined somewhere
        start_y = 3  # Starting position on the y-axis

        for y in range(3):  # Loop for each layer of the pyramid
            for row in range(width1):  # Loop through rows of cubes
                for col in range(depth1):  # Loop through columns of cubes
                    # Calculate position for each cube
                    pos_x = width1 // 2 + col * size * 2
                    pos_y = depth1 // 2 + row * size * 2
                    pos_z = start_y + y * size * 2
                    
                    # Create a cube and append to the list
                    cub = Cube(size, pos_x, pos_y, pos_z)
                    cubes.append(cub)
            
            # Decrease width and depth for the next layer
            width1 -= 2
            depth1 -= 2


        return cubes
        #5,5
        #3,3
        #1,1