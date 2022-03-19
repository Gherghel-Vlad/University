from datetime import datetime

from Library.SQLRepository.SQLHelpers import SQLHelpers
from Library.domain.rental import Rental
from Library.repository.RentalRepository import RentalRepository


class RentalSQLRepository(RentalRepository):
    def __init__(self, database_path):
        super().__init__()
        self._db_path = database_path
        self.select_all_rentals_sql()

    def select_all_rentals_sql(self):
        """
        Creates and returns a list with all the rentals in the table rentals
        :return: A list containing all the rentals
        """
        conn = SQLHelpers.create_connection(self._db_path)

        cur = conn.cursor()
        cur.execute("SELECT * FROM rentals")

        rows = cur.fetchall()

        # i update/copy the list from the table clients into the repo list
        for row in rows:
            if super().find_rental_by_rental_id(row[0]) == -1:
                try:
                    rented_date_ = datetime.strptime(row[3], '%Y-%m-%d %H:%M:%S.%f')
                except ValueError:
                    rented_date_ = datetime.strptime(row[3], '%Y-%m-%d %H:%M:%S')

                if row[4] != None:
                    try:
                        returned_date_ = datetime.strptime(row[4], '%Y-%m-%d %H:%M:%S.%f')
                    except ValueError:
                        returned_date_ = datetime.strptime(row[4], '%Y-%m-%d %H:%M:%S')
                if row[4] != None:
                    super().rent_book(Rental(row[0], row[1], row[2], rented_date_, returned_date_))
                else:
                    super().rent_book(Rental(row[0], row[1], row[2], rented_date_, None))

        conn.close()

    def insert_rental_sql(self, rental):
        """
        Inserts a new rental into the rentals table
        :param conn: The connection to the database
        :param rental: The rental to be inserted
        :return: The id of the row it was inserted into
        """
        conn = SQLHelpers.create_connection(self._db_path)

        sql = ''' INSERT INTO rentals(rental_id,book_id,client_id,rented_date,returned_date)
                  VALUES(?,?,?,?,?) '''

        cur = conn.cursor()
        cur.execute(sql, (rental.rental_id, rental.book_id, rental.client_id, rental.rented_date, rental.returned_date))
        conn.commit()

        conn.close()

        return cur.lastrowid

    def delete_rental_sql(self, id):
        """
        Deletes a rental by rental id
        :param id: id of the rental
        :return: -
        """
        conn = SQLHelpers.create_connection(self._db_path)

        sql = 'DELETE FROM rentals WHERE rental_id=?'

        cur = conn.cursor()
        cur.execute(sql, (id,))
        conn.commit()

        conn.close()

    def update_returned_date_sql(self, id_, returned_date=None):
        """
        Updates the rental's returned date that has that id
        :param id_: The id of the book that s going to be returned (or deleted the returned date)
        :param returned_date: The returned date of the rental (none for removing the returned date)
        :return: -
        """
        conn = SQLHelpers.create_connection(self._db_path)
        if returned_date is not None:
            sql = ''' UPDATE rentals
                      SET returned_date = ?
                      WHERE rental_id = ?'''
            cur = conn.cursor()
            cur.execute(sql, (returned_date, id_))
        else:
            sql = ''' UPDATE rentals
                      SET returned_date = NULL
                      WHERE rental_id = ?'''
            cur = conn.cursor()
            cur.execute(sql, (id_,))
        conn.commit()

        conn.close()

    def rent_book(self, new_rental):
        super().rent_book(new_rental)
        self.insert_rental_sql(new_rental)

    def return_book(self, book_id, returned_date_time_now=None):
        index_rental_id = super().find_not_returned_rental_by_book_id(book_id)
        rental_id = super().rental_list[index_rental_id].rental_id
        if returned_date_time_now is None:
            super().return_book(book_id)
        else:
            super().return_book(book_id, returned_date_time_now)
        self.update_returned_date_sql(rental_id, super().rental_list[index_rental_id].returned_date)

    def delete_by_rental_id(self, rental_id):
        super().delete_by_rental_id(rental_id)
        self.delete_rental_sql(rental_id)

    def remove_returned_date(self, rental_id):
        super().remove_returned_date(rental_id)
        self.update_returned_date_sql(rental_id)
