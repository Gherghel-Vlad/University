def is_prime(x):
    """
    Checks if a number is prime or not
    :param x: The number to be checked (int)
    :return: True if it is, else if it isn't
    """
    for i in range(2, x):
        if x % i == 0:
            return False
    return True


def divide_and_conquer(list):
    """
    Finds the biggest prime number on an even position
    :param list: The list that s going to work on (list)
    :return: The biggest prime number on an even position (int), None if it didn't find
    """
    if len(list) == 0:
        return None

    if len(list) == 1 or len(list) == 2:
        if is_prime(list[0]):
            return list[0]
        else:
            return None

    nr_to_compare = divide_and_conquer(list[2:])

    if nr_to_compare is not None:
        if is_prime(list[0]):
            return max(list[0], nr_to_compare)
        else:
            return nr_to_compare
    else:
        if is_prime(list[0]):
            return list[0]
        else:
            return None


def test_is_prime():
    assert is_prime(11) is True
    assert is_prime(17) is True
    assert is_prime(24) is False
    assert is_prime(2) is True
    assert is_prime(100) is False


def test_divide_and_conquer():
    assert divide_and_conquer([5, 6, 7, 8, 9, 10, 4, 12, 13, 14, 15, 16, 17, 25, 19]) == 19
    assert divide_and_conquer([21, 3, 50]) is None
    assert divide_and_conquer([]) is None
    assert divide_and_conquer([2, 3, 4, 6, 8, 10, 16]) == 2
    assert divide_and_conquer([2, 5, 11]) == 11
    assert divide_and_conquer([10, 20, 30, 40, 50, 60, 70, 80, 100, 10000, 100002]) is None

test_divide_and_conquer()
test_is_prime()
