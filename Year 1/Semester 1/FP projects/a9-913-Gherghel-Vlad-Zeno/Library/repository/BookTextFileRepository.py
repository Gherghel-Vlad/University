from Library.domain.book import Book
from Library.repository.BookRepository import BookRepository


class BookTextFileRepositoryException(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class BookTextFileRepository(BookRepository):
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
        book_list = super().book_list

        f = open(self.file_name, "w")
        try:
            for book in book_list:
                book_str = str(book.book_id) + "*" + str(book.title) + "*" + str(book.author) + "\n"
                f.write(book_str)

            f.close()
        except Exception:
            raise BookTextFileRepositoryException(
                "Something went wrong with the writing in the file. Please check that the file is okay.")

    def _load_data(self):
        book_list = []

        try:
            f = open(self.file_name, "r")

            line = f.readline().strip()

            while len(line) > 0:
                line = line.split("*")
                book_list.append(Book(line[0], line[1], line[2]))
                line = f.readline().strip()

            for book in book_list:
                self.add_book(book)

            f.close()
        except FileNotFoundError as e:
            raise FileNotFoundError()
        except IOError as e:
            raise BookTextFileRepositoryException(
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
