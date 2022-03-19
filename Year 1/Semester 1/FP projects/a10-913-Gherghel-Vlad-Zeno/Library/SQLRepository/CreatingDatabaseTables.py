import sqlite3
from sqlite3 import Error

from Library.SQLRepository.SQLHelpers import SQLHelpers


def create_table(conn, create_table_sql):
    """
    Creates a table with the given statement
    :param conn: The connection to the database
    :param create_table_sql: The statement to create a table
    :return: -
    """
    try:
        c = conn.cursor()
        c.execute(create_table_sql)
    except Error as e:
        print(e)


def create_database_and_tables(db_path):
    database = db_path

    sql_create_clients_table = """ CREATE TABLE IF NOT EXISTS clients (
                                            client_id text PRIMARY KEY,
                                            name text NOT NULL
                                        ); """

    sql_create_books_table = """CREATE TABLE IF NOT EXISTS books (
                                        book_id text PRIMARY KEY,
                                        title text NOT NULL,
                                        author text NOT NULL
                                    );"""

    sql_create_rentals_table = """CREATE TABLE IF NOT EXISTS rentals (
                                        rental_id text PRIMARY KEY,
                                        book_id text NOT NULL,
                                        client_id text NOT NULL,
                                        rented_date text NOT NULL,
                                        returned_date text NULL
                                    );"""

    # create a database connection
    conn = SQLHelpers.create_connection(database)

    # creating the tables in the database
    if conn is not None:
        create_table(conn, sql_create_clients_table)
        create_table(conn, sql_create_books_table)
        create_table(conn, sql_create_rentals_table)
    else:
        print("Error! cannot create the database connection.")


#if __name__ == '__main__':
# this function creates only if theres not database or tables with those names
# uncomment if you want to redo all the database and tables
# create_database_and_tables("name.db")
