import unittest

from Library.domain.book import Book
from Library.repository.BookRepository import BookRepository, BookRepositoryException


class TestBookRepo(unittest.TestCase):

    def setUp(self):
        self.book_repo = BookRepository()

    def test_add_book(self):
        self.assertEqual(len(self.book_repo), 0)
        self.book_repo.add_book(Book("123", "asd", "asdw"))
        self.assertEqual(len(self.book_repo), 1)

        with self.assertRaises(BookRepositoryException):
            self.book_repo.add_book(Book("123", "asdw", "frg"))

    def test_book_list(self):
        self.book_repo.add_book(Book("123", "asd", "asdw"))

        self.assertEqual(len(self.book_repo.book_list), 1)

    def test_remove_book(self):
        self.book_repo.add_book(Book("123", "asd", "asdw"))
        self.assertEqual(len(self.book_repo.book_list), 1)

        self.book_repo.remove_book("123")
        self.assertEqual(len(self.book_repo.book_list), 0)

        with self.assertRaises(BookRepositoryException):
            self.book_repo.remove_book("123")

    def test_update_book(self):
        self.book_repo.add_book(Book("123", "asd", "asdw"))

        self.book_repo.update_book("123", "john", "")
        self.assertEqual(self.book_repo["123"].title, "john")

        self.book_repo.update_book("123", "", "qwerty")
        self.assertEqual(self.book_repo["123"].author, "qwerty")

        with self.assertRaises(BookRepositoryException):
            self.book_repo.update_book("1234", "asd", "qwerty")
        with self.assertRaises(BookRepositoryException):
            self.book_repo.update_book("123", "john", "qwerty")

    def test_find(self):
        self.assertEqual(self.book_repo.find("123"), -1)

        self.book_repo.add_book(Book("123", "asd", "asdw"))
        self.assertEqual(self.book_repo.find("123"), 0)

    def test_str(self):
        self.assertEqual(str(self.book_repo), "Library Books: \nThere are no books yet")

        self.book_repo.add_book(Book("123", "asd", "asdw"))
        self.assertEqual(str(self.book_repo), "Library Books: \n" + str(Book("123", "asd", "asdw")) + "\n")

    def test_search_books_by_id(self):
        self.book_repo.add_book(Book("123", "asd", "asd"))
        self.book_repo.add_book(Book("1234", "asfd", "dasd"))
        self.book_repo.add_book(Book("12535", "asdf", "assd"))

        book_list = self.book_repo.search_books_by_id("23")
        self.assertEqual(len(book_list), 2)
        book_list = self.book_repo.search_books_by_id("2345")
        self.assertEqual(len(book_list), 0)

    def test_search_books_by_title(self):
        self.book_repo.add_book(Book("123", "asd", "asd"))
        self.book_repo.add_book(Book("1234", "asfd", "dasd"))
        self.book_repo.add_book(Book("12535", "asdf", "assd"))

        book_list = self.book_repo.search_books_by_title("sD")
        self.assertEqual(len(book_list), 2)
        book_list = self.book_repo.search_books_by_title("sfedd")
        self.assertEqual(len(book_list), 0)

    def test_search_books_by_author(self):
        self.book_repo.add_book(Book("123", "asd", "aSd"))
        self.book_repo.add_book(Book("1234", "asfd", "dafdsd"))
        self.book_repo.add_book(Book("12535", "asdf", "asdf"))

        book_list = self.book_repo.search_books_by_author("asD")
        self.assertEqual(len(book_list), 2)
        book_list = self.book_repo.search_books_by_author("asfdedsfd")
        self.assertEqual(len(book_list), 0)

    def test_find_book(self):
        self.book_repo.add_book(Book("123", "asd", "asd"))
        self.assertEqual(self.book_repo.find_book("123"), Book("123", "asd", "asd"))
        self.assertEqual(self.book_repo.find_book("1234"), None)


