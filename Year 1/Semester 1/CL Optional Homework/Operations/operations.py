import math

from Domain.number import Number


def convert_to_base_10(number):
    """
    This function returns the number converted into base 10
    :param number: An instance of the number object
    :return: An number instance representing the converted number in base 10 and base 10
    """
    list_for_base_16 = ['a', 'b', 'c', 'd', 'e', 'f']
    x = number.number
    p = 0
    result = 0
    x = str(x).strip()
    while x != "":
        c = x[-1]
        if str(c).lower() in list_for_base_16:
            result += (list_for_base_16.index(str(c).lower()) + 10) * (int(number.base) ** p)
        else:
            result += int(c) * (int(number.base) ** p)
        p += 1
        x = x[:-1]
    return Number(result, 10)


def validate_input_number(number):
    """
    Validates the input number
    :param number: The number object to be verified
    raises ValueError if something is wrong
    """
    list_number = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']
    if number.base not in [2, 3, 4, 5, 6, 7, 8, 9, 10, 16]:
        raise ValueError("Base can be only between these values {2,3,...,9,10,16}")

    # i am going to verify if a number is correct in regards with the base
    # there cant be any digits higher than the base

    nr = number.number
    i = 0
    while i < len(nr):
        if nr[i] not in list_number:
            raise ValueError("Number written incorrectly.")
        if int(convert_to_base_10(Number(nr[i], number.base)).number) >= number.base:
            raise ValueError("The number is incorrect in the given base")
        i += 1


def addition_in_base(number1, number2):
    """
    This function calculates the sum of the 2 numbers that are in the same base
    :param number1: First instance of an number
    :param number2: Second instance of an number
    :return: A new number object containing the result of the sum
    """
    # calculating the max length
    n = len(number1.number) if len(number1.number) > len(number2.number) else len(number2.number)
    # list that i will use to convert from base 10 to the base
    list_number = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']
    # reversing the strings
    number_1 = number1.number[::-1]
    number_2 = number2.number[::-1]
    base = number1.base

    result_in_base_10 = 0
    result_string = ""
    c = 0
    for i in range(0, n):
        # taking the digits that i need to add and converting them to base 10
        # i check first that i have digits left to add
        if i < len(number_1):
            digit_1 = int(convert_to_base_10(Number(number_1[i], base)).number)
        else:
            digit_1 = 0
        if i < len(number_2):
            digit_2 = int(convert_to_base_10(Number(number_2[i], base)).number)
        else:
            digit_2 = 0

        result_in_base_10 = digit_1 + digit_2 + c

        result_string += list_number[result_in_base_10 % base]
        c = result_in_base_10 // base
    # if there s a carry left, add it to the end
    if c != 0:
        result_string += str(c)

    return Number(result_string[::-1], base)


def multiplication_by_one_digit(number1, number2):
    """
    Calculates the multiplication of a number by another digit (from number2)
    :param number1: The first number object
    :param number2: The second number object that is the digit by which is multiplied
    :return: A number instance that has the result and the base in which the result is in
    """
    # calculating the max length
    n = len(number1.number) if len(number1.number) > len(number2.number) else len(number2.number)
    # list that i will use to convert from base 10 to the base
    list_number = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']
    # reversing the strings
    number_1 = number1.number[::-1]
    number_2 = number2.number[::-1]
    base = number1.base

    result_in_base_10 = 0
    result_string = ""
    # this will be the digit with whom i will multiply number1
    digit_to_multiply_with = int(convert_to_base_10(Number(number_2[0], base)).number)
    c = 0
    for i in range(0, n):
        # taking the digit from the first number in order
        digit_1 = int(convert_to_base_10(Number(number_1[i], base)).number)

        # calculating the result of the multiplication
        result_in_base_10 = digit_1 * digit_to_multiply_with + c

        # calculating the string result
        result_string += list_number[result_in_base_10 % base]
        # calculating the carry
        c = result_in_base_10 // base
    # if there s a carry left, add it to the end
    if c != 0:
        result_string += str(list_number[c])

    return Number(result_string[::-1], base)


