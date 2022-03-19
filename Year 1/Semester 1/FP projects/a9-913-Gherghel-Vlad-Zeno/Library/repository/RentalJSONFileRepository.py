import json
import jsonpickle
from datetime import datetime
from pathlib import Path

from Library.domain.rental import Rental
from Library.repository.RentalRepository import RentalRepository


class RentalJSONFileRepositoryException(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class RentalJSONFileRepository(RentalRepository):
    def __init__(self, file_name):
        super().__init__()
        self._file_name = file_name

        # loads the data if it can or creates a new file with that name
        try:
            self._load_data()
        except FileNotFoundError as e:
            f = open(file_name, "w")
            f.close()

    @property
    def file_name(self):
        return self._file_name

    def _save_data(self):
        rental_list = super().rental_list

        f = open(self.file_name, "w")
        try:
            f.write(jsonpickle.encode(rental_list))

            f.close()
        except Exception:
            raise RentalJSONFileRepositoryException(
                "Something went wrong with the writing in the file. Please check that the file is okay.")

    def _load_data(self):
        rental_list = []

        try:
            f = open(self.file_name, "r")

            rental_list = jsonpickle.decode(f.read())

            for rental in rental_list:
                self.rent_book(rental)

            f.close()
        except json.decoder.JSONDecodeError as e:
            pass
        except FileNotFoundError as e:
            raise FileNotFoundError()
        except Exception as e:
            raise RentalJSONFileRepositoryException(
                "File " + str(self.file_name) + " could not be opened. Check if everything is alright.")

    def rent_book(self, new_rental):
        super().rent_book(new_rental)
        self._save_data()

    def return_book(self, book_id):
        super().return_book(book_id)
        self._save_data()

    def delete_by_rental_id(self, rental_id):
        super().delete_by_rental_id(rental_id)
        self._save_data()

    def remove_returned_date(self, rental_id):
        super().remove_returned_date(rental_id)
        self._save_data()
