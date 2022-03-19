import unittest

from Library.Helpers import Helper
from Library.Validators.BookValidator import BookValidator
from Library.Validators.ClientValidator import ClientValidator
from Library.domain.book import Book
from Library.repository.BookRepository import BookRepository
from Library.repository.ClientRepository import ClientRepository
from Library.repository.RentalRepository import RentalRepository
from Library.service.BookService import BookService
from Library.service.ClientService import ClientService
from Library.service.RentalService import RentalService
from Library.service.UndoRedoFunctionality import UndoService


class TestBookService(unittest.TestCase):
    def setUp(self):
        self.undo_service = UndoService()

        self.book_validator = BookValidator()

        self.book_repo = BookRepository()

        self.client_repo = ClientRepository()

        self.client_validator = ClientValidator()

        self.rental_repo = RentalRepository()
        self.rental_repo.add_dummy_data()

        self.client_service = ClientService(self.client_repo, self.client_validator, self.rental_repo, self.undo_service)
        self.book_service = BookService(self.book_repo, self.book_validator, self.rental_repo, self.undo_service)
        self.rental_service = RentalService(self.rental_repo, self.book_service, self.client_service, self.undo_service)

        Helper.add_clients(self.client_service)
        Helper.add_books(self.book_service)

    def test_adding(self):
        self.assertEqual(len(self.book_repo), 10)
        self.book_service.add_book("1234", "123", "123")
        self.assertEqual(len(self.book_repo), 11)

    def test_removing(self):
        self.assertEqual(len(self.book_repo), 10)
        self.book_service.remove_book("23")
        self.assertEqual(len(self.book_repo), 9)
        self.assertEqual(len(self.rental_repo.rental_list), 8)

    def test_update_book(self):
        self.book_service.update_book("23", "asd", "asd")
        self.assertEqual(self.book_repo.find_book("23").title, "asd")
        self.assertEqual(self.book_repo.find_book("23").author, "asd")

    def test_list_books(self):
        self.assertEqual(str(self.book_repo), self.book_service.list_books())

    def test_book_exists(self):
        self.assertEqual(self.book_service.book_exists("23"), True)
        self.assertEqual(self.book_service.book_exists("234324"), False)

    def test_search_books_by_id(self):
        self.assertEqual(self.book_service.search_books_by_id("23"), str(self.book_repo.find_book("23")) + "\n")
        self.assertEqual(self.book_service.search_books_by_id("2fds3"),
                         "No books were found with their id containing 2fds3\n")

    def test_search_books_by_title(self):
        self.assertEqual(self.book_service.search_books_by_title("Ala"),
                         str(self.book_repo.find_book("23")) + "\n" + str(self.book_repo.find_book("45")) + "\n" + str(
                             self.book_repo.find_book("64")) + "\n")
        self.assertEqual(self.book_service.search_books_by_title("adsafsd"), "No books were found with their title containing adsafsd\n")

    def test_search_books_by_author(self):
        self.assertEqual(self.book_service.search_books_by_author("Jiran"), str(self.book_repo.find_book("23")) + "\n")
        self.assertEqual(self.book_service.search_books_by_author("Ddfsfdsfd"),
                         "No books were found with their author containing Ddfsfdsfd\n")

    def test_get_book_by_book_id(self):
        self.assertEqual(self.book_service.get_book_by_book_id("23"), Book("23", "Ala", "Jiran"))
