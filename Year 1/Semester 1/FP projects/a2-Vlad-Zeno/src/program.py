#
# Write the implementation for A2 in this file
#


# Function section
# (write all non-UI functions in this section)
# There should be no print or input statements below this comment
# Each function should do one thing only
# Functions communicate using input parameters and their return values

# print('Hello A2'!) -> prints aren't allowed here!


# Complex number functions

def create_complex_number(real, imag):
    """
    Creates a complex number
    :param real: The real part of the number
    :param imag: The imaginary part of the function
    :return: A complex number formed with the given params
    """
    return {"real": real, "imag": imag}


def get_real_part(complex_number):
    """
    Returns the real part of the complex number
    :param complex_number: The complex number
    :return: The real part of the complex number
    """
    return complex_number["real"]


def get_imag_part(complex_number):
    """
    Returns the imaginary part of the complex number
    :param complex_number: The complex number
    :return: The imaginary part of the complex number
    """
    return complex_number["imag"]


def set_real_part(complex_number, new_real):
    """
    Sets a new real part of the complex number
    :param complex_number: The complex number
    :param real: The new real part
    :return: -
    """
    complex_number["real"] = new_real


def set_imag_part(complex_number, new_imag):
    """
    Sets a new imaginary part for the complex number
    :param complex_number: The complex number
    :param imag: The new imaginary part
    :return: -
    """
    complex_number["imag"] = new_imag


def to_str(complex_number):
    """
    Writes a complex number in a nice format
    :param complex_number: The complex number that needs to be written in a nice format
    :return: A string that represents the complex number written in a nice format (z=a+bi)
    """
    return "z = " + str(get_real_part(complex_number)).rjust(2) + " + " + str(get_imag_part(complex_number)).rjust(2) + "i"


def calculate_modulus(complex_number):
    """
    Calculates the modulus of a complex number
    :param complex_number: The complex number
    :return: The modulus
    """
    return (get_real_part(complex_number)**2 + get_imag_part(complex_number)**2) ** 0.5


def add_real_parts(complex_number_1, complex_number_2):
    """
    Adds the real part of 2 complex numbers and returns it
    :param complex_number_1: First complex number
    :param complex_number_2: Second complex number
    :return: A number that represents the sum of the real parts of the complex numbers
    """
    return get_real_part(complex_number_1) + get_real_part(complex_number_2)


def add_imaginary_parts(complex_number_1, complex_number_2):
    """
    Adds the imaginary part of 2 complex numbers and returns it
    :param complex_number_1: First complex number
    :param complex_number_2: Second complex number
    :return: A number that represents the sum of the imaginary parts of the complex numbers
    """
    return get_imag_part(complex_number_1) + get_imag_part(complex_number_2)


def add_2_complex_numbers(complex_number_1, complex_number_2):
    """
    Adds 2 complex numbers
    :param complex_number_1: First one
    :param complex_number_2: Second one
    :return: A complex number that is the sum of the other 2
    """
    return create_complex_number(add_real_parts(complex_number_1, complex_number_2), add_imaginary_parts(complex_number_1, complex_number_2))


def compare_2_complex_numbers(complex_number_1, complex_number_2):
    """
    Compares 2 complex numbers
    :param complex_number_1:
    :param complex_number_2:
    :return: True if they are equal, False if not
    """
    if get_real_part(complex_number_1) == get_real_part(complex_number_2) and get_imag_part(complex_number_1) == get_imag_part(complex_number_2):
        return True
    return False

# Property 4 Functions


