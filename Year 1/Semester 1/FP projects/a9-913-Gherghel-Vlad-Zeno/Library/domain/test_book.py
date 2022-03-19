import unittest
from datetime import datetime

from Library.domain.book import Book, BookException
from Library.domain.rental import Rental


class TestBookClass(unittest.TestCase):

    def setUp(self):
        self.book = Book("123", "asd", "qwerty")
        self.book2 = Book("123", "asd", "qwerty")
        self.book3 = Book("1234", "asdf", "qwertyu")
        self.random_object = "123"

    def test_property_setter(self):
        self.assertEqual(self.book.author, "qwerty")
        self.assertEqual(self.book.title, "asd")
        self.assertEqual(self.book.book_id, "123")

        self.book.author = "ty"
        self.assertEqual(self.book.author, "ty")

        self.book.title = "her"
        self.assertEqual(self.book.title, "her")

    def test_str(self):
        self.assertEqual(str(self.book), "Id: 123 Title: asd Author: qwerty")

    def test_eq(self):
        self.assertEqual(self.book == self.book2, True)
        self.assertEqual(self.book == self.book3, False)
        with self.assertRaises(BookException):
            self.assertEqual(self.book == self.random_object, True)

