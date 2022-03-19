import unittest
from datetime import datetime

from Library.domain.rental import Rental
from Library.repository.RentalRepository import RentalRepository, RentalRepositoryException


class TestRentalRepoClass(unittest.TestCase):
    def setUp(self):
        self.rental_repo = RentalRepository()
        self.rental_repo.rent_book(Rental("123", "123", "123", datetime.now(), None))
        self.rental_repo.rent_book(Rental("1234", "1234", "1234", datetime.now(), datetime.now()))

    def test_rental_list(self):
        self.assertEqual(len(self.rental_repo.rental_list), 2)

    def test_is_book_available(self):
        self.assertEqual(self.rental_repo.is_book_available("123"), False)
        self.assertEqual(self.rental_repo.is_book_available("1234"), True)

    def test_find_not_returned_rental_by_book_id(self):
        self.assertEqual(self.rental_repo.find_not_returned_rental_by_book_id("123"), 0)
        self.assertEqual(self.rental_repo.find_not_returned_rental_by_book_id("1233"), -1)

    def test_rent_book(self):
        with self.assertRaises(RentalRepositoryException):
            self.rental_repo.rent_book(Rental("123", "123", "123", datetime.now(), None))
        with self.assertRaises(RentalRepositoryException):
            self.rental_repo.rent_book(Rental("123", "1234", "123", datetime.now(), None))
        self.rental_repo.rent_book(Rental("12345", "12344", "12332", datetime.now(), None))
        self.assertEqual(len(self.rental_repo.rental_list), 3)

    def test_return_book(self):
        with self.assertRaises(RentalRepositoryException):
            self.rental_repo.return_book("1234")
        self.rental_repo.return_book("123")
        self.assertIsNotNone(self.rental_repo.rental_list[0].returned_date)

    def test_filter_by_book_id(self):
        list = self.rental_repo.filter_by_book_id("123")

        self.assertEqual(len(list), 1)

    def test_filter_by_client_id(self):
        list = self.rental_repo.filter_by_client_id("123")

        self.assertEqual(len(list), 1)

    def test_delete_by_rental_id(self):
        self.assertEqual(len(self.rental_repo.rental_list), 2)
        self.rental_repo.delete_by_rental_id("123")
        self.assertEqual(len(self.rental_repo.rental_list), 1)

    def test_remove_returned_date(self):
        self.rental_repo.remove_returned_date("1234")
        self.assertIsNone(self.rental_repo.rental_list[1].returned_date)

    def test_str(self):
        self.assertEqual(str(self.rental_repo), "Rentals: \n" + str(Rental("123", "123", "123", datetime.now(), None)) + "\n" + str(Rental("1234", "1234", "1234", datetime.now(), datetime.now())) + "\n")
        self.rental_repo.delete_by_rental_id("123")
        self.rental_repo.delete_by_rental_id("1234")
        self.assertEqual(str(self.rental_repo), "Rentals: \nThere are no rentals yet \n")

    def test_add_dummy_data(self):
        self.rental_repo.add_dummy_data()
        self.assertEqual(len(self.rental_repo.rental_list), 12)