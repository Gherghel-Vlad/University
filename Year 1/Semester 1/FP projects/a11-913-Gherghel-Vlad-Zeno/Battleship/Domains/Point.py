from math import sqrt


class Point:
    def __init__(self, x, y):
        self._x = x
        self._y = y

    @property
    def x(self):
        return self._x

    @property
    def y(self):
        return self._y

    @x.setter
    def x(self, value):
        self._x = value

    @y.setter
    def y(self, value):
        self._y = value

    def __eq__(self, other):
        return (self.x == other.x) and (self.y == other.y)

    def __add__(self, other):
        return Point(self.x + other.x, self.y + other.y)

    @staticmethod
    def distance(start, end):
        return sqrt((start.x - end.x) ** 2 + (start.y - end.y) ** 2)
