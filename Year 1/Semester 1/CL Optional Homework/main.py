from Domain.number import Number
from Operations.operations import validate_input_number, addition_in_base, multiplication_by_one_digit, \
    subtraction_in_base, division_by_one_digit, successive_divisions, converting_using_base_10, rapid_conversion, \
    substitution_method


def read_command():
    return input("Give command: ").strip()


def addition_in_base_ui():
    base = input("Terms's base: ").strip().lower()
    number_1 = input("First term: ").strip().lower()
    number1 = Number(number_1, int(base))
    validate_input_number(number1)
    number_2 = input("Second term: ").strip().lower()
    number2 = Number(number_2, int(base))
    validate_input_number(number2)

    result_number = addition_in_base(number1, number2)
    print(f"The sum: {result_number.number.lstrip('0')} in base {result_number.base}\n")


def multiplication_by_one_digit_ui():
    base = input("First factor's base: ").strip().lower()
    number_1 = input("First factor: ").strip().lower()
    number1 = Number(number_1, int(base))
    validate_input_number(number1)
    number_2 = input("Digit to multiply with: ").strip().lower()
    if len(number_2) != 1:
        raise ValueError("Second factor has to be a digit.")
    number2 = Number(number_2, int(base))
    validate_input_number(number2)
    result_number = multiplication_by_one_digit(number1, number2)

    print(f"Product: {result_number.number.lstrip('0')} in base {result_number.base}\n")


def division_by_one_digit_ui():
    base = input("Dividend's base: ").strip().lower()
    number_1 = input("Dividend: ").strip().lower()
    number1 = Number(number_1, int(base))
    validate_input_number(number1)
    number_2 = input("Divisor (digit): ").strip().lower()
    if len(number_2) != 1:
        raise ValueError("Divisor needs to be a digit.")
    number2 = Number(number_2, int(base))
    validate_input_number(number2)
    list_numbers = division_by_one_digit(number1, number2)

    print(f"Quotient: {list_numbers[0].number.lstrip('0')} Remainder: {list_numbers[1].number}\n")


def subtraction_in_base_ui():
    base = input("Numbers's base: ").strip().lower()
    number_1 = input("First number: ").strip().lower()
    number1 = Number(number_1, int(base))
    validate_input_number(number1)
    number_2 = input("Second number: ").strip().lower()
    number2 = Number(number_2, int(base))
    validate_input_number(number2)
    result_number = subtraction_in_base(number1, number2)

    print(f"Difference: {result_number.number.lstrip('0')} in base {result_number.base}\n")


def successive_divisions_ui():
    base = input("Number's base: ").strip().lower()
    number_1 = input("Value to be converted: ").strip().lower()
    number1 = Number(number_1, int(base))
    validate_input_number(number1)
    to_base = input("The base in which to be transformed into: ").strip().lower()
    if to_base not in ['2', '3', '4', '5', '6', '7', '8', '9', '10', '16']:
        raise ValueError("Base can be only between these values {2,3,...,9,10,16}")
    to_base = int(to_base)
    result_number = successive_divisions(number1, to_base)
    print(f"Converted value: {result_number.number.lstrip('0')} in base {result_number.base}\n")


def converting_using_base_10_ui():
    base = input("Number's base: ").strip().lower()
    number_1 = input("Value to be converted: ").strip().lower()
    number1 = Number(number_1, int(base))
    validate_input_number(number1)
    to_base = input("The base in which to be transformed into: ").strip().lower()
    if to_base not in ['2', '3', '4', '5', '6', '7', '8', '9', '10', '16']:
        raise ValueError("Base can be only between these values {2,3,...,9,10,16}")
    to_base = int(to_base)
    result_number = converting_using_base_10(number1, to_base)
    print(f"Converted value: {result_number.number.lstrip('0')} in base {result_number.base}\n")


def substitution_method_ui():
    base = input("Number's base: ").strip().lower()
    number_1 = input("Value to be converted: ").strip().lower()
    number1 = Number(number_1, int(base))
    validate_input_number(number1)
    to_base = input("The base in which to be transformed into: ").strip().lower()
    if to_base not in ['2', '3', '4', '5', '6', '7', '8', '9', '10', '16']:
        raise ValueError("Base can be only between these values {2,3,...,9,10,16}")
    to_base = int(to_base)
    result_number = substitution_method(number1, to_base)
    print(f"Converted value: {result_number.number.lstrip('0')} in base {result_number.base}\n")


def rapid_conversion_ui():
    base = input("Number's base: ").strip().lower()
    if base not in ['2', '8', '4', '16']:
        raise ValueError("Source base has to be from {2, 4, 8, 16}")

    number_1 = input("Value to be converted: ").strip().lower()
    number1 = Number(number_1, int(base))
    validate_input_number(number1)
    to_base = input("The base in which to be transformed into: ").strip().lower()
    if to_base not in ['2', '8', '4', '16']:
        raise ValueError("Destination base has to be from {2, 4, 8, 16}")
    to_base = int(to_base)
    result_number = rapid_conversion(number1, to_base)
    print(f"Converted value: {result_number.number.lstrip('0')} in base {result_number.base}\n")


def print_menu():
    print("1. Addition of two numbers in a base")
    print("2. Multiplication of a number by a digit in a base")
    print("3. Division of a number by a digit in a base")
    print("4. Subtraction of two numbers in a base")
    print("5. Algorithm for the method of successive divisions")
    print("6. Algorithm for conversion using 10 as an intermediate base")
    print("7. Algorithm for the substitution method")
    print("8. Rapid conversions between two bases from {2, 4, 8, 16}")
    print("0. Exit\n")


def menu():
    command_list = {"1": addition_in_base_ui, "2": multiplication_by_one_digit_ui,
                    "3": division_by_one_digit_ui, "4": subtraction_in_base_ui,
                    "5": successive_divisions_ui, "6": converting_using_base_10_ui,
                    "7": substitution_method_ui, "8": rapid_conversion_ui}

    done = False

    while not done:
        try:
            print_menu()
            command = read_command()

            if command == "0":
                done = True
            elif command in command_list:
                command_list[command]()
            else:
                print("Bad command. Try again please.")
        except Exception as e:
            print(e)


menu()
