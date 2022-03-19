import unittest

from Library.Helpers import Helper
from Library.data_structures.IterableDataStructure import IterableDataStructure, gnome_sort, filter_list
from Library.domain.client import Client


class TestIterableDataStructure(unittest.TestCase):
    def setUp(self):
        self.data = IterableDataStructure()
        Helper.add_clients_append(self.data)
        self.normal_list = []
        Helper.add_clients_append(self.normal_list)

    def test_list(self):
        self.assertEqual(self.data.list[3].name, self.normal_list[3].name)
        self.assertEqual(self.data.list[3].client_id, self.normal_list[3].client_id)

    def test_getitem(self):
        for index in range(0, len(self.data)):
            self.assertEqual(self.data[index].name, self.normal_list[index].name)
            self.assertEqual(self.data[index].client_id, self.normal_list[index].client_id)

    def test_setitem(self):
        self.data[3] = Client("asd", "asdf")
        self.assertEqual(self.data[3].client_id, "asd")
        self.assertEqual(self.data[3].name, "asdf")

    def test_delitem(self):
        del self.data[3]
        self.assertEqual(len(self.data), len(self.normal_list) - 1)

    def test_len(self):
        self.assertEqual(len(self.data), len(self.normal_list))

    def test_iter(self):
        index = 0
        for elem in self.data:
            self.assertEqual(elem.name, self.normal_list[index].name)
            self.assertEqual(elem.client_id, self.normal_list[index].client_id)
            index += 1

    def test_append(self):
        self.data.append(Client("asd", "asd"))
        self.assertEqual(self.data[len(self.data) - 1].name, "asd")
        self.assertEqual(self.data[len(self.data) - 1].client_id, "asd")


class TestGnomeSort(unittest.TestCase):
    def setUp(self):
        self.list = []
        Helper.add_clients_append(self.list)

    def test_gnome_sort_ascending(self):
        normal_sorted_list = []
        Helper.add_clients_append(normal_sorted_list)

        gnome_sort(self.list, lambda a, b: a.client_id > b.client_id)
        normal_sorted_list.sort(key=lambda a: a.client_id)

        for index in range(0, len(self.list)):
            self.assertEqual(self.list[index].name, normal_sorted_list[index].name)
            self.assertEqual(self.list[index].client_id, normal_sorted_list[index].client_id)

    def test_gnome_sort_descending(self):
        normal_sorted_list = []
        Helper.add_clients_append(normal_sorted_list)

        gnome_sort(self.list, lambda a, b: a.client_id < b.client_id)
        normal_sorted_list.sort(key=lambda a: a.client_id, reverse=True)

        for index in range(0, len(self.list)):
            self.assertEqual(self.list[index].name, normal_sorted_list[index].name)
            self.assertEqual(self.list[index].client_id, normal_sorted_list[index].client_id)


class TestFilter(unittest.TestCase):
    def setUp(self):
        self.list = []
        Helper.add_clients_append(self.list)

    def test_filter_list_client_id_case(self):
        filtered_list = filter_list(self.list, lambda x: "1" in x.client_id)
        self.assertEqual(len(filtered_list), 1)

        filtered_list = filter_list(self.list, lambda x: "6" in x.client_id)
        self.assertEqual(len(filtered_list), 4)

    def test_filter_list_name_case(self):
        filtered_list = filter_list(self.list, lambda x: "a" in str(x.name).lower())
        self.assertEqual(len(filtered_list), 9)

        filtered_list = filter_list(self.list, lambda x: "Kimiko Yui" in x.name)
        self.assertEqual(len(filtered_list), 1)