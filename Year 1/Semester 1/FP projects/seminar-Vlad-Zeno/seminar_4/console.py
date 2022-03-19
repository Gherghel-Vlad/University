from seminar_4.functions import *


def show_commands():
    print("1 Add circle")
    print("2 Generate n circles")
    print("3 Delete circles")
    print("4 Display circles")
    print("0 Exit")


def read_user_command():
    return input("Give command: ")


def read_circle():
    try:
        x = int(input("Give x: "))
        y = int(input("Give y: "))
        r = int(input("Give radius: "))
        return create_circle(x, y, r)
    except ValueError:
        raise ValueError("The coordinates and the radius must be integers")


def add_circle_ui(circles_list):
    add_circle(circles_list, read_circle())


def generate_n_circles_ui(circles_list):
    try:
        n = int(input("Give n: "))
        create_n_random_circles(circles_list, n)
    except ValueError:
        raise ValueError("Give an integer next time")


def delete_circles_ui(circles_list):
    if len(circles_list) == 0:
        raise ValueError("There are no circles to be deleted")
    delete_circles_in_circle(circles_list, read_circle())


def display_all_circles(circles_list):
    new_list = sort_list(circles_list)

    for circle in new_list:
        print(to_str(circle))


def start():
    done = False
    circles_list = []
    commands_dict = {"1": add_circle_ui, "2": generate_n_circles_ui, "3": delete_circles_ui, "4": display_all_circles}

    while not done:
        try:
            show_commands()
            command = read_user_command()

            if command == "0":
                done = True
            elif command in commands_dict:
                commands_dict[command](circles_list)
            else:
                print("Wrong command")
        except ValueError as val:
            print(val)


start()





















