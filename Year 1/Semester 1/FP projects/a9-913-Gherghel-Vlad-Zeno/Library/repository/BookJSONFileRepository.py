import json
import jsonpickle
from pathlib import Path
from Library.domain.book import Book
from Library.repository.BookRepository import BookRepository


class BookJSONFileRepositoryException(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class BookJSONFileRepository(BookRepository):
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
        book_list = super().book_list

        f = open(self.file_name, "w")
        try:
            # json.dump(book_list, f)
            f.write(jsonpickle.encode(book_list))

            f.close()
        except Exception:
            raise BookJSONFileRepositoryException(
                "Something went wrong with the writing in the file. Please check that the file is okay.")

    def _load_data(self):
        book_list = []

        try:
            f = open(self.file_name, "r")

            book_list = jsonpickle.decode(f.read())

            for book in book_list:
                self.add_book(book)

            f.close()
        except json.decoder.JSONDecodeError as e:
            pass
        except FileNotFoundError as e:
            raise FileNotFoundError()
        except Exception as e:
            raise BookJSONFileRepositoryException(
                "File " + str(self.file_name) + " could not be opened. Check if everything is alright.")

    def add_book(self, book):
        super().add_book(book)
        self._save_data()

    def remove_book(self, id_):
        super().remove_book(id_)
        self._save_data()

    def update_book(self, id_, new_title, new_author):
        super().update_book(id_, new_title, new_author)
        self._save_data()
