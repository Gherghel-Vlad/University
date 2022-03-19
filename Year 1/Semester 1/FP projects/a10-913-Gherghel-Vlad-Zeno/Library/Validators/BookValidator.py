from Library.domain.book import Book


class BookValidatorException(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class BookValidator:
    @staticmethod
    def validate_book(book):
        if not isinstance(book, Book):
            raise BookValidatorException("Variable must be instance of Book class.")

        BookValidator.validate_book_id(book.book_id)
        BookValidator.validate_book_title(book.title)
        BookValidator.validate_book_author(book.author)

    @staticmethod
    def validate_book_title(title):
        if not isinstance(title, str):
            raise BookValidatorException("Book title must be string type.")

        if title == "" or len(title) == 0:
            raise BookValidatorException("Book title must not be empty.")

    @staticmethod
    def validate_book_id(id_):
        if not isinstance(id_, str):
            raise BookValidatorException("Book id must be string type.")

        if id_ == "" or len(id_) < 0:
            raise BookValidatorException("Book id incorrect. It must have at least a character.")

    @staticmethod
    def validate_book_author(author):
        if not isinstance(author, str):
            raise BookValidatorException("Book author must be string type.")

        if author == "" or len(author) < 0:
            raise BookValidatorException("Book author incorrect. It must have at least a character.")
