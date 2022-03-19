"""
Functions that implement program features. They should call each other, or other functions from the domain
"""
from src.domain.entity import create_contestant, set_p3, set_p2, set_p1, calculate_average_mark, get_p1, get_p2, get_p3
import copy


def change_2_positions_between_them(contestants_list, position1, position2):
    """
    Changes the position of 2 contestants between them
    :param contestants_list: Contestants list (list of dictionaries)
    :param position1: First contestant's position
    :param position2: Second contestant's position
    :return: -
    """
    arg = contestants_list[position1]
    contestants_list[position1] = contestants_list[position2]
    contestants_list[position2] = arg


def add_new_contestant(contestants_list, p1, p2, p3):
    """
    Adds a new contestant to the list
    :param contestants_list: Contestants list (list of dictionaries)
    :param p1: First mark
    :param p2: Second mark
    :param p3: Third mark
    :return: -
    """
    contestants_list.append(create_contestant(p1, p2, p3))


def insert_new_contestant_at_position(contestants_list, p1, p2, p3, position):
    """
    Adds a new contestant to the list
    :param contestants_list: Contestants list (list of dictionaries)
    :param p1: First mark
    :param p2: Second mark
    :param p3: Third mark
    :param position: The position in the list where the new contestant will be inserted
    :return: -
    Raise ValueError if position is outside of bounds
    """
    if position > len(contestants_list) or position < 0:
        raise ValueError("Position must be a correct one")

    if len(contestants_list) == 0:  # Here we treat the case where the list is empty
        contestants_list.append(create_contestant(p1, p2, p3))
    else:
        contestants_list.append(create_contestant(0, 0, 0))
        for index in range(len(contestants_list) - 1, position - 1, -1):
            contestants_list[index] = contestants_list[index - 1]
        contestants_list[position] = create_contestant(p1, p2, p3)


def remove_contestant(contestants_list, position):
    """
    Sets the contestant's marks that is on the given position to 0
    :param contestants_list: Contestants list (list of dictionaries)
    :param position: The position to be removed
    :return: -
    Raise ValueError if position is not correct
    """
    if position > len(contestants_list) - 1 or position < 0:
        raise ValueError("Position is not correct")

    contestant = contestants_list[position]
    set_p1(contestant, 0)
    set_p2(contestant, 0)
    set_p3(contestant, 0)


def remove_between_positions(contestants_list, start_position, end_position):
    """
    Sets the score of the participants from start_position to end_position to 0
    :param contestants_list:
    :param start_position:
    :param end_position:
    :return: -
    Raises ValueError if one of the positions is out of bounds or they are not correctly written ( start_position<=enn_position)
    """
    if start_position < 0 or start_position > len(contestants_list) - 1:
        raise ValueError("Start position is not correct")

    if end_position < 0 or end_position > len(contestants_list) - 1:
        raise ValueError("End position is not correct")

    if start_position > end_position:
        raise ValueError("Start position needs to be less or equal to end position")

    for index in range(start_position, end_position + 1):
        contestants_list[index] = create_contestant(0, 0, 0)


def replace_contestant_mark(contestants_list, position, mark, mark_value):
    """
    Replaces the mark from the contestant that s on the given position with the mark_value given
    :param contestants_list: Contestants list (list of dictionaries)
    :param position: The contestant's position
    :param mark: The mark to be changed (p1, p2 or p3)
    :param mark_value: The new value that the mark will have
    :return: -
    Raise ValueError when mark_value is not a correct one, mark isnt a correct one or if the position out of bounds
    """
    if position < 0 or position > len(contestants_list) - 1:
        raise ValueError("Position is out of bounds")

    mark = str(mark).lower().strip()
    if mark not in ["p1", "p2", "p3"]:
        raise ValueError("Wrong mark name")

    if mark_value not in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]:
        raise ValueError("Mark value wrong. It should be an integer between [0, 10]")

    if mark == "p1":
        set_p1(contestants_list[position], mark_value)
    elif mark == "p2":
        set_p2(contestants_list[position], mark_value)
    elif mark == "p3":
        set_p3(contestants_list[position], mark_value)


