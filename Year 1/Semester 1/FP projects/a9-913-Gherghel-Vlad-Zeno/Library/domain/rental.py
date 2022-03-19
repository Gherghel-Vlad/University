from datetime import datetime


class Rental:
    def __init__(self, rental_id, book_id, client_id, rented_date, returned_date):
        self._rental_id = rental_id
        self._book_id = book_id
        self._client_id = client_id
        self.rented_date = rented_date
        self.returned_date = returned_date

    @property
    def rental_id(self):
        return self._rental_id

    @property
    def book_id(self):
        return self._book_id

    @property
    def client_id(self):
        return self._client_id

    @property
    def rented_date(self):
        return self._rented_date

    @property
    def returned_date(self):
        return self._returned_date

    @rented_date.setter
    def rented_date(self, value):
        self._rented_date = value

    @returned_date.setter
    def returned_date(self, value):
        self._returned_date = value

    def __str__(self):
        if self.returned_date is None:
            return "Rental id: " + str(self.rental_id) + " Book id: " + str(self.book_id) + " Client id: " + str(self.client_id) + " Rented date: " + str(self.rented_date.day) + "/" + str(self.rented_date.month) + "/" + str(self.rented_date.year) + " " + str(self.rented_date.hour) + ":" + str(self.rented_date.minute) + " Returned date: None"
        else:
            return "Rental id: " + str(self.rental_id) + " Book id: " + str(self.book_id) + " Client id: " + str(self.client_id) + " Rented date: " + str(self.rented_date.day) + "/" + str(self.rented_date.month) + "/" + str(self.rented_date.year) + " " + str(self.rented_date.hour) + ":" + str(self.rented_date.minute) + " Returned date: " + str(self.returned_date.day) + "/" + str(self.returned_date.month) + "/" + str(self.returned_date.year) + " " + str(self.returned_date.hour) + ":" + str(self.returned_date.minute)

    def __len__(self):
        if self.returned_date is None:
            return (datetime.now() - self.rented_date).days
        return (self.returned_date - self.rented_date).days
