"""
    Entity class should be coded here
"""
import random

from src.Helpers.helpers import Helpers
from src.domain.BookException import BookException


class Book:
    def __init__(self, author="", title="", isbn=""):
        """
        Constructor for the Book class
        :param isbn: The ISBN of a book (can be with 10 digits or 13 digits)
        :param author: The book's author's name
        :param title: The book's title
        Raises BookException if the ISBN is not formed with 10 or 13 digits
        """
        if author == "":
            author = Helpers.generate_author_name()
        if title == "":
            title = Helpers.generate_title()
        if isbn == "":
            isbn = Helpers.generate_isbn()
        self.isbn = isbn
        if not self.check_isbn():
            raise BookException("ISBN is not valid. Please try another one.")

        self.author = author
        self.title = title

    @property
    def isbn(self):
        return self._isbn

    @property
    def author(self):
        return self._author

    @property
    def title(self):
        return self._title

    @isbn.setter
    def isbn(self, value):
        self._isbn = value

    @author.setter
    def author(self, value):
        self._author = value

    @title.setter
    def title(self, value):
        self._title = value

    def to_string_format(self):
        """
        Creates a string representation of the instance
        :return: A string representation of the instance
        """
        return "ISBN: " + str(self.isbn) + "   Author: " + str(self.author) + 10*" " + "Title: " + str(self.title)

    def check_isbn(self):
        """
        Checks if the given value is a valid isbn
        :param isbn: The isbn that's going to be checked
        :return: True if it s a valid isbn, False otherwise
        """
        list_strings = str(self.isbn).lower().split("-")
        for string in list_strings:
            string = string.strip()

        sum_len = 0
        for string in list_strings:
            sum_len += len(string)

        if sum_len not in [10, 13]:
            return False

        for string in list_strings:
            try:
                int(string)
            except ValueError:
                return False

        return True


def test_class_book():
    b1 = Book("Marie Carol", "Before the Abyss", "1-123-45678-122-3")
    b2 = Book("NotG0d", "I am so sorry, my friend", "5-342-5435-12")
    b3 = Book("NotG0d", "I'll see you later, dear friend")
    b4 = Book()

    try:
        # ISBN too short
        b3 = Book("Aaa", "Bbb", "4-324-45")
        assert False
    except BookException:
        assert True
    try:
        # ISBN contains letters
        b4 = Book("Aaa", "Bbb", "4-324-45a-4357")
        assert False
    except BookException:
        assert True
    try:
        # ISBN is too long
        b5 = Book("Aaa", "Bbb", "4-324-459-4357-123")
        assert False
    except BookException:
        assert True

    assert b1.isbn == "1-123-45678-122-3" and b1.author == "Marie Carol" and b1.title == "Before the Abyss"

    assert len(b4.title) > 0 and len(b4.isbn) > 0 and len(b4.author) > 0


test_class_book()
