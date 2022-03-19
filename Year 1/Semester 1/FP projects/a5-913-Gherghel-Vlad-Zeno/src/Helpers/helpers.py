import random


class Helpers:
    """
    This class is dedicated to functions that help in other processes
    """

    @staticmethod
    def generate_isbn():
        """
        Creates a random ISBN (with a fixed format of 3-1-5-3-1 digits)
        :return: An ISBN number
        """
        list_length = [3, 1, 5, 3, 1]
        isbn = ""
        for length in list_length:
            for index in range(0, length):
                isbn += str(random.randint(0, 9))
            isbn += "-"
        isbn = isbn[:-1]
        return isbn

    @staticmethod
    def _read_names():
        """
        Reads the names from the names.txt
        :return: A list created with those names (has 200 names)
        """
        list_names = []
        f = open("../names.txt", "r")

        for index in range(0, 100):
            string = f.readline()
            string = string[:-1]
            string_list = string.split("\t")
            list_names.append(string_list[1])
            list_names.append(string_list[3])

        return list_names

    @staticmethod
    def generate_author_name():
        """
        Generates author names using the names from names.txt
        :return: A new author name (string)
        """
        list_names = Helpers._read_names()

        how_many_names = random.randint(1, 3)

        name = ""
        for index in range(0, how_many_names):
            random_int = random.randint(0, 199)
            name += list_names[random_int].strip() + " "
        name = name[:-1]
        return name

    @staticmethod
    def _read_titles():
        """
        Reads all the words in the titles.txt
        :return: a list containing all the words from the titles.txt
        """
        f = open("../titles.txt", "r")

        titles_list = []
        string = f.readline()
        string = string.replace(".", "")
        string = string.replace(",", "")

        string_list = string.split(" ")
        for index in range(0, len(string_list)):
            titles_list.append(string_list[index].strip())

        string = f.readline()
        string = string.replace(".", "")
        string = string.replace(",", "")

        string_list = string.split(" ")
        for index in range(0, len(string_list)):
            titles_list.append(string_list[index].strip())

        return titles_list

    @staticmethod
    def generate_title():
        """
        Generates a title using the words from titles.txt
        :return: A title (string) that uses the words from titles.txt
        """
        list_titles = Helpers._read_titles()

        how_many_titles = random.randint(1, 5)

        title = ""
        for index in range(0, how_many_titles):
            random_int = random.randint(0, 99)
            title += list_titles[random_int].strip() + " "
        title = title[:-1]
        title = title.capitalize()
        return title


def test_generate_isbn():
    isbn = Helpers.generate_isbn()

    assert len(isbn) == 17


def test_generate_authors_name():
    name = Helpers.generate_author_name()

    assert len(name) > 0 and isinstance(name, str)


def test_generate_title():
    title = Helpers.generate_title()
    assert len(title) > 0 and isinstance(title, str)


test_generate_isbn()

test_generate_authors_name()

test_generate_title()
