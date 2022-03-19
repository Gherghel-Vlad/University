'''
    Functions that deal wiht a student
'''


def create_student(student_id, student_name, student_grade):
    """
    Create a student with given attributes
    :param student_id:  The id
    :param student_name: Student's name
    :param student_grade: Student's grade, int between 1 and 10
    :return: The new student, or None if could not be created
    """
    if student_grade < 1 or student_grade>10:
        return None

    return {'id': student_id, 'name': student_name, 'grade': student_grade}


def get_id(student):
    """
    Returns student ID
    :param student: -
    :return: -
    """
    return student['id']


def get_name(student):
    return student['name']


def get_grade(student):
    return student['grade']


def to_str(student):
    return str(get_id(student)).rjust(3) + ', name: ' + str(get_name(student)).ljust(16) + ', grade: ' + str(get_grade(student)).ljust(2)


'''
    Functions that implement program features
    add_student, delete_student... 
'''


def find_by_id(student_list, student_id):
    """
    Find the student with the given id
    :param student_list: List of students
    :param student_id: This is the id (str) we are searching for
    :return: The index of the student, -1 if student not found
    """
    for index in range(len(student_list)):
        if student_id == get_id(student_list[index]):
            return index
    return -1


def get_student_by_id(student_list, student_id):
    """
    Gets the student that has the given id
    :param student_list: -
    :param student_id: -
    :return: The student with the given id, or None if it isnt found
    """
    for student in student_list:
        if student['id'] == student_id:
            return student
    return None


def delete_student_by_id(student_list, student_id):
    """
    Deletes a student by the given id
    :param student_list: The student's list
    :param student_id: The student's id
    :return: -
    """
    student = get_student_by_id(student_list, student_id)
    if student is not None:
        student_list.remove(student)



'''
    Functions for user interface
     -All print, input statements 
'''


def read_student_id():
    """
    Reads an id
    :return: The id
    """
    return input("Enter id to be deleted: ")


def read_student_ui():
    """
    Read a new student
    :return: The new student, or None if student could not be created
    """
    student_id = input("Enter id: ")
    name = input("Enter name: ")
    grade = int(input("Enter grade: "))
    return create_student(student_id, name, grade)


def add_student_ui(student_list):
    """
    Add a new student to out list
    :param student_list: List of students
    :return: -
    """
    student = read_student_ui()
    if student is None:
        print("Invalid student parameter")
        return

    #Check unique id
    if find_by_id(student_list, get_id(student)) > -1 :
        print("Duplicate student id")
        return

    student_list.append(student)


def delete_student_ui(student_list):
    """
    Deletes a student
    :param student_list: The student's list
    :return: -
    """
    student_id = read_student_id()
    if find_by_id(student_list, student_id) == -1:
        print("Invalid id. Id does not exist")
        return
    delete_student_by_id(student_list, student_id)


def show_students_ui(student_list):
    for student in student_list:
        print(to_str(student))


def print_menu():
    print("1. Add student")
    print("2. Delete student")
    print("3. Show all students")
    print("0. Exit")


def start():
    """
    Steps for UI:
        1. print menu
        2. read user input
        3. handle it!
    """

    student_list = []
    test_init(student_list)

    command_dict = {'3': show_students_ui, '1': add_student_ui, '2': delete_student_ui}

    are_we_done_yet = False

    while not are_we_done_yet:
        print_menu()
        command = input('Enter command: ')
        if command == '0':
            are_we_done_yet = True
        elif command not in command_dict:
            print("Invalid command")
        else:
            command_dict[command](student_list)


def test_init(student_list):
    student_list.append(create_student('1', "Pop Ioana", 10))
    student_list.append(create_student('2', "Man Ionel", 5))
    student_list.append(create_student('3', "Marian Sofia", 9))
    student_list.append(create_student('4', "Boca Mihaela", 6))
    student_list.append(create_student('5', "Popa Adela", 5))
    student_list.append(create_student('6', "Costin Daniel", 7))
    student_list.append(create_student('7', "Zaharia Vasile", 8))
    student_list.append(create_student('8', "Mihnea Loredana", 9))


start()