def sort_list(contestants_list):
    """
    Returns a list that has all the given lists elements sorted in a decreasing order of average score
    :param contestants_list:
    :return: A new list that contains the sorted elements of the original list in a decreasing order of average score
    """
    new_list = copy.deepcopy(contestants_list)
    for i in range(0, len(new_list)):
        for j in range(i + 1, len(new_list)):
            if calculate_average_mark(new_list[i]) > calculate_average_mark(new_list[j]):
                change_2_positions_between_them(new_list, i, j)

    return new_list


def sign_list(contestants_list, sign, value):
    """
    Creates a new list with the given properties
    :param contestants_list: Contestants list (list of dictionaries)
    :param sign: The sign that will be the condition for the new list creation together with the value
    :param value: The value that s going to be used with the sign
    :return: A new list consisting of all the elements that succeeded the condition
    Raise ValueError if invalid sign or value
    """

    if value < 0 or value > 10:
        raise ValueError("The value must be in [0,10]")

    sign = str(sign).lower().strip()
    if sign not in ["<", "=", ">"]:
        raise ValueError("Invalid sign")

    new_list = []

    if sign == "<":
        for i in range(0, len(contestants_list)):
            if calculate_average_mark(contestants_list[i]) < value:
                new_list.append(contestants_list[i])
    elif sign == "=":
        for i in range(0, len(contestants_list)):
            if calculate_average_mark(contestants_list[i]) == value:
                new_list.append(contestants_list[i])
    elif sign == ">":
        for i in range(0, len(contestants_list)):
            if calculate_average_mark(contestants_list[i]) > value:
                new_list.append(contestants_list[i])

    return new_list


def delete_empty_elements_from_list(list):
    """
    Deletes the empty elements ( '' or "" ) from a list
    :param list: The list with the elements
    :return: -
    """
    # Gotta take care of extra spaces between params
    i = 0
    while i < len(list):
        if list[i] == "":
            list.pop(i)
        else:
            i += 1


def average_between_positions(contestants_list, start_pos, end_pos):
    """
    Calculates the average score of average scores between positions given
    :param contestants_list: The contestants list (dict)
    :param start_pos: The starting position in the list
    :param end_pos: The ending position in the list
    :return: The average score of the averages between the positions given
    Raises ValueError if the positions given are incorrect
    Raises ValueError if start pos < end pos
    """
    if start_pos < 0 or end_pos > len(contestants_list) - 1:
        raise ValueError("The positions are out of the list")
    if start_pos > end_pos:
        raise ValueError("Start position needs to be bigger than end position................dumb")

    avg_sum = 0;

    for i in range(0, end_pos - start_pos + 1):
        avg_sum = avg_sum + calculate_average_mark(contestants_list[start_pos+i])

    return avg_sum/(end_pos-start_pos+1)


def lowest_average_between_positions(contestants_list, start_pos, end_pos):
    """
    Returns the lowest average between the given postions
    :param contestants_list: The contestants list (dict)
    :param start_pos: The starting position in the list
    :param end_pos: The ending position in the list
    :return: The lowest average in the given positions
    Raises ValueError if the positions given are incorrect
    Raises ValueError if start pos < end pos
    """

    if start_pos < 0 or end_pos > len(contestants_list) - 1:
        raise ValueError("The positions are out of the list")
    if start_pos > end_pos:
        raise ValueError("Start position needs to be bigger than end position................dumb")

    minimum_avg = 11

    for i in range(0, end_pos-start_pos+1):
        if minimum_avg > calculate_average_mark(contestants_list[start_pos+i]):
            minimum_avg = calculate_average_mark(contestants_list[start_pos+i])

    return minimum_avg


def top_participants_by_average(contestants_list, number):
    """
    Creats a list consisting of the top (number value) participants by average score
    :param contestants_list: The contestants list (dict)
    :param number: The number of participants to be returned
    :return: A list consisting of the top (number value) participants
    Raises ValueError if the number is bigger than the number of participants by average score
    """
    if len(contestants_list) < number:
        raise ValueError("There aren't so many participants. Please try another number.")

    new_list = sorted(contestants_list, key=calculate_average_mark, reverse=True)

    top_list = []
    for index in range(0, number):
        top_list.append(new_list[index])

    return top_list


