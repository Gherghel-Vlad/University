from Library.SQLRepository.SQLHelpers import SQLHelpers
from Library.domain.book import Book
from Library.repository.BookRepository import BookRepository


class BookSQLRepository(BookRepository):
    def __init__(self, database_path):
        super().__init__()
        self._db_path = database_path
        self.select_all_books_sql()

    def select_all_books_sql(self):
        """
        Creates and returns a list with all the books in the table books
        :return: A list containing all the books
        """
        conn = SQLHelpers.create_connection(self._db_path)

        cur = conn.cursor()
        cur.execute("SELECT * FROM books")

        rows = cur.fetchall()

        # i update/copy the list from the table clients into the repo list
        for row in rows:
            if super().find(row[0]) == -1:
                super().add_book(Book(row[0], row[1], row[2]))

        conn.close()

    def insert_book_sql(self, book):
        """
        Inserts a new book into the books table
        :param conn: The connection to the database
        :param book: The book to be inserted
        :return: The id of the row it was inserted into
        """
        conn = SQLHelpers.create_connection(self._db_path)

        sql = ''' INSERT INTO books(book_id,title,author)
                  VALUES(?,?,?) '''

        cur = conn.cursor()
        cur.execute(sql, (book.book_id, book.title, book.author))
        conn.commit()

        conn.close()

        return cur.lastrowid

    def delete_book_sql(self, id):
        """
        Deletes a book by book id
        :param id: id of the book
        :return: -
        """
        conn = SQLHelpers.create_connection(self._db_path)

        sql = 'DELETE FROM books WHERE book_id=?'

        cur = conn.cursor()
        cur.execute(sql, (id,))
        conn.commit()

        conn.close()

    def update_book_sql(self, id_, new_title, new_author):
        """
        Updates the book that has that id
        :param id_: The id of the book that s going to be updated
        :param new_title: The new title of the book
        :param new_author: The new author of the book
        :return: -
        """
        conn = SQLHelpers.create_connection(self._db_path)

        sql = ''' UPDATE books
                  SET title = ?,
                    author = ?
                  WHERE book_id = ?'''
        cur = conn.cursor()
        cur.execute(sql, (new_title, new_author, id_))
        conn.commit()

        conn.close()

    def add_book(self, book):
        super().add_book(book)
        self.insert_book_sql(book)

    def remove_book(self, id_):
        super().remove_book(id_)
        self.delete_book_sql(id_)

    def update_book(self, id_, new_title, new_author):
        super().update_book(id_, new_title, new_author)
        self.update_book_sql(id_, new_title, new_author)
