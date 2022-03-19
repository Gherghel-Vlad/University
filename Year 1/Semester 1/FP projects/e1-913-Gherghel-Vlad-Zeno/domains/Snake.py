import configparser
import copy

from domains.Point import Point


class SnakeException(Exception):
    def __init__(self, ms):
        super().__init__(ms)
        self._ms = ms

    @property
    def ms(self):
        return self._ms


class Snake:
    def __init__(self):
        self.config = configparser.ConfigParser()
        self.config.read("settings.properties")

        self._dim = int(self.config["Settings"]["dim"])

        self._direction = "up"
        self._coordinates = []  # the end represents where the head is

    @property
    def direction(self):
        return self._direction

    @direction.setter
    def direction(self, value):
        self._direction = value

    def get_coordinates(self):
        return self._coordinates

    def add_coordinate_end_snake(self, coord):
        """
        Ads the coordinate at the bottom of the list (representing a eating of an apple)
        :param coord: The coordinate (point instance)
        :return: -
        """
        new_list = []
        new_list.append(0)
        new_list.append(self._coordinates)
        new_list[0] = coord
        self._coordinates = copy.deepcopy(new_list)

    def set_snake_coordinates(self, dim):
        """
        Sets the snake's coords
        :param dim: The table dimension
        :return: -
        """
        mid = dim // 2
        self._coordinates.append(Point(mid + 1, mid))
        self._coordinates.append(Point(mid, mid))
        self._coordinates.append(Point(mid - 1, mid))

    def move_tail(self):
        """
        Moves the tail
        :return: -
        """
        self._coordinates = self._coordinates[1:]

    def check_new_coordinates(self, coord):
        """
        Checks if the new coordinates are correct:
            - goes outside the table = death
            - hits himself = death
        :param coord: The coordinates to be checked
        :return: -
        raises SnakeException if it happens one of those 2 cases
        """
        if coord.x < 0 or coord.x >= self._dim or coord.y < 0 or coord.y >= self._dim or coord in self.get_coordinates():
            raise SnakeException("Game over!")

    def move_snake(self, n, apple_list_coord):
        """
        Moves the snake n positions in the direction it is facing
        :param n: The number of positions moved
        :param apple_list_coord: The apple's coordinates
        :return: The number of apples eaten (int)
        """
        head = []
        nr = 0
        for i in range(n):
            head = copy.deepcopy(self._coordinates[-1])
            if self.direction == "up":
                head.x -= 1
            elif self.direction == "right":
                head.y += 1
            elif self.direction == "left":
                head.y -= 1
            elif self.direction == "down":
                head.x += 1
            if head not in apple_list_coord:
                self.move_tail()
            else:
                nr += 1

            self.check_new_coordinates(head)
            self._coordinates.append(head)

        return nr
