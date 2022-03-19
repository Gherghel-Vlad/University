import configparser
from secrets import choice

from texttable import Texttable

from domains.Point import Point
from domains.Snake import Snake, SnakeException


class TableException(Exception):
    def __init__(self, ms):
        super().__init__(ms)
        self._ms = ms

    @property
    def ms(self):
        return self._ms


class Table:
    def __init__(self, snake):
        """
        Legend:
            - 0 - means free space
            - 1 - means apple
            - 2 - means tail
            - 3 - means head
        """
        self.config = configparser.ConfigParser()
        self.config.read("settings.properties")

        self._dim = int(self.config["Settings"]["dim"])
        self._apple_count = int(self.config["Settings"]["apple_count"])

        self._table_matrix = [[0 for i in range(self._dim)] for j in range(self._dim)]
        self._snake = snake

        self.set_snake_starting_position()
        self.set_apples(self._apple_count)

    def update_table_matrix(self):
        """
        Updates the table matrix with the snake s current positions
        :return: -
        """
        for i in range(self._dim):
            for j in range(self._dim):
                if self.get_table_coordinate_value(Point(i, j)) in [2, 3]:
                    self.set_table_coordinate_value(Point(i, j), 0)

        snake_coordinates = self._snake.get_coordinates()
        self.set_table_coordinate_value(snake_coordinates[-1], 3)

        snake_coordinates = snake_coordinates[:-1]
        for point in snake_coordinates:
            self.set_table_coordinate_value(point, 2)

    def get_apple_coordinates(self):
        """
        Gets all coordinates where there are apples
        :return: A list containing the corodinates of the apples (list of Points)
        """
        apple_coords = []
        for i in range(self._dim):
            for j in range(self._dim):
                if self._table_matrix[i][j] == 1:
                    apple_coords.append(Point(i, j))
        return apple_coords

    def check_coordinate(self, coord):
        """
        Checks the given coordinate
        :param coord: The given coordinate
        :return: True if its okay, false if not
        """
        if coord.x < 0 or coord.x >= self._dim or coord.y < 0 or coord.y >= self._dim:
            return False

        return True

    def set_snake_starting_position(self):
        """
        Sets the starting positions of the snake and the snake on the table
        :return: -
        """
        self._snake.set_snake_coordinates(self._dim)

        snake_coordinates = self._snake.get_coordinates()
        self.set_table_coordinate_value(snake_coordinates[-1], 3)

        snake_coordinates = snake_coordinates[:-1]
        for point in snake_coordinates:
            self.set_table_coordinate_value(point, 2)

    def get_possibly_apple_spaces(self):
        """
        Gets the spaces where i can put apples
        :return: A list containing all the coordinates that possible
        """
        new_list = []
        for i in range(self._dim):
            for j in range(self._dim):
                if self._table_matrix[i][j] == 0 and not self.check_for_apple_position_posibility(Point(i, j)):
                    new_list.append(Point(i, j))

        return new_list

    def get_table_coordinate_value(self, coord):
        return self._table_matrix[coord.x][coord.y]

    def set_table_coordinate_value(self, coord, value):
        self._table_matrix[coord.x][coord.y] = value

    def check_for_apple_position_posibility(self, coord):
        """
        Checks if there are apples in the vicinity of the coordinate (horizontally or vertically
        :return: True if there are, False otherwise
        """
        x_list = [0, 0, 1, -1]
        y_list = [1, -1, 0, 0]

        for i in range(4):
            new_x = coord.x + x_list[i]
            new_y = coord.y + y_list[i]

            if not self.check_coordinate(Point(new_x, new_y)):
                continue

            value = self.get_table_coordinate_value(Point(new_x, new_y))

            if value == 1:
                return True

        return False

    def set_apples(self, n):
        """
        Sets n apples on the tabel if it can
        :param n: The number of apples to set (n)
        :return: -
        """
        while n > 0:
            free_coordinates = self.get_possibly_apple_spaces()

            # if there are no more free spaces
            if len(free_coordinates) == 0:
                break

            coord = choice(free_coordinates)

            self.set_table_coordinate_value(coord, 1)

            n -= 1

    def move_snake(self, n):
        """
        Moves the snake n positions in the direction it faces
        :param n: The number of positions to move
        :return: -
        """
        list_of_apples_coordinates = self.get_apple_coordinates()
        if len(list_of_apples_coordinates) == 0:
            raise TableException("Game won!")

        try:
            nr_of_apple_eaten = self._snake.move_snake(n, list_of_apples_coordinates)
        except SnakeException as se:
            raise TableException(se.ms)

        self.set_apples(nr_of_apple_eaten)

        list_of_apples_coordinates = self.get_apple_coordinates()
        if len(list_of_apples_coordinates) == 0:
            raise TableException("Game won!")

        self.update_table_matrix()

    def move_direction(self, direction):
        """
        Changes the direction of the snake and moves it by 1
        :param direction: String value from [left, right, up, down]
        :return: -
        """
        snake_dir = self._snake.direction
        if direction == "right" and snake_dir == "left" or direction == "up" and snake_dir == "down" or direction == "left" and snake_dir == "right" or direction == "down" and snake_dir == "up":
            raise TableException("You can't make a 180 degrees move.")
        if direction == snake_dir:
            return
        self._snake.direction = str(direction).strip()
        self.move_snake(1)

    def __str__(self):
        """
        Creates a string representation of the table
        :return: A string representation of the table
        """
        t = Texttable()
        for row in range(self._dim):
            row_data = []

            for val in self._table_matrix[row]:
                if val == 1:
                    row_data.append(".")
                elif val == 2:
                    row_data.append("+")
                elif val == 3:
                    row_data.append("*")
                else:
                    row_data.append(" ")

            t.add_row(row_data)

        return t.draw()


