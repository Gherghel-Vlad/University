import copy

from Library.data_structures.IterableDataStructure import IterableDataStructure, filter_list
from Library.domain.book import Book


class BookRepositoryException(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class BookRepository:
    def __init__(self):
        self._book_list = IterableDataStructure()

    @property
    def book_list(self):
        """
        Returns the whole list of books
        :return: THe list of books (list of Book objects
        """
        return self._book_list.list

    def add_book(self, book):
        """
        Adds a Book instance to the list of books
        :param book: The instance of the book (Book object)
        :return: -
        Raises BookRepositoryException if it s already in the list
        """
        if self.find(book.book_id) != -1:
            raise BookRepositoryException("There s already a book with the same id " + str(book.book_id))

        self._book_list.append(book)

    def remove_book(self, id_):
        """
        Deletes the book with the given id
        :param id_: The given id of the book to be deleted
        :return: -
        Raises BookRepositoryException if there is no book with the given id
        """
        index = self.find(id_)

        if index == -1:
            raise BookRepositoryException("There s no book with the given id: " + str(id_))

        del self._book_list[index]

    def update_book(self, id_, new_title, new_author):
        """
        Updates the book with the given id
        :param id_: The id that will show which book to be updated
        :param new_title: The new title (leave empty string "" for no modifications)
        :param new_author: The new author's name (leave empty string "" for no modifications)
        :return: -
        Raises exception if the book with the given id does not exist
        Raises exception if the book has already these values
        """
        index = self.find(id_)
        if index == -1:
            raise BookRepositoryException("There s no book with the given id: " + str(id_))
        if self._book_list[index].title == new_title and self._book_list[index].author == new_author:
            raise BookRepositoryException("The book already has these values.")

        if new_title != "":
            self._book_list[index].title = new_title
        if new_author != "":
            self._book_list[index].author = new_author

    def find(self, id_):
        """
        Searches for the index of the Book with the given id
        :param id_: The id of the book
        :return: The index of -1 if it isn't found
        """
        for index in range(0, len(self.book_list)):
            if id_ == self.book_list[index].book_id:
                return index
        return -1

    def find_book(self, id_):
        """
        Searches for the book with the given id
        :param id_: The id of the book
        :return: The book object, or None if it wasnt found
        """
        for index in range(0, len(self.book_list)):
            if id_ == self.book_list[index].book_id:
                return self.book_list[index]
        return None

    def search_books_by_id(self, value):
        """
        Searches if a book id contains the value by doing a substring case-insensitive search
        :param value: The value it searches
        :return: A list containing all the books found
        """
        return filter_list(self.book_list, lambda x: str(value).lower() in str(x.book_id).lower())

    def search_books_by_title(self, value):
        """
        Searches if a book title contains the value by doing a substring case-insensitive search
        :param value: The value it searches
        :return: A list containing all the books found
        """
        return filter_list(self.book_list, lambda x: str(value).lower() in str(x.title).lower())

    def search_books_by_author(self, value):
        """
        Searches if a book author contains the value by doing a substring case-insensitive search
        :param value: The value it searches
        :return: A list containing all the books found
        """
        return filter_list(self.book_list, lambda x: str(value).lower() in str(x.author).lower())

    #
    # def get_title_of_book_id(self, book_id):
    #     """
    #     Get s the title of the instance with the book id given
    #     :param book_id: The book id given (int)
    #     :return: A string representing the title of the book with the given id
    #     Raises exception if the book with the given id does not exist
    #     """
    #     index = self.find(book_id)
    #
    #     if index == -1:
    #         raise BookRepositoryException("There s no book with the given id.")
    #
    #     return str(self.book_list[index].title)
    #
    # def get_author_of_book_id(self, book_id):
    #     """
    #     Get s the title of the instance with the book id given
    #     :param book_id: The book id given (int)
    #     :return: A string representing the title of the book with the given id
    #     Raises exception if the book with the given id does not exist
    #     """
    #     index = self.find(book_id)
    #
    #     if index == -1:
    #         raise BookRepositoryException("There s no book with the given id.")
    #
    #     return str(self.book_list[index].author)

    def __str__(self):
        """
        Creates a string representation of the repository
        :return: A string representation of the repository
        """
        representation = "Library Books: \n"
        for book in self.book_list:
            representation += str(book) + "\n"
        if len(self.book_list) == 0:
            representation += "There are no books yet"
        return representation

    def __len__(self):
        return len(self.book_list)

    def __getitem__(self, id_):
        for book in self._book_list:
            if book.book_id == id_:
                return book
