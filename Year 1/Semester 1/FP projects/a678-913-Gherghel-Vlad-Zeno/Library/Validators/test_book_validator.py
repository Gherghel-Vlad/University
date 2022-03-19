import unittest

from Library.Validators.BookValidator import BookValidatorException, BookValidator
from Library.domain.book import Book


class TesBookValidator(unittest.TestCase):
    def test_validate_book_title(self):
        with self.assertRaises(BookValidatorException):
            BookValidator.validate_book_title(123)
        with self.assertRaises(BookValidatorException):
            BookValidator.validate_book_title("")

    def test_validate_book_id(self):
        with self.assertRaises(BookValidatorException):
            BookValidator.validate_book_id("")
        with self.assertRaises(BookValidatorException):
            BookValidator.validate_book_id(123)
        with self.assertRaises(BookValidatorException):
            BookValidator.validate_book_id(-123)

    def test_validate_book_author(self):
        with self.assertRaises(BookValidatorException):
            BookValidator.validate_book_author("")
        with self.assertRaises(BookValidatorException):
            BookValidator.validate_book_author(123)

    def test_validate_book(self):
        with self.assertRaises(BookValidatorException):
            BookValidator.validate_book(Book(123, 123, 123))
        with self.assertRaises(BookValidatorException):
            BookValidator.validate_book(Book("123", 123, 123))
        with self.assertRaises(BookValidatorException):
            BookValidator.validate_book(Book("123", "123", 123))
        with self.assertRaises(BookValidatorException):
            BookValidator.validate_book(0)
