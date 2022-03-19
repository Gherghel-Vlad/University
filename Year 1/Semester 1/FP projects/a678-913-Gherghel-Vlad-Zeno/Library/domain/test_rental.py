import unittest
import datetime

from Library.domain.rental import Rental


class TestRentalClass(unittest.TestCase):
    def setUp(self):
        self.rented_date = datetime.datetime.now()
        self.returned_date = datetime.datetime.now()
        self.rental1 = Rental("123", "123", "123", self.rented_date, None)
        self.rental2 = Rental("1234", "1234", "1234", self.rented_date, self.returned_date)

    def test_properties(self):
        self.assertEqual(self.rental1.rental_id, "123")
        self.assertEqual(self.rental1.book_id, "123")
        self.assertEqual(self.rental1.client_id, "123")
        self.assertEqual(self.rental1.rented_date, self.rented_date)
        self.assertIsNone(self.rental1.returned_date)
        self.assertEqual(self.rental2.returned_date, self.returned_date)

        new_date = datetime.datetime.now()

        self.rental1.returned_date = new_date
        self.assertEqual(self.rental1.returned_date, new_date)

        self.rental2.rented_date = new_date
        self.assertEqual(self.rental2.rented_date, new_date)

    def test_str(self):
        self.assertEqual(str(self.rental2), "Rental id: " + str(self.rental2.rental_id) + " Book id: " + str(self.rental2.book_id) + " Client id: " + str(self.rental2.client_id) + " Rented date: " + str(self.rental2.rented_date.day) + "/" + str(self.rental2.rented_date.month) + "/" + str(self.rental2.rented_date.year) + " " + str(self.rental2.rented_date.hour) + ":" + str(self.rental2.rented_date.minute) + " Returned date: " + str(self.rental2.returned_date.day) + "/" + str(self.rental2.returned_date.month) + "/" + str(self.rental2.returned_date.year) + " " + str(self.rental2.returned_date.hour) + ":" + str(self.rental2.returned_date.minute))
        self.assertEqual(str(self.rental1), "Rental id: " + str(self.rental1.rental_id) + " Book id: " + str(self.rental1.book_id) + " Client id: " + str(self.rental1.client_id) + " Rented date: " + str(self.rental1.rented_date.day) + "/" + str(self.rental1.rented_date.month) + "/" + str(self.rental1.rented_date.year) + " " + str(self.rental1.rented_date.hour) + ":" + str(self.rental1.rented_date.minute) + " Returned date: None")