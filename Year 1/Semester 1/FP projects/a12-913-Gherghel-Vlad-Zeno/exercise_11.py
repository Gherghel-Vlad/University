# Two natural numbers m and n are given. Display in all possible modalities the numbers from 1 to n,
# such that between any two numbers on consecutive positions, the difference in absolute value is at least
# m. If there is no solution, display a message.


def start():
    m = input("m= ").strip()
    n = input("n= ").strip()

    # backtracking iterative
    ok = [0]
    backtracking_iterative([], int(n), int(m), ok)
    # backtracking_recursive([], int(n), int(m), ok)
    if ok[-1] == 0:
        print("No solution")


def afis(result_list):
    string = ""
    for elem in result_list:
        string = string + str(elem) + " "
    print(string)
    print("\n")


def correct(result_list, m):
    if len(result_list) == 1:
        return True
    if abs(result_list[-1] - result_list[-2]) < m:
        return False
    for elem in result_list[:-1]:
        if elem == result_list[-1]:
            return False
    return True


def backtracking_recursive(result_list, n, m, ok):
    if len(result_list) == n:
        afis(result_list[:])
        ok[-1] = 1
        return
    result_list.append(0)
    for i in range(1, n + 1):
        result_list[-1] = i
        if correct(result_list[:], m):
            backtracking_recursive(result_list[:], n, m, ok)


def can_add_number(result_list, i, m, pos):
    # checks if i can add that number to the list
    if pos == 0:
        return True
    for elem in result_list:
        if elem == i:
            return False
    if abs(i - result_list[pos - 1]) < m:
        return False
    return True


def work_solution(result_list):
    string = ""
    for elem in result_list:
        string = string + str(elem) + " "
    print(string)
    print("\n")


def backtracking_iterative(result_list, n, m, ok):
    """
    Creates the list and prints it on the screen
    :param result_list: The stack
    :param n: The length of the list and what values it can get [1, n]
    :param m: The minimum difference between 2 consecutive numbers
    :param ok: Checks if at least one solution was found
    :return:
    """
    value_list = [0 for i in range(n)]  # creating the space for the numbers
    pos = 0  # position to show me where i need to put/check the number
    result_list = [0 for i in range(n)]  # creating the space for the numbers
    while pos >= 0:
        for i in range(value_list[pos] + 1, n + 2):
            if can_add_number(result_list[:-(n-pos)], i, m, pos) and i != n+1:
                result_list[pos] = i
                break

        value_list[pos] = i  # saving so i know where to start next when i am done
        if value_list[pos] != result_list[pos]:
            pos -=1
            continue
        elif pos+1 == n:
            ok[0] = 1
            work_solution(result_list[:])
            continue
        else:
            # going to the next value
            pos += 1
            value_list[pos] = 0
            continue


start()