def top_participants_by_mark(contestants_list, number, mark):
    """
    Creates a list consisting of the top (number value) participants by a mark
    :param contestants_list: The contestants list (dict)
    :param number: The number of participants to be returned
    :param mark: The mark which the sorting will use
    :return: A list consisting of the top (number value) participants that have the highest mark in that
    Raises ValueError if the number is bigger than the number of participants by a mark
    Raises ValueError if the mark is incorrect
    """
    if len(contestants_list) < number:
        raise ValueError("There aren't so many participants. Please try another number.")

    mark = str(mark).strip().lower()
    if mark not in ["p1", "p2", "p3"]:
        raise ValueError("Mark is incorrect")

    if mark == "p1":
        new_list = sorted(contestants_list, key=get_p1, reverse=True)
    elif mark == 'p2':
        new_list = sorted(contestants_list, key=get_p2, reverse=True)
    elif mark == "p3":
        new_list = sorted(contestants_list, key=get_p3, reverse=True)

    top_list = []
    for index in range(0, number):
        top_list.append(new_list[index])

    return top_list


def remove_participants_sign(contestants_list, sign, value):
    """
    Sets the value of the participants that have the average score <, =, > than the value to 0
    :param contestants_list: The contestants list (dict)
    :param sign: It can be: <, =, > and it will be applied to the comparison
    :param value: The value that s going to be compared to the average score of the participants
    :return: -
    Raises ValueError if the sign is invalid
    Raises ValueError if the value is not in 0 and 10
    """
    sign = str(sign).strip().lower()
    if sign not in ["<", "=", ">"]:
        raise ValueError("The sign is invalid")

    if value < 0 or value > 10:
        raise ValueError("Value needs to be in [0,10]")

    if sign == '<':
        for contestant in contestants_list:
            if calculate_average_mark(contestant) < value:
                set_p1(contestant, 0)
                set_p2(contestant, 0)
                set_p3(contestant, 0)
    elif sign == '=':
        for contestant in contestants_list:
            if calculate_average_mark(contestant) == value:
                set_p1(contestant, 0)
                set_p2(contestant, 0)
                set_p3(contestant, 0)
    elif sign == '>':
        for contestant in contestants_list:
            if calculate_average_mark(contestant) > value:
                set_p1(contestant, 0)
                set_p2(contestant, 0)
                set_p3(contestant, 0)


def save_contestants_list_in_history(contestants_list, history_list):
    """
    Saves the contestants list in the history list
    :param contestants_list: The contestants list
    :param history_list: The list representing the past contestants list
    :return: -
    """
    history_list.append(copy.deepcopy(contestants_list))


def undo_command(contestants_list, history_list):
    """
    Undo the last command that has been applied
    :param contestants_list: The contestants list
    :param history_list: The history list containing contestants lists prior to the last change
    :return: -
    Raises ValueError if there is no command to undo
    """
    if len(history_list) == 0:
        raise ValueError("There is no command to undo")

    contestants_list.clear()
    for contestant in history_list[-1]:
        contestants_list.append(contestant)
    history_list.pop()


# Tests

def test_init(test_list):
    """
    Appends 10 dummy entries to the given list
    :param test_list: The contestants list
    :return: -
    """
    test_list.append(create_contestant(4, 9, 8))
    test_list.append(create_contestant(8, 8, 3))
    test_list.append(create_contestant(10, 10, 10))
    test_list.append(create_contestant(3, 1, 9))
    test_list.append(create_contestant(5, 1, 6))
    test_list.append(create_contestant(1, 1, 1))
    test_list.append(create_contestant(1, 7, 10))
    test_list.append(create_contestant(3, 2, 2))
    test_list.append(create_contestant(8, 5, 1))
    test_list.append(create_contestant(9, 9, 10))


