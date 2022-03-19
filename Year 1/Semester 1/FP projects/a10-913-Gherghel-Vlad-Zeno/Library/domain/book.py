class BookException(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class Book:
    def __init__(self, id_book, title, author):
        self._book_id = id_book
        self.title = title
        self.author = author

    @property
    def book_id(self):
        return self._book_id

    @property
    def title(self):
        return self._title

    @property
    def author(self):
        return self._author

    @author.setter
    def author(self, value):
        self._author = value

    @title.setter
    def title(self, value):
        self._title = value

    def __eq__(self, other):
        if not isinstance(other, Book):
            raise BookException("Cannot compare a book with a object of different class.")

        if self.book_id == other.book_id:
            return True
        return False

    def __str__(self):
        """
        :return: A string representation of a book's data
        """
        return "Id: " + str(self._book_id) + " Title: " + str(self.title) + " Author: " + str(self.author)
