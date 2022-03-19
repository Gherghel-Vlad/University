import math
from random import *


def create_circle(x, y, r):
    """
    Creates a circle with the given center (x, y) and the radius r
    :param x: The x coordinate of the center
    :param y: The y coordiante of the center
    :param r: The radius of the circle
    :return: A dictionary
    """
    if not isinstance(x, int) or not isinstance(y, int) or not isinstance(r, int):
        raise ValueError("The numbers need to be integers")

    return {"x": x, "y": y, "r": r}


def get_x(circle):
    return circle["x"]


def get_y(circle):
    return circle["y"]


def get_r(circle):
    return circle["r"]


def set_x(circle, value):
    circle["x"] = value


def set_y(circle, value):
    circle["y"] = value


def set_r(circle, value):
    circle["r"] = value


def to_str(circle):
    return get_x(circle), get_y(circle), get_r(circle)


def circle_exists(circles_list, circle):
    if circle in circles_list:
        return True
    return False


def create_random_circle():
    done = False

    while not done:
        x = randint(0, 20)
        y = randint(0, 20)
        r = randint(0, 20)
        if x - r > 0 and x + r < 20 and y - r > 0 and y + r < 20:
            done = True

    return create_circle(x, y, r)


def calculate_distance_to_second_diagonal(circle):
    first_distance = get_y(circle) - get_x(circle)
    second_distance = get_x(circle) - get_y(circle)
    return min(first_distance, second_distance)


def interchange_2_circles_in_a_list(circles_list, i, j):
    aug = circles_list[i]
    circles_list[i] = circles_list[j]
    circles_list[j] = aug
