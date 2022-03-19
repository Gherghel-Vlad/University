#
# Write the implementation for A3 in this file
#

#
# domain section is here (domain = numbers, transactions, expenses, etc.)
# getters / setters
# No print or input statements in this section
# Specification for all non-trivial functions (trivial usually means a one-liner)
import copy


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

# Functionalities section (functions that implement required features)
# No print or input statements in this section
# Specification for all non-trivial functions (trivial usually means a one-liner)
# Each function does one thing only
# Functions communicate using input parameters and their return values


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

    if len(contestants_list) == 0: # Here we treat the case where the list is empty
        contestants_list.append(create_contestant(p1, p2, p3))
    else:
        contestants_list.append(create_contestant(0, 0, 0))
        for index in range(len(contestants_list)-1, position - 1, -1):
            contestants_list[index] = contestants_list[index-1]
        contestants_list[position] = create_contestant(p1, p2, p3)


def remove_contestant(contestants_list, position):
    """
    Sets the contestant's marks that is on the given position to 0
    :param contestants_list: Contestants list (list of dictionaries)
    :param position: The position to be removed
    :return: -
    Raise ValueError if position is not correct
    """
    if position > len(contestants_list)-1 or position < 0:
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
    if start_position<0 or start_position > len(contestants_list)-1:
        raise ValueError("Start position is not correct")

    if end_position<0 or end_position > len(contestants_list)-1:
        raise ValueError("End position is not correct")

    if start_position > end_position:
        raise ValueError("Start position needs to be less or equal to end position")

    for index in range(start_position, end_position+1):
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
    if position<0 or position>len(contestants_list)-1:
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
        for j in range(i+1, len(new_list)):
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


# UI section
# (all functions that have input or print statements, or that CALL functions with print / input are  here).
# Ideally, this section should not contain any calculations relevant to program functionalities


def show_list(contestants_list):
    """
    Prints the whole list of contestants in the console
    :param list: The list of contestants to be printed
    :return: -
    """
    for i in range(0, len(contestants_list)):
        print(i, ".   ", to_str(contestants_list[i]))


def read_user_command():
    """
    Reads the user's input
    :return: The user's input
    """
    return input("Give command: ")


def show_all_commands():
    """
    Shows all possible commands to the user
    :return: -
    """
    print("Available commands:")
    print("add < P1 score > < P2 score > < P3 score >")
    print("insert < P1 score > < P2 score > < P3 score > at < position >")
    print("remove <position>")
    print("remove <start position> to <end position>")
    print("replace <old score> <P1 | P2 | P3> with <new score>")
    print("list")
    print("list sorted")
    print("list [ < | = | > ] <score>")
    print("exit")


def split_command(command):
    """
    Splits the user's input into command name and command params
    :param command: The user's input
    :return: The command's name and the command's params
    """
    tokens = str(command).lower().strip().split(" ", 1)
    return tokens[0].lower().strip(), tokens[1].lower().strip() if len(tokens) == 2 else ""


def add_command_ui(contestants_list, command_params):
    tokens = command_params.split(" ")
    delete_empty_elements_from_list(tokens)

    if len(tokens) != 3:
        raise ValueError("There must be 3 scores")

    try:
        add_new_contestant(contestants_list, int(tokens[0]), int(tokens[1]), int(tokens[2]))
    except ValueError:
        print("The scores must be an integer between [0, 10]")


def insert_command_ui(contestants_list, command_params):
    tokens = command_params.split(" ")
    delete_empty_elements_from_list(tokens)

    if len(tokens) != 5 or "at" not in tokens:
        raise ValueError("Something is wrong with the command. Please write it again")

    try:
        insert_new_contestant_at_position(contestants_list, int(tokens[0]), int(tokens[1]), int(tokens[2]), int(tokens[4]))
    except ValueError:
        print("Values are incorrect")


def remove_command_ui(contestants_list, command_params):
    tokens = command_params.split(" ")
    delete_empty_elements_from_list(tokens)
    if len(tokens) == 1:
        try:
            remove_contestant(contestants_list, int(tokens[0]))
        except ValueError:
            print("Invalid values")
    else:
        if len(tokens) != 3 or "to" not in tokens:
            raise ValueError("Something is wrong with the command. Please write it again.")

        try:
            remove_between_positions(contestants_list, int(tokens[0]), int(tokens[2]))
        except ValueError:
            print("Values are incorrect")


def replace_command_ui(contestants_list, command_params):
    tokens = command_params.split(" ")
    delete_empty_elements_from_list(tokens)

    if len(tokens) != 4 or "with" not in tokens:
        raise ValueError("Command is incorrect. Please rewrite it.")

    try:
        replace_contestant_mark(contestants_list, int(tokens[0]), tokens[1], int(tokens[3]))
    except ValueError:
        print("Values are not correct")


def list_command_ui(contestants_list, command_params):
    tokens = command_params.split(" ")
    delete_empty_elements_from_list(tokens)

    if len(tokens) == 0:
        show_list(contestants_list)
    elif len(tokens) == 1 and tokens[0] == "sorted":
        new_list = sort_list(contestants_list)
        show_list(new_list)
    elif len(tokens) == 2:
        try:
            new_list = sign_list(contestants_list, tokens[0], int(tokens[1]))
            show_list(new_list)
        except ValueError:
            print("Value is incorrect")
    else:
        print("The command is wrong. Please write it correctly.")


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


def start_command_menu_ui():
    """
    The starting menu
    :return: -
    """
    contestants_list = []
    test_init(contestants_list)
    command_dict = {"add": add_command_ui, "insert": insert_command_ui, "remove": remove_command_ui,
                    "replace": replace_command_ui, "list": list_command_ui}
    done = False

    while not done:
        try:
            show_all_commands()
            command = read_user_command()
            command_name, command_params = split_command(command)
            if command_name == "exit":
                done = True
            elif command_name in command_dict:
                command_dict[command_name](contestants_list, command_params)
            else:
                print("The command does not exist.")
        except ValueError as val:
            print(val)


start_command_menu_ui()

# Test functions go here
#
# Test functions:
#   - no print / input
#   - great friends with assert


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
    assert len(contestants_list) == len_contestants_list+1 and contestants_list[5] == create_contestant(3, 4, 5)

    len_contestants_list = len(contestants_list)
    insert_new_contestant_at_position(contestants_list, 3, 4, 5, 0)
    assert len(contestants_list) == len_contestants_list+1 and contestants_list[0] == create_contestant(3, 4, 5)

    len_contestants_list = len(contestants_list)
    insert_new_contestant_at_position(contestants_list, 3, 4, 5, len_contestants_list)
    assert len(contestants_list) == len_contestants_list+1 and contestants_list[len(contestants_list)-1] == create_contestant(3, 4, 5)


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
