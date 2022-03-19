import copy

from seminar_4.circle import create_circle, create_random_circle, get_x, get_y, get_r, calculate_distance_to_second_diagonal, to_str, interchange_2_circles_in_a_list


def add_circle(circles_list, circle):
    circles_list.append(circle)


def create_n_random_circles(circles_list, n):
    for index in range(0, n):
        circle = create_random_circle()
        circles_list.append(circle)


def delete_circles_in_circle(circles_list, circle):
    if len(circles_list) == 0:
        raise ValueError("There are no circles to delete")

    index = 0

    while index < len(circles_list):
        big_circle = circles_list[index]
        if get_x(circle) + get_r(circle) > get_x(big_circle) + get_r(big_circle) and get_y(circle) + get_r(circle) > get_y(big_circle) + get_r(big_circle):
            circles_list.pop(index)
        else:
            index = index+1


def sort_list(circles_list):
    if len(circles_list) == 0:
        raise ValueError("There are no elements to be shown")

    new_list = copy.deepcopy(circles_list)
    for i in range(0, len(new_list)):
        for j in range(i+1, len(new_list)):
            if calculate_distance_to_second_diagonal(new_list[i]) < calculate_distance_to_second_diagonal(new_list[j]):
                interchange_2_circles_in_a_list(new_list, i, j)

    return new_list


def test_delete_circles_in_circle():
    circle_list = []

    try:
        delete_circles_in_circle(circle_list, create_circle(0, 0, 0))
        assert False
    except ValueError:
        assert True

    circle_list.append(create_circle(2, 2, 2))
    circle_list.append(create_circle(5, 5, 2))
    circle_list.append(create_circle(7, 6, 10))
    circle_list.append(create_circle(12, 10, 3))
    circle_list.append(create_circle(14, 16, 2))
    delete_circles_in_circle(circle_list, create_circle(2, 2, 7))
    assert len(circle_list) == 3


test_delete_circles_in_circle()