def test_insert_new_contestant_at_position():
    contestants_list = []
    test_init(contestants_list)

    try:
        insert_new_contestant_at_position(contestants_list, 1, 2, 3, -1)
        assert False
    except ValueError as val:
        assert True

    try:
        insert_new_contestant_at_position(contestants_list, 1, 2, 3, 11)
        assert False
    except ValueError as val:
        assert True

    len_contestants_list = len(contestants_list)
    insert_new_contestant_at_position(contestants_list, 3, 4, 5, 5)
    assert len(contestants_list) == len_contestants_list + 1 and contestants_list[5] == create_contestant(3, 4, 5)

    len_contestants_list = len(contestants_list)
    insert_new_contestant_at_position(contestants_list, 3, 4, 5, 0)
    assert len(contestants_list) == len_contestants_list + 1 and contestants_list[0] == create_contestant(3, 4, 5)

    len_contestants_list = len(contestants_list)
    insert_new_contestant_at_position(contestants_list, 3, 4, 5, len_contestants_list)
    assert len(contestants_list) == len_contestants_list + 1 and contestants_list[
        len(contestants_list) - 1] == create_contestant(3, 4, 5)


test_insert_new_contestant_at_position()


def test_remove_contestant():
    test_list = []
    test_init(test_list)

    try:
        remove_contestant(test_list, -1)
        assert False
    except ValueError as val:
        assert True

    try:
        remove_contestant(test_list, 11)
        assert False
    except ValueError as val:
        assert True

    len_test_list = len(test_list)
    remove_contestant(test_list, 5)
    assert len_test_list == len(test_list) and test_list[5] == create_contestant(0, 0, 0)


test_remove_contestant()


def test_remove_between_positions():
    contestants_list = []
    test_init(contestants_list)

    try:
        remove_between_positions(contestants_list, -1, 3)
        assert False
    except ValueError as val:
        assert True
    try:
        remove_between_positions(contestants_list, 0, 13)
        assert False
    except ValueError as val:
        assert True
    try:
        remove_between_positions(contestants_list, -1, 33)
        assert False
    except ValueError as val:
        assert True
    try:
        remove_between_positions(contestants_list, 3, 1)
        assert False
    except ValueError as val:
        assert True

    len_contestants_list = len(contestants_list)
    remove_between_positions(contestants_list, 4, 6)
    assert len_contestants_list == len(contestants_list) and contestants_list[4] == create_contestant(0, 0, 0)
    assert contestants_list[5] == create_contestant(0, 0, 0) and contestants_list[6] == create_contestant(0, 0, 0)

    remove_between_positions(contestants_list, 9, 9)
    assert contestants_list[9] == create_contestant(0, 0, 0)


test_remove_between_positions()


def test_replace_contestant_mark():
    contestants_list = []
    test_init(contestants_list)

    try:
        replace_contestant_mark(contestants_list, -1, "p1", 4)
        assert False
    except ValueError:
        assert True
    try:
        replace_contestant_mark(contestants_list, 4, "p4", 4)
        assert False
    except ValueError:
        assert True
    try:
        replace_contestant_mark(contestants_list, 4, "p1", 12.5)
        assert False
    except ValueError:
        assert True
    try:
        replace_contestant_mark(contestants_list, 4, "p1", -1)
        assert False
    except ValueError:
        assert True

    replace_contestant_mark(contestants_list, 4, "p1", 7)
    assert get_p1(contestants_list[4]) == 7

    replace_contestant_mark(contestants_list, 8, "p2", 9)
    assert get_p2(contestants_list[8]) == 9

    replace_contestant_mark(contestants_list, 9, "p3", 0)
    assert get_p3(contestants_list[9]) == 0


test_replace_contestant_mark()


def test_sign_list():
    contestants_list = []
    test_init(contestants_list)

    try:
        sign_list(contestants_list, "!", 4)
        assert False
    except ValueError:
        assert True

    try:
        sign_list(contestants_list, "<>", 4)
        assert False
    except ValueError:
        assert True

    try:
        sign_list(contestants_list, "<", 20)
        assert False
    except ValueError:
        assert True

    new_list = sign_list(contestants_list, "<", 3)
    assert len(new_list) == 2

    new_list = sign_list(contestants_list, "=", 10)
    assert len(new_list) == 1

    new_list = sign_list(contestants_list, ">", 9)
    assert len(new_list) == 2


test_sign_list()


def test_sort_list():
    contestants_list = []
    test_init(contestants_list)
    new_list = sort_list(contestants_list)

    assert len(new_list) == len(contestants_list) and new_list[-1] == create_contestant(10, 10, 10)
    assert new_list[0] == create_contestant(1, 1, 1)


