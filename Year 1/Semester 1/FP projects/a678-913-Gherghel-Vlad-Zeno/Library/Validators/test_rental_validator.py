import unittest
from datetime import datetime

from Library.Validators.RentalValidator import RentalValidatorException, RentalValidator
from Library.domain.rental import Rental


class TestRentalValidator(unittest.TestCase):
    def test_validate_rental_id(self):
        with self.assertRaises(RentalValidatorException):
            RentalValidator.validate_rental_id("")
        with self.assertRaises(RentalValidatorException):
            RentalValidator.validate_rental_id(None)

    def test_validate_client_id(self):
        with self.assertRaises(RentalValidatorException):
            RentalValidator.validate_client_id("")
        with self.assertRaises(RentalValidatorException):
            RentalValidator.validate_client_id(None)

    def test_validate_book_id(self):
        with self.assertRaises(RentalValidatorException):
            RentalValidator.validate_book_id("")
        with self.assertRaises(RentalValidatorException):
            RentalValidator.validate_book_id(None)

    def test_validate_rental(self):
        rental = Rental("", "123", "123", datetime.now(), None)
        with self.assertRaises(RentalValidatorException):
            RentalValidator.validate_rental(rental)
        rental = Rental("123", "", "123", datetime.now(), None)
        with self.assertRaises(RentalValidatorException):
            RentalValidator.validate_rental(rental)
        rental = Rental("123", "123", "", datetime.now(), None)
        with self.assertRaises(RentalValidatorException):
            RentalValidator.validate_rental(rental)
        with self.assertRaises(RentalValidatorException):
            RentalValidator.validate_rental(123)