def answer_1_algorithm(complex_number_list):
    """
    Resolves property 4: Numbers having increasing modulus returning a lsit containing the longest
    sequence that has all the elements in an increasing modulus
    :param complex_number_list: The complex number list that it s working on (list of dictionaries)
    :return: A new list containing the longest sequence of the given property (list of dictionaries)
    """
    # we create 2 empty lists
    current_list = []
    answer_list = []

    # we begin the algorithm from the first
    if len(complex_number_list) >= 1:
        current_list.append(complex_number_list[0])

    for index in range(1, len(complex_number_list)):
        # we check if the modulus are doing what we need for the 2 consecutive complex numbers
        if calculate_modulus(complex_number_list[index]) >= calculate_modulus(complex_number_list[index-1]):
            current_list.append(complex_number_list[index])
        else:
            # if not we see if it s a better result than what we have already
            if len(current_list) > len(answer_list):
                answer_list = current_list
            # we create a new list starting from a new modulus
            current_list = [complex_number_list[index]]

    # we check one last time because the else part from above might not be reached if the last element is okay
    if len(current_list) > len(answer_list):
        answer_list = current_list

    return answer_list


# Property 9 Functions

def starting_from_the_first(complex_number_list):
    """
    Solves the case in which we make pairs from the first element
    :param complex_number_list: -
    :return: A list that contains the maximum elements of the sequence asked for
    """
    # we create 2 empty lists
    current_list = []
    answer_list = []

    # we start from the first pair
    current_list.append(complex_number_list[0])
    current_list.append(complex_number_list[1])

    for index in range(2, len(complex_number_list), 2):
        # we check that there are 2 elements remaining so that we can create the next pair
        if len(complex_number_list) - 1 - index >= 2:
            # we see if the next pair has the same sum as the last pair
            if compare_2_complex_numbers(add_2_complex_numbers(current_list[-1], current_list[-2]),
                                         add_2_complex_numbers(complex_number_list[index], complex_number_list[index+1])):
                current_list.append(complex_number_list[index])
                current_list.append(complex_number_list[index+1])
            else:
                # if not we see if the result is what we need and
                # create another list that starts from the pair that has the different sum
                if len(answer_list) < len(current_list):
                    answer_list = current_list
                current_list = [complex_number_list[index], complex_number_list[index + 1]]

    # we check one last time (because the else part might not be reached if the last pair is correct
    if len(answer_list) < len(current_list):
        answer_list = current_list

    return answer_list


def starting_from_the_second(complex_number_list):
    """
    Solves the case in which we make pairs from the second element
    :param complex_number_list: -
    :return: A list that contains the maximum elements of the sequence asked for
    """
    # we create 2 empty lists
    current_list = []
    answer_list = []

    # we start from the first pair
    current_list.append(complex_number_list[1])
    current_list.append(complex_number_list[2])

    for index in range(3, len(complex_number_list), 2):
        # we check that there are 2 elements remaining so that we can create the next pair
        if len(complex_number_list) - 1 - index >= 1:
            # we see if the next pair has the same sum as the last pair
            if compare_2_complex_numbers(add_2_complex_numbers(current_list[-1], current_list[-2]),
                                         add_2_complex_numbers(complex_number_list[index],
                                                               complex_number_list[index + 1])):
                current_list.append(complex_number_list[index])
                current_list.append(complex_number_list[index + 1])
            else:
                # if not we see if the result is what we need and
                # create another list that starts from the pair that has the different sum
                if len(answer_list) < len(current_list):
                    answer_list = current_list
                current_list = [complex_number_list[index], complex_number_list[index + 1]]

    # we check one last time (because the else part might not be reached if the last pair is correct
    if len(answer_list) < len(current_list):
        answer_list = current_list

    return answer_list


def answer_2_algorithm(complex_number_list):
    """
    Resolves the property 9
    :param complex_number_list: The complex number list
    :return: A list that contains the answer for property 9
    Raise ValueError if list is too short (<4 elements)
    """

    first_answer = []
    second_answer = []
    answer_list = []

    if len(complex_number_list)<4:
        raise ValueError("The list needs to have at least 4 elements")

    first_answer = starting_from_the_first(complex_number_list)

    second_answer = starting_from_the_second(complex_number_list)

    if len(first_answer) < len(second_answer):
        answer_list = second_answer
    else:
        answer_list = first_answer

    return answer_list


