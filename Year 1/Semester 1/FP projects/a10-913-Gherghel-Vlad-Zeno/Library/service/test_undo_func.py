import unittest

from Library.Validators.BookValidator import BookValidator
from Library.Validators.ClientValidator import ClientValidator
from Library.repository.BookRepository import BookRepository
from Library.repository.ClientRepository import ClientRepository
from Library.repository.RentalRepository import RentalRepository
from Library.service.BookService import BookService
from Library.service.ClientService import ClientService
from Library.service.RentalService import RentalService
from Library.service.UndoRedoFunctionality import FunctionCall, Operation, UndoService
from Library.Helpers import Helper


class TestUndoFunc(unittest.TestCase):
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

    def test_undo(self):
        self.book_service.add_book("123", "123", "123")
        self.assertEqual(len(self.book_repo), 11)
        self.undo_service.undo()
        self.assertEqual(len(self.book_repo), 10)
        self.undo_service.redo()
        self.assertEqual(len(self.book_repo), 11)

    def test_undo_cascade(self):
        self.book_service.add_book("123", "123", "123")
        self.book_service.add_book("1234", "1234", "1234")
        self.assertEqual(self.undo_service.redo(), False)
        self.assertEqual(len(self.book_repo), 12)
        self.undo_service.undo()
        self.assertEqual(len(self.book_repo), 11)
        self.undo_service.undo()
        self.assertEqual(len(self.book_repo), 10)
        self.undo_service.redo()
        self.assertEqual(len(self.book_repo), 11)
        self.undo_service.redo()
        self.assertEqual(len(self.book_repo), 12)

    def test_undo_cascade_2(self):
        self.book_service.remove_book("23")
        self.assertEqual(len(self.rental_repo.rental_list), 8)
        self.assertEqual(len(self.book_repo), 9)
        self.undo_service.undo()
        self.assertEqual(len(self.rental_repo.rental_list), 10)
        self.assertEqual(len(self.book_repo), 10)
        self.undo_service.redo()
        self.assertEqual(len(self.rental_repo.rental_list), 8)
        self.assertEqual(len(self.book_repo), 9)

    def test_undo_cascade_3(self):
        self.book_service.add_book("123", "123", "123")
        self.book_service.add_book("1243", "1243", "1243")
        self.undo_service.undo()
        self.book_service.add_book("1243", "1243", "1243")
        self.assertEqual(len(self.book_repo), 12)


class TestSpecialCase(unittest.TestCase):
    def test_undo_false(self):
        undo_service = UndoService()
        self.assertEqual(undo_service.undo(), False)