test_sort_list()


def test_average_between_positions():
    contestants_list = []
    test_init(contestants_list)
    try:
        average_between_positions(contestants_list, -1, 10)
        assert False
    except ValueError:
        assert True
    try:
        average_between_positions(contestants_list, -1, 11)
        assert False
    except ValueError:
        assert True
    try:
        average_between_positions(contestants_list, 2, 13)
        assert False
    except ValueError:
        assert True

    avg = average_between_positions(contestants_list, 4, 6)

    assert avg == 11 / 3


test_average_between_positions()


def test_lowest_average_between_positions():
    contestants_list = []
    test_init(contestants_list)
    try:
        lowest_average_between_positions(contestants_list, -1, 10)
        assert False
    except ValueError:
        assert True
    try:
        lowest_average_between_positions(contestants_list, -1, 11)
        assert False
    except ValueError:
        assert True
    try:
        lowest_average_between_positions(contestants_list, 2, 13)
        assert False
    except ValueError:
        assert True

    minimum = lowest_average_between_positions(contestants_list, 0, 9)

    assert minimum == 1


test_lowest_average_between_positions()


def test_top_participants_by_average():
    contestants_list = []
    test_init(contestants_list)
    new_list = []
    try:
        new_list = top_participants_by_average(contestants_list, 11)
        assert False
    except ValueError:
        assert True

    new_list = top_participants_by_average(contestants_list, 4)
    assert len(new_list) == 4 and new_list[0] == create_contestant(10, 10, 10)


test_top_participants_by_average()


def test_top_participants_by_mark():
    contestants_list = []
    test_init(contestants_list)

    try:
        top_participants_by_mark(contestants_list, 11, "p1")
        assert False
    except ValueError:
        assert True

    try:
        top_participants_by_mark(contestants_list, 3, "p4")
        assert False
    except ValueError:
        assert True

    new_list = []
    new_list = top_participants_by_mark(contestants_list, 3, "p1")
    assert len(new_list) == 3 and new_list[0] == create_contestant(10, 10, 10)
    new_list = top_participants_by_mark(contestants_list, 4, "p2")
    assert len(new_list) == 4 and new_list[0] == create_contestant(10, 10, 10)
    new_list = top_participants_by_mark(contestants_list, 10, "p3")
    assert len(new_list) == 10 and new_list[0] == create_contestant(10, 10, 10)


test_top_participants_by_mark()


def test_remove_participants_sign():
    contestants_list = []
    test_init(contestants_list)

    try:
        remove_participants_sign(contestants_list, "!=", 4)
        assert False
    except ValueError:
        assert True

    try:
        remove_participants_sign(contestants_list, "=", 40)
        assert False
    except ValueError:
        assert True

    try:
        remove_participants_sign(contestants_list, "=", -4)
        assert False
    except ValueError:
        assert True

    remove_participants_sign(contestants_list, "=", calculate_average_mark(contestants_list[0]))
    assert contestants_list[0] == create_contestant(0, 0, 0)

    remove_participants_sign(contestants_list, "<", 2)
    assert contestants_list[5] == create_contestant(0, 0, 0)

    remove_participants_sign(contestants_list, ">", 9)
    assert contestants_list[2] == create_contestant(0, 0, 0)


test_remove_participants_sign()


def test_save_contestants_list_in_history():
    contestants_list = []
    test_init(contestants_list)
    history_list = []
    save_contestants_list_in_history(contestants_list, history_list)
    assert len(history_list) == 1 and history_list[0] == contestants_list


test_save_contestants_list_in_history()


def test_undo_command():
    contestants_list = []
    test_init(contestants_list)
    history_list = []

    try:
        undo_command(contestants_list, history_list)
        assert False
    except ValueError:
        assert True

    # Saves the current list
    save_contestants_list_in_history(contestants_list, history_list)

    # Uses a command that changes the contestants list
    add_new_contestant(contestants_list, 0, 1, 2)
    assert len(history_list) == 1 and len(contestants_list) == 11

    # Undo the command
    undo_command(contestants_list, history_list)
    assert len(history_list) == 0 and len(contestants_list) == 10


test_undo_command()
