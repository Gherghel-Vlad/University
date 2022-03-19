import unittest

from Library.domain.client import Client


class TestClientClass(unittest.TestCase):
    def setUp(self):
        self.c = Client("123", "asd")

    def test_property_setter(self):
        self.assertEqual(self.c.client_id, "123")
        self.assertEqual(self.c.name, "asd")

        self.c.name = "qwerty"
        self.assertEqual(self.c.name, "qwerty")

    def test_str(self):
        self.assertEqual(str(self.c), "Id: 123 Name: asd")

