import unittest

from Library.domain.client import Client
from Library.repository.ClientRepository import ClientRepository, ClientRepositoryException


class TestClientRepo(unittest.TestCase):

    def setUp(self):
        self.client_repo = ClientRepository()

    def test_client_list(self):
        self.assertEqual(len(self.client_repo.client_list), 0)
        self.client_repo.add_client(Client("123", "asd"))
        self.assertEqual(len(self.client_repo.client_list), 1)

    def test_add_client(self):
        self.assertEqual(len(self.client_repo), 0)
        self.client_repo.add_client(Client("123", "asd"))
        self.assertEqual(len(self.client_repo), 1)

        with self.assertRaises(ClientRepositoryException):
            self.client_repo.add_client(Client("123", "asd"))

    def test_remove_client(self):
        self.client_repo.add_client(Client("123", "asd"))
        self.assertEqual(len(self.client_repo), 1)

        self.client_repo.remove_client("123")
        self.assertEqual(len(self.client_repo), 0)

        with self.assertRaises(ClientRepositoryException):
            self.client_repo.remove_client("123")

    def test_update_client(self):
        self.client_repo.add_client(Client("123", "asd"))
        self.client_repo.update_client("123", "john")

        self.assertEqual(self.client_repo.client_list[0].name, "john")

        with self.assertRaises(ClientRepositoryException):
            self.client_repo.update_client("1234", "john")
        with self.assertRaises(ClientRepositoryException):
            self.client_repo.update_client("123", "john")

    def test_find(self):
        self.assertEqual(self.client_repo.find("123"), -1)
        self.client_repo.add_client(Client("123", "asd"))
        self.assertEqual(self.client_repo.find("123"), 0)

    def test_str(self):
        self.assertEqual(str(self.client_repo), "Library Clients: \nThere are no clients yet.")
        self.client_repo.add_client(Client("123", "asd"))
        self.assertEqual(str(self.client_repo), "Library Clients: \n" + str(Client("123", "asd")) + "\n")

    def test_search_client_by_id(self):
        self.client_repo.add_client(Client("123", "asd"))
        self.client_repo.add_client(Client("124", "asdf"))
        self.client_repo.add_client(Client("1235", "afsd"))

        self.assertEqual(len(self.client_repo.search_clients_by_id("23")), 2)
        self.assertEqual(len(self.client_repo.search_clients_by_id("234")), 0)

    def test_search_client_by_name(self):
        self.client_repo.add_client(Client("123", "asd"))
        self.client_repo.add_client(Client("124", "asdf"))
        self.client_repo.add_client(Client("1235", "afsd"))

        self.assertEqual(len(self.client_repo.search_clients_by_name("aSd")), 2)
        self.assertEqual(len(self.client_repo.search_clients_by_name("asdfg")), 0)

    def test_find_by_client_id(self):
        self.client_repo.add_client(Client("123", "asd"))

        self.assertEqual(self.client_repo.find_by_client_id("123").name, "asd")
        self.assertEqual(self.client_repo.find_by_client_id("1234"), None)

    def test_len(self):
        self.assertEqual(len(self.client_repo), 0)
        self.client_repo.add_client(Client("123", "asd"))

        self.assertEqual(len(self.client_repo), 1)

    def test_getitem(self):
        self.client_repo.add_client(Client("123", "asd"))

        self.assertEqual(self.client_repo["123"].name, "asd")

        with self.assertRaises(ClientRepositoryException):
            client = self.client_repo["1234"]
