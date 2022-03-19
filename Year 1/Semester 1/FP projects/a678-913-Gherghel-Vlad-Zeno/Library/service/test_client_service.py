import unittest

from Library.Helpers import Helper
from Library.Validators.BookValidator import BookValidator
from Library.Validators.ClientValidator import ClientValidator
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
        self.assertEqual(len(self.client_repo), 11)
        self.client_service.add_client("1234", "123")
        self.assertEqual(len(self.client_repo), 12)

    def test_remove_client(self):
        self.assertEqual(len(self.client_repo), 11)
        self.client_service.remove_client("50")
        self.assertEqual(len(self.client_repo), 10)

    def test_update_client(self):
        self.client_service.update_client("50", "asd")
        self.assertEqual(self.client_repo.find_by_client_id("50").name, "asd")

    def test_list_client(self):
        self.assertEqual(str(self.client_repo), self.client_service.list_client())

    def test_client_exists(self):
        self.assertEqual(self.client_service.client_exists("50"), True)
        self.assertEqual(self.client_service.client_exists("5gfdsdg0"), False)

    def test_search_clients_by_id(self):
        string = self.client_service.search_clients_by_id("50")
        self.assertEqual(string, str(self.client_repo.find_by_client_id("50")) + "\n")

        string = self.client_service.search_clients_by_id("sfddfsf")
        self.assertEqual(string, "No clients were found with their id containing sfddfsf\n")

    def test_search_clients_by_name(self):
        string = self.client_service.search_clients_by_name("Reta DeMildo")
        self.assertEqual(string, str(self.client_repo.find_by_client_id("50")) + "\n")

        string = self.client_service.search_clients_by_name("gfdsfds")
        self.assertEqual(string, "No clients were found with their id containing gfdsfds\n")

    def test_get_client_by_client_id(self):
        self.assertEqual(self.client_service.get_client_by_client_id("50").client_id,
                         self.client_repo.find_by_client_id("50").client_id)
