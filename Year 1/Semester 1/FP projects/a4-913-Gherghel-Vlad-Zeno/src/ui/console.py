"""
This is the user interface module. These functions call functions from the domain and functions module.
"""
from src.domain.entity import to_str
from src.functions.functions import delete_empty_elements_from_list, insert_new_contestant_at_position, \
    remove_contestant, remove_between_positions, replace_contestant_mark, sort_list, sign_list, add_new_contestant, \
    average_between_positions, lowest_average_between_positions, top_participants_by_average, top_participants_by_mark, \
    remove_participants_sign, undo_command, save_contestants_list_in_history


def show_list(contestants_list):
    """
    Prints the whole list of contestants in the console
    :param contestants_list: The list of contestants to be printed
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
    print("avg <start position> to <end position>")
    print("min <start position> to <end position>")
    print("top <number>")
    print("top <number> <P1 | P2 | P3>")
    print("remove [ < | = | > ] <score>")
    print("undo")
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
    elif len(tokens) == 3 and "to" not in tokens:
        try:
            remove_between_positions(contestants_list, int(tokens[0]), int(tokens[2]))
        except ValueError:
            print("Values are incorrect")
    elif len(tokens) == 2:
        try:
            avg_score = int(tokens[1])
        except ValueError:
            print("Write numbers pls :(")

        remove_participants_sign(contestants_list, tokens[0], avg_score)
    else:
        raise ValueError("Haha, wrong command")


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


def avg_command_ui(contestants_list, command_params):
    tokens = command_params.split(" ")
    delete_empty_elements_from_list(tokens)

    if len(tokens) != 3:
        raise ValueError("Problems in paradise. Wrong command")
    if "to" not in tokens:
        raise ValueError("Command wrong boye")
    try:
        start_pos = int(tokens[0])
        end_pos = int(tokens[2])
    except ValueError:
        print("Write numbers pls :(")

    print(average_between_positions(contestants_list, start_pos, end_pos))


def min_command_ui(contestants_list, command_params):
    tokens = command_params.split(" ")
    delete_empty_elements_from_list(tokens)

    if len(tokens) != 3:
        raise ValueError("Problems in paradise. Wrong command")
    if "to" not in tokens:
        raise ValueError("Command wrong boye")
    try:
        start_pos = int(tokens[0])
        end_pos = int(tokens[2])
    except ValueError:
        print("Write numbers pls :(")

    print(lowest_average_between_positions(contestants_list, start_pos, end_pos))


def top_command_ui(contestants_list, command_params):
    tokens = command_params.split(" ")
    delete_empty_elements_from_list(tokens)

    try:
        number = int(tokens[0])
    except ValueError:
        print("Write numbers pls :(")

    if len(tokens) == 1:
        show_list(top_participants_by_average(contestants_list, number))
    elif len(tokens) == 2:
        show_list(top_participants_by_mark(contestants_list, number, tokens[1]))
    else:
        print("Write the command correctly pls")




def undo_command_ui(contestants_list, history_list):
    undo_command(contestants_list, history_list)


def save_list_in_history_ui(contestants_list, history_list):
    save_contestants_list_in_history(contestants_list, history_list)






