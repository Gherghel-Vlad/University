import unittest

from Library.Helpers import Helper
from Library.Validators.BookValidator import BookValidator
from Library.Validators.ClientValidator import ClientValidator
from Library.domain.book import Book
from Library.domain.client import Client
from Library.repository.BookRepository import BookRepository
from Library.repository.ClientRepository import ClientRepository
from Library.repository.RentalRepository import RentalRepository
from Library.service.BookService import BookService
from Library.service.ClientService import ClientService
from Library.service.RentalService import RentalService, RentalServiceException, BookRentedDays, ClientRentalDays, \
    AuthorRentalNumber
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

        self.client_service = ClientService(self.client_repo, self.client_validator, self.rental_repo,
                                            self.undo_service)
        self.book_service = BookService(self.book_repo, self.book_validator, self.rental_repo, self.undo_service)
        self.rental_service = RentalService(self.rental_repo, self.book_service, self.client_service, self.undo_service)

        Helper.add_clients(self.client_service)
        Helper.add_books(self.book_service)

    def test_rent_book(self):
        self.assertEqual(len(self.rental_repo.rental_list), 10)
        self.rental_service.rent_book("123", "23", "50")
        self.assertEqual(len(self.rental_repo.rental_list), 11)

        with self.assertRaises(RentalServiceException):
            self.rental_service.rent_book("123", "2fdsfd3", "50")
        with self.assertRaises(RentalServiceException):
            self.rental_service.rent_book("123", "23", "5fdsf0")

    def test_return_book(self):
        with self.assertRaises(RentalServiceException):
            self.rental_service.rent_book("123ds", "asd", "asd")

        self.rental_service.return_book("61")
        self.assertIsNotNone(self.rental_repo.filter_by_book_id("61")[0].returned_date, None)

    def test_rental_list(self):
        self.assertEqual(str(self.rental_repo), self.rental_service.rental_list())

    def test_delete_rentals_by_client_id(self):
        self.rental_service.delete_rentals_by_client_id("50")
        self.assertEqual(len(self.rental_repo.rental_list), 8)
        self.rental_service.delete_rentals_by_client_id("50")
        self.assertEqual(len(self.rental_repo.rental_list), 8)

    def test_delete_rentals_by_book_id(self):
        self.rental_service.delete_rentals_by_book_id("23")
        self.assertEqual(len(self.rental_repo.rental_list), 8)
        self.rental_service.delete_rentals_by_book_id("23")
        self.assertEqual(len(self.rental_repo.rental_list), 8)

    def test_most_rented_books(self):
        list = self.rental_service.most_rented_books()
        self.assertGreater(len(list), 0)
        list = self.rental_service.most_active_clients()
        self.assertGreater(len(list), 0)
        list = self.rental_service.most_rented_authors()
        self.assertGreater(len(list), 0)

    def test_book_rented_days_class(self):
        book = Book("123", "123", "123")
        brd = BookRentedDays(book, 12)
        self.assertEqual(brd.book.book_id, book.book_id)
        self.assertEqual(brd.rented_times, 12)
        self.assertEqual(str(brd), str(book) + " Rented times: " + str(12))

    def test_client_rental_days(self):
        client = Client("123", "123")
        crd = ClientRentalDays(client, 12)
        self.assertEqual(crd.client.client_id, client.client_id)
        self.assertEqual(crd.rented_days, 12)
        self.assertEqual(str(crd), str(client) + " Rented days: " + str(12))

    def test_author_rental_number(self):
        arn = AuthorRentalNumber("asd", 12)
        self.assertEqual(arn.author, "asd")
        self.assertEqual(arn.rental_number, 12)
        self.assertEqual(str(arn), "asd Rental number: 12")