def division_by_one_digit(number1, number2):
    """
    Calculates the division of number1 by the number from number2
    :param number1: The first number object
    :param nubmer2: The second number object that has the digit for the division
    :return: A string representing the result and the remainder
    """
    # setting the length
    n = len(number1.number)
    # list that i will use to convert from base 10 to the base
    list_number = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']
    # making referencing easier
    number_1 = number1.number
    number_2 = number2.number
    base = number1.base

    result_in_base_10 = 0
    result_string = ""
    # this will be the digit with whom i will division number1
    # when number_2 is 10, the way cahnges
    if number_2 == '10':
        digit_to_divide_with = int(convert_to_base_10(Number(list_number[int(number_2)], base)).number)
    else:
        digit_to_divide_with = int(convert_to_base_10(Number(number_2, base)).number)

    r = 0
    for i in range(0, n):
        # taking the digit from the first number in order
        digit_1 = int(convert_to_base_10(Number(number_1[i], base)).number)

        # calculating the result of the multiplication
        result_in_base_10 = r * base + digit_1

        # calculating the string result (calculating and converting already to the base in which i am)
        result_string += list_number[result_in_base_10 // digit_to_divide_with]
        # calculating the remainder
        r = result_in_base_10 % digit_to_divide_with

    r_in_base = list_number[r]
    return [Number(str(result_string), base), Number(str(r_in_base), base)]


def subtraction_in_base(number1, number2):
    """
    Calculates the difference between 2 numbers
    :param number1: The first number object (minuend)
    :param number2: The second number object (subtrahend)
    :return: Returns a number obejct representing the difference and the base in which is written
    """
    # calculating the max length
    n = len(number1.number) if len(number1.number) > len(number2.number) else len(number2.number)

    # Checking if number1 is bigger than number2, and if not, swap them and the result will be with -
    ok = 0
    if int(convert_to_base_10(number1).number) < int(convert_to_base_10(number2).number):
        aux = number1
        number1 = number2
        number2 = aux
        ok = 1

    # list that i will use to convert from base 10 to the base
    list_number = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']
    # reversing the strings
    number_1 = number1.number[::-1]
    number_2 = number2.number[::-1]
    base = number1.base

    result_in_base_10 = 0
    result_string = ""
    c = 0
    for i in range(0, n):
        # taking the digits that i need to add and converting them to base 10
        # i check first that i have digits left to add
        if i < len(number_1):
            digit_1 = int(convert_to_base_10(Number(number_1[i], base)).number)
        else:
            digit_1 = 0
        if i < len(number_2):
            digit_2 = int(convert_to_base_10(Number(number_2[i], base)).number)
        else:
            digit_2 = 0

        # Calculating the result in base 10
        result_in_base_10 = digit_1 - digit_2 - c

        c = 0

        # Checks if there needs to be a borrowed unit
        if result_in_base_10 < 0:
            result_in_base_10 += base
            c = 1

        # creating the end result in string format
        result_string += list_number[result_in_base_10 % base]

    # Checking if the number was swapped or not (so that i know if the number will be shown with - or not)
    if ok == 0:
        return Number(result_string[::-1], base)
    else:
        return Number("-" + result_string[::-1], base)


def successive_divisions(number, base):
    """
    The process of successive divisions ends when 0 is obtained as quotient.
    The remainders, in the reverse order, are the digits of the new representation in base.
    :param number: Number object representing the number to be converted
    :param base: The base in which i convert it into
    :return: A nubmer representing the converted number in the given base
    """
    list_remainders = []
    nr = number.number
    nr_base = number.base
    list_convert = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']
    while nr.strip('0') != "":
        # Calculating the first division (converting the base in the right base as well)
        if number.base < base:
            list_numbers = division_by_one_digit(Number(str(nr), nr_base),
                                                 successive_divisions(Number(base, 10), nr_base))
        else:
            list_numbers = division_by_one_digit(Number(str(nr), nr_base), Number(base, nr_base))
        # Saving the remainder that i got from the division
        list_remainders.append(list_numbers[1].number)
        # setting the last remainder to know if the algorithm continues
        # updating for the next division
        nr = list_numbers[0].number
        nr_base = list_numbers[0].base

    string = (''.join(list_remainders))[::-1]

    return Number(string if string != "" else '0', base)


def converting_using_base_10(number, base):
    """
    This algorithm converses a number from its base to base 10, and then from base 10 to the destination base
    :return: A number object representing the number in the destination base
    """
    return successive_divisions(convert_to_base_10(number), base)


def substitution_method(number, base):
    """
    This function converts the given number from its base to the given base
    :param number: An instance of the number class that's going to be converted
    :param base: The destination base (int)
    :return: A number instance that represents the converted number and the current base
    raises ValueError if the number's base is greater than the destination base
    """
    if number.base > base:
        raise ValueError("Source base has to be lower than the destination base.")

    # i inverse my string number so i can start from the beginning
    number_reversed = number.number[::-1]
    # this will be my multiplier that will increase with each digit the number has
    c = Number('1', base)
    result = Number('0', base)

    for i in range(0, len(number_reversed)):
        # I add here to my result the current digit multiplied with it's own positional multiplier
        result = addition_in_base(result, multiplication_by_one_digit(c, Number(number_reversed[i], base)))
        # Increase the multiplier
        c = multiplication_by_one_digit(c, Number(number.base, base))


    return result


def rapid_conversion(number, base):
    """
    Converts the given number in the current base to the destination base using rapid conversion method
    :param number: An instance of a number representing the number to be converted and it s base {2, 4, 8, 16}
    :param base: The base in which to convert into {2, 4, 8, 16}
    :return: A Number object representing the number converted in the destination base and its base
    """
    # I have 3 cases: one in which I convert from base 2 into another base
    # Another one in which i convert into base 2
    # and the last one in which i can convert my number into base 2 from its current base, and then convert it to the
    # actual destination base
    if number.base == 2:

        # The number of digits a group has
        size_of_groups = int(math.log2(base))

        # I calculate how many zeroes i have to add so i can divide it in into exact chunks
        if len(number.number) % size_of_groups != 0:
            nr_of_extra_zeroes = size_of_groups - len(number.number) % size_of_groups
            while nr_of_extra_zeroes > 0:
                number.number = "0" + number.number
                nr_of_extra_zeroes -= 1
        # i divide it into exact chunks, chunks being a list of them
        chunks = [number.number[i:i + size_of_groups] for i in range(0, len(number.number), size_of_groups)]

        # i calculate each chunks conversion and add it to the result
        result_number = ""

        for chunk in chunks:
            # i use substitution so i dont use a big array representing the correspondence table
            result_number += substitution_method(Number(chunk, 2), base).number

        return Number(result_number, base)
    elif base == 2:

        # The number of digits a group has
        size_of_groups = int(math.log2(number.base))

        result_number = ""
        # for each digit i calculate its representation in base 2, and if there arent enough digits to form a gull group
        # i add 0 to it
        for digit in number.number:
            aux = successive_divisions(Number(digit, number.base), 2).number
            while len(aux) < size_of_groups:
                aux = '0' + aux
            result_number += aux

        return Number(result_number, base)
    else:
        return rapid_conversion(rapid_conversion(number, 2), base)

# print(str(rapid_conversion(Number("101011010111", 2), 16)))
# print(str(rapid_conversion(Number("ad7", 16), 2)))
# print(str(rapid_conversion(Number("5327", 8), 2)))
# print(str(rapid_conversion(Number("5327", 8), 16)))
# print(successive_divisions(Number("1536", 16), 10))
# print(successive_divisions(Number("1536", 7), 10))
# print(successive_divisions(Number("1536", 7), 6))
# print(successive_divisions(Number("1536", 7), 8))
# print(successive_divisions(Number("1536", 7), 16))
# print(successive_divisions(Number("267", 16), 7))
# print("\n")
# print(conversing_using_base_10(Number("1536", 16), 10))
# print(conversing_using_base_10(Number("1536", 7), 10))
# print(conversing_using_base_10(Number("1536", 7), 6))
# print(conversing_using_base_10(Number("1536", 7), 8))
# print(conversing_using_base_10(Number("1536", 7), 16))
# print(conversing_using_base_10(Number("267", 16), 7))
#
# print("\n")
#
# print(substitution_method(Number("1536", 7), 10))
# print(substitution_method(Number("1536", 7), 2))
# print(substitution_method(Number("1536", 7), 8))
# print(substitution_method(Number("1536", 7), 16))

#
# list = division_by_one_digit(Number("ABCD", 16), Number("a", 16))
# for e in list:
#     print(str(e))
#
# list = division_by_one_digit(Number("5674", 16), Number("a", 16))
# for e in list:
#     print(str(e))
