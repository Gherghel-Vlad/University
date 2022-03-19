"""
Domain file includes code for entity management
entity = number, transaction, expense etc.
"""


def create_contestant(p1, p2, p3):
    """
    Creates a new contestant
    :param p1: The first mark
    :param p2: The second mark
    :param p3: The third mark
    :return: A dictionary representing the contestant's marks
    Raise ValueError when the marks are not an integer between [0, 10]
    """
    if p1 not in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]:
        raise ValueError("The p1 mark is not a valid one.")
    if p2 not in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]:
        raise ValueError("The p2 mark is not a valid one.")
    if p3 not in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]:
        raise ValueError("The p3 mark is not a valid one.")
    return {"p1": p1, "p2": p2, "p3": p3}


def get_p1(contestant):
    return contestant["p1"]


def get_p2(contestant):
    return contestant["p2"]


def get_p3(contestant):
    return contestant["p3"]


def set_p1(contestant, value):
    contestant['p1'] = value


def set_p2(contestant, value):
    contestant['p2'] = value


def set_p3(contestant, value):
    contestant['p3'] = value


def to_str(contestant):
    """
    Returns a string that represents a marks of the contestant
    :param contestant: The contestant
    :return: A string with the marks of the contestant
    """
    return str(get_p1(contestant)) + " " + str(get_p2(contestant)) + " " + str(get_p3(contestant))


def calculate_average_mark(contestant):
    """
    Calculates the average mark of the student
    :param contestant: The contestant (dictionary)
    :return: A float number representing the average mark
    """
    return (get_p1(contestant) + get_p2(contestant) + get_p3(contestant))/3


# Tests

def test_create_contestant():

    assert create_contestant(1, 2, 3) == {"p1": 1, "p2": 2, "p3": 3}

    try:
        create_contestant(11, 9, 9)
        assert False
    except ValueError as val:
        assert True
    try:
        create_contestant(1, 99, 9)
        assert False
    except ValueError as val:
        assert True
    try:
        create_contestant(10, 9, -1)
        assert False
    except ValueError as val:
        assert True


test_create_contestant()