# UI section
# (write all functions that have input or print statements here).
# Ideally, this section should not contain any calculations relevant to program functionalities


def show_menu():
    """
    Shows the menu to the user
    :return: -
    """
    print("1. Read complex number.")
    print("2. Show all complex numbers.")
    print("3. Numbers having increasing modulus.")
    print("4. Consecutive number pairs have equal sum.")
    print("0. Exit.")


def show_complex_numbers_ui(complex_number_list):
    """
    Shows all the complex numbers
    :param complex_number_list: The complex number list
    :return: -
    """
    for complex_number in complex_number_list:
        print(to_str(complex_number))


def show_answer_1_ui(complex_number_list):
    """
    Resolves the ui part for property 4: Numbers having increasing modulus
    :param complex_number_list: The complex number list
    :return: -
    """
    answer_list = answer_1_algorithm(complex_number_list)

    # for complex_number in answer_list:
    #    print(to_str(complex_number))

    show_complex_numbers_ui(answer_list)


def show_answer_2_ui(complex_number_list):
    """
    Resolves the ui part for property 9: Consecutive number pairs have equal sum. (e.g. 1+3i, 1-i, 1+3i, 1-i)
    :param complex_number_list: The complex number list
    :return: -
    """
    answer_list = answer_2_algorithm(complex_number_list)

    show_complex_numbers_ui(answer_list)


def read_complex_number_ui(complex_number_list):
    """
    Reads a complex number and adds it to the complex number list
    :param complex_number_list: The complex number list
    :return: -
    """
    real = float(input("Real part: "))
    imag = float(input("Imaginary part: "))
    complex_number_list.append(create_complex_number(real, imag))


def add_complex_numbers(complex_numbers_list):
    """
    Adds data in the complex number list
    :param complex_numbers_list: The complex number list
    :return: -
    """

    complex_numbers_list.append(create_complex_number( 8,  9))
    complex_numbers_list.append(create_complex_number( 4,  5))
    complex_numbers_list.append(create_complex_number( 6,  7))
    complex_numbers_list.append(create_complex_number( 6,  7))
    complex_numbers_list.append(create_complex_number( 1,  2))
    complex_numbers_list.append(create_complex_number (1,  3))
    complex_numbers_list.append(create_complex_number( 1, -1))
    complex_numbers_list.append(create_complex_number( 1,  3))
    complex_numbers_list.append(create_complex_number( 1, -1))
    complex_numbers_list.append(create_complex_number( 1,  3))
    '''
    complex_numbers_list.append(create_complex_number( 8,  9))
    complex_numbers_list.append(create_complex_number( 4,  5))
    complex_numbers_list.append(create_complex_number( 8,  7))
    complex_numbers_list.append(create_complex_number( 6,  7))
    complex_numbers_list.append(create_complex_number( 1,  2))
    complex_numbers_list.append(create_complex_number (5,  3))
    complex_numbers_list.append(create_complex_number( 1, -1))
    complex_numbers_list.append(create_complex_number( 7,  3))
    complex_numbers_list.append(create_complex_number( 1, -1))
    complex_numbers_list.append(create_complex_number( 9,  3))
    '''

def start():
    """
    The main UI function
    :return: -
    """

    complex_number_list = []
    add_complex_numbers(complex_number_list)

    commands = {"1": read_complex_number_ui, "2": show_complex_numbers_ui, "3": show_answer_1_ui, "4": show_answer_2_ui}

    done = False

    while not done:
        show_menu()

        command = input("Write command number: ")

        try:

            if command == '0':
                done = True
            elif command in commands:
                commands[command](complex_number_list)
            else:
                print("Careful, you wrote a bad command")
        except ValueError as ve:
            print("Oh oh, a problem occurred: " + str(ve))


# start()


def complexity_1(x):
    m = len(x)
    found = False
    while m >= 1:
        c = m -m / 3* 3
        if c == 1:
            found = True
        m = m / 3

complexity_1([1, 2, 3, 4, 5, 6, 7, 8])











