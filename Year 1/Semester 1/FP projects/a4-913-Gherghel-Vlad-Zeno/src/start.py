"""
Assemble the program and start the user interface here
"""
from src.functions.functions import test_init
from src.ui.console import add_command_ui, insert_command_ui, remove_command_ui, replace_command_ui, list_command_ui, \
    read_user_command, show_all_commands, split_command, avg_command_ui, min_command_ui, top_command_ui, \
    undo_command_ui, save_list_in_history_ui


def start_command_menu_ui():
    """
    The starting menu
    :return: -
    """
    contestants_list = []
    history_list = []
    test_init(contestants_list)
    command_dict = {"add": add_command_ui, "insert": insert_command_ui, "remove": remove_command_ui,
                    "replace": replace_command_ui, "list": list_command_ui, "avg": avg_command_ui,
                    "min": min_command_ui, "top": top_command_ui,}
    done = False

    while not done:
        try:
            show_all_commands()
            command = read_user_command()
            command_name, command_params = split_command(command)
            if command_name == "exit":
                done = True
            elif command_name == "undo":
                undo_command_ui(contestants_list, history_list);
            elif command_name in command_dict:
                if command_name in ["add", "insert", "remove", "replace"]:
                    save_list_in_history_ui(contestants_list, history_list)
                command_dict[command_name](contestants_list, command_params)
            else:
                print("The command does not exist.")
        except ValueError as val:
            print(val)


start_command_menu_ui()


