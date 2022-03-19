import pickle
from datetime import datetime
from pathlib import Path

from Library.domain.rental import Rental
from Library.repository.RentalRepository import RentalRepository


class RentalPickleFileRepositoryException(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class RentalPickleFileRepository(RentalRepository):
    def __init__(self, file_name):
        super().__init__()
        self._file_name = file_name

        # loads the data if it can or creates a new file with that name
        try:
            self._load_data()
        except FileNotFoundError as e:
            f = open(file_name, "wb")
            f.close()

    @property
    def file_name(self):
        return self._file_name

    def _save_data(self):
        rental_list = super().rental_list

        f = open(self.file_name, "wb")
        try:
            pickle.dump(rental_list, f)

            f.close()
        except Exception:
            raise RentalPickleFileRepositoryException(
                "Something went wrong with the writing in the file. Please check that the file is okay.")

    def _load_data(self):
        rental_list = []

        try:
            f = open(self.file_name, "rb")

            rental_list = pickle.load(f)

            for rental in rental_list:
                self.rent_book(rental)

            f.close()
        except EOFError as e:
            pass
        except FileNotFoundError as e:
            raise FileNotFoundError()
        except IOError as e:
            raise RentalPickleFileRepositoryException(
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
