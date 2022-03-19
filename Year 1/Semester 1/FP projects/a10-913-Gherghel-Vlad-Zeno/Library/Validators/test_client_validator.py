import unittest

from Library.Validators.ClientValidator import ClientValidatorException, ClientValidator
from Library.domain.client import Client


class TestClient(unittest.TestCase):
    def test_validate_client_name(self):
        with self.assertRaises(ClientValidatorException):
            ClientValidator.validate_client_name(123)
        with self.assertRaises(ClientValidatorException):
            ClientValidator.validate_client_name("")

    def test_validate_client_id(self):
        with self.assertRaises(ClientValidatorException):
            ClientValidator.validate_client_id(123)
        with self.assertRaises(ClientValidatorException):
            ClientValidator.validate_client_id("")

    def test_validate_client(self):
        with self.assertRaises(ClientValidatorException):
            ClientValidator.validate_client(123)
        with self.assertRaises(ClientValidatorException):
            ClientValidator.validate_client(Client(123, "john"))
        with self.assertRaises(ClientValidatorException):
            ClientValidator.validate_client(Client("123", 123))

