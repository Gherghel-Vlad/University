#
# Implement the program to solve the problem statement from the first set here
#
# I did exercise 2 set 1, but because I am not fully sure I did it well enough, I will
# do exercise 3 set 1 as well.
"""
def slicing_number(n, list_numbers):
    ''' This function will create a list with all the digits from the number '''
    while n != 0:
        c = n % 10
        list_numbers.append(c)
        n = int( n / 10 )


def basic_sorting_algorithm(list_numbers):
    ''' This function will sort the list in an ascending order '''
    for i in range(0, len(list_numbers)):
        for j in range(i, len(list_numbers)):
            if list_numbers[i] > list_numbers[j]:
                aux = list_numbers[i]
                list_numbers[i] = list_numbers[j]
                list_numbers[j] = aux


def create_lowest_number(list_numbers):
    '''This function will return the lowest number that can be formed using the digits in the list given'''
    m = 0
    for i in range(0, len(list_numbers)):
        m = m * 10 + list_numbers[i]
    return m


# Main function
def main():
    list_numbers = []
    n = int(input("Please give a natural number: "))
    slicing_number(n, list_numbers)
    basic_sorting_algorithm(list_numbers)
    print("The lowest number created by using the digits from the given number is:", create_lowest_number(list_numbers))


main()
"""

# Exercise 2 from set 1

# Algorithm functions


def create_list_of_3(p1, p2, p3):
    """
    Creates a list with the parameters
    :param p1: First number of the list
    :param p2: Second number of the list
    :param p3: Third number of the lsit
    :return: A list that s created with all the given numbers
    """
    return [p1, p2, p3]


def prime(n):
    """This function will verify if the parameter given to it is a prime number.
     If it is, it returns True, if it is not, it returns False."""
    if n<=1:
        return False
    else:
        if n == 2:
            return True
        else:
            if n%2 == 0:
                return False
            else:
                for i in range(3, int(n**0.5)+1, 2):
                    if n % i == 0:
                        return False
    return True


def check_parity(x):
    """
    Checks the parity of a number
    :param x: The number that s going to be checked 
    :return: 0 for even, 1 for odd
    """
    return int(x%2)


def odd_number_case(n):
    """
    Resolves the odd case
    :param n: The number to be checked if it can be written as a sum of 2 prime numbers
    :return: Returns the answer for the odd case
    """
    if prime(n-2):
        return create_list_of_3(True, 2, n-2)
    return create_list_of_3(False, 0, 0)


def even_number_case(n):
    """
    Resolves the even case number
    :param n: The user's number
    :return: A list that consists of 3 numbers: first shows a boolean value that represents if it can be written or not, and the other 2 the numbers from the sum if it can
    """
    for i in range(3, int(n / 2 + 1), 2):
        p1 = i
        p2 = n - i
        if prime(p1) and prime(p2):
            return create_list_of_3(True, p1, p2)
    return create_list_of_3(False, 0, 0)


def main_algorithm(n):
    """
    Main function that resolves the exercise
    :param n: User's number
    :return:  A list that consists of 3 numbers: first a boolean one that tells if it can or not be written as one, and the rest the memebers of the sum
    """

    if check_parity(n):
        return odd_number_case(n)
    else:
        return even_number_case(n)


# UI functions


def print_result(list):
    """
    Shows the result
    :param list: The list that consists of the result
    :return:
    """
    if list[0]:
        print(str(list[1]+list[2]), "=", str(list[1]), "+", str(list[2]))
    else:
        print("It cant be written as a sum of 2 prime numbers")


def read_user_number():
    """
    Reads the user s data
    :return: Returns the user's input data
    """
    return int(input("Please write a natural number greater or equal than 4: "))


def main():
    # From my research i found you can't write an odd number as the sum of 2 prime numbers only if
    # one of the numbers is 2, but that makes numbers like 47 impossible to write as a sum of 2 prime
    # numbers because 45 isn't a prime number. And because 1 isn't a prime number, the first number
    # from which we can write them as a sum of 2 prime numbers is 4.

    """
    The main function
    """
    n = read_user_number()
    list = main_algorithm(n)
    print_result(list)

main()



