import copy
import math


def gcd_divide_iterative(list):
    """
    Calculates the gcd of a list of numbers in an iterative way
    :return: The gcd of the numbers in the list
    """
    list_of_numbers = list
    new_list = []

    while len(list_of_numbers) != 1:
        # i will divide the original list in pairs of 2 numbers, create a new list with them, and then apply that alg
        # on the new list created
        nr_of_iterations = len(list_of_numbers) // 2

        for index in range(0, nr_of_iterations):
            new_list.append(math.gcd(list_of_numbers[2 * index], list_of_numbers[2 * index + 1]))

        if len(list_of_numbers) % 2 == 1:
            new_list.append(list_of_numbers[-1])

        list_of_numbers = copy.deepcopy(new_list)
        new_list = []

    return list_of_numbers[0]


def test_gcd_function():
    assert gcd_divide_iterative([4, 16, 32, 100, 64]) == 4
    assert gcd_divide_iterative([4, 16, 32, 100, 13]) == 1
    assert gcd_divide_iterative([4, 16, 2, 100, 64]) == 2
    assert gcd_divide_iterative([11]) == 11


test_gcd_function()


def product_divide_recursive(list, ok):

    # stuck on the fact that if there was only a list of 1 element, it wouldnt return 0, it would return 1
    # ideea: the slicing is done with variables on the whole list, instead of slicing the list and working
    # on that sliced list
    if len(list) == 0:
        return 1
    if len(list) == 1:
        if list[0] % 2 == 0:
            return list[0]
        else:
            return 1

    mid = len(list) // 2


    if len(list) % 2 == 1:
        product = product_divide_recursive(list[:mid+1], 0) * product_divide_recursive(list[mid+2:], 0)
    else:
        product = product_divide_recursive(list[:mid], 0) * product_divide_recursive(list[mid+1:], 0)

    if ok == 1 and product % 2 == 1:
        return 0
    else:
        return product


def test_product_divide_recursive():
    assert product_divide_recursive([2, 4, 6, 7, 8, 9, 10]) == 960
    assert product_divide_recursive([11, 13, 17, 23]) == 1
    assert product_divide_recursive([2, 4, 6, 7, 8, 9, 10]) == 960


print(product_divide_recursive([11, 13, 2, 24, 2], 1))
