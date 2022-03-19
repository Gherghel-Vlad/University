# Source code for Test 1 program. Success!

import re


def create_function(function_name, params, value_params, signs):
    return {"name": function_name, "params": params, "value_params": value_params, "signs": signs}


def read_command():
    return input("Give command: ")


def split_command(command):
    tokens = str(command).strip().split(" ")
    return tokens[0].strip().lower(), tokens[1].strip() if len(tokens) == 2 else ""


def split_function_def(function):
    """
    Splits the function in the 2 parts
    :param function: The whole definition of the function
    :return: -
    """
    tokens = str(function).strip().split("=")
    try:
        return tokens[0].lower(), tokens[1].lower()
    except Exception:
        raise ValueError("Wrong function definition")


def split_function_name_params(function_def):
    """
    Splits the part before =
    :param function_def: The whole part of the function
    :return:
    """
    tokens = str(function_def).strip().split("(")
    return tokens[0], tokens[1]


def split_function_params(function_params):
    """
    Splits the params between ()
    :param function_params: The params between ()
    :return:
    """
    tokens = str(function_params).split(",")
    tokens[-1] = tokens[-1][:-1]
    return tokens


def split_value_sign(functionality):
    """
    Splits the part after =
    :param functionality: The aprt after =
    :return: -
    """
    signs = []
    for element in functionality:
        if element == "+":
            signs.append("+")
        elif element == "-":
            signs.append("-")

    value_params = []
    value_params = re.split(r'\W+', functionality)
    return value_params, signs


def add_command_ui(list_functions, command_params):
    """
    Adds a new function to the list functions
    :param list_functions: List of funtions (list of dict)
    :param command_params: The definition of the function
    :return: -
    """
    function_def, functionality = split_function_def(command_params)
    function_name, function_params = split_function_name_params(function_def)
    for fun in list_functions:
        if fun["name"] == function_name:
            raise ValueError("There s already a function with that name. Please use another name")
    function_params = split_function_params(function_params)
    value_params, signs = split_value_sign(functionality)
    list_functions.append(create_function(function_name, function_params, value_params, signs))


def list_response(function):
    answer = "def " + str(function["name"]) + "("
    answer = answer + str(function["params"][0])
    for index in range(1, len(function["params"])):
        answer = answer + "," + function["params"][index]
    answer = answer + ")" + ":" + " return "
    if len(function["signs"]) == len(function["value_params"]):
        for index in range(0, len(function["signs"])):
            answer = answer + str(function["signs"]) + str(function["value_params"])
    else:
        answer = answer + str(function["value_params"][0])
        for index in range(1, len(function["value_params"])):
            answer = answer + str(function["signs"][index - 1]) + str(function["value_params"][index])
    return answer


def list_command_ui(list_functions, function_name):
    for function in list_functions:
        if function_name == function["name"]:
            print(list_response(function))
            return
    raise ValueError("Function wasn't found")


def split_eval_function(function):
    strings = str(function).lower().strip().split("(")
    function_name = strings[0]
    function_params = strings[1].split(",")
    function_params[-1] = function_params[-1][:-1]
    return function_name, function_params


def get_index_value_params(function, letter):
    ok = 0
    for index in range(0, len(function["params"])):
        if function["params"][index] == letter:
            return ok
        ok = ok + 1


def eval_function(list_functions, function):
    function_name, function_params = split_eval_function(function)
    sum = 0
    for fun in list_functions:
        if function_name == fun["name"]:
            if len(function_params) != len(fun["params"]):
                raise ValueError("Invalid number of params for the given function.")
            if len(fun["signs"]) == len(fun["value_params"]):
                ok = get_index_value_params(fun, fun["value_params"][0])
                sum = int(function_params[ok])
                for index in range(0, len(fun["signs"])):
                    ok = get_index_value_params(fun, fun["value_params"][index])
                    value = int(function_params[ok])
                    if fun["signs"][index] == "-":
                        value = -value
                        sum = sum + value
                    else:
                        sum = sum + value
            else:
                ok = get_index_value_params(fun, fun["value_params"][0])
                sum = int(function_params[ok])
                for index in range(1, len(fun["value_params"])):
                    ok = get_index_value_params(fun, fun["value_params"][index])
                    value = int(function_params[ok])
                    if fun["signs"][index - 1] == "-":
                        value = -value
                        sum = sum + value
                    else:
                        sum = sum + value

    return sum


def eval_command_ui(list_functions, function):
    print(eval_function(list_functions, function))


def ui():
    done = False
    list_functions = []

    command_dict = {"add": add_command_ui, "list": list_command_ui, "eval": eval_command_ui}

    while not done:
        try:
            command = read_command().strip()
            command_name, command_params = split_command(command)
            if command_name in command_dict:
                command_dict[command_name](list_functions, command_params)
            else:
                print("Bad command")
        except ValueError as msg:
            print(msg)


ui()
