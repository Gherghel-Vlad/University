import sqlite3
from sqlite3 import Error


def create_connection(db_file):
    """
    Creates/connects to a database
    :param db_file: The path to the database
    :return: A connection to that database (if everything went okay)
    """
    conn = None
    try:
        conn = sqlite3.connect(db_file)
        return conn
    except Error as e:
        print(e)

    return conn


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


def insert_client(conn, client):
    """
    Inserts a new client into the clients table
    :param conn: The connection to the database
    :param client: The client to be inserted
    :return: The id of the row it was inserted into
    """
    sql = ''' INSERT INTO clients(client_id,name)
              VALUES(?,?) '''
    cur = conn.cursor()
    cur.execute(sql, (client.client_id, client.name))
    conn.commit()
    return cur.lastrowid


def insert_book(conn, book):
    """
    Inserts a new book into the books table
    :param conn: The connection to the database
    :param book: The client to be inserted
    :return: The id of the row it was inserted into
    """
    sql = ''' INSERT INTO books(book_id,title,author)
              VALUES(?,?,?) '''
    cur = conn.cursor()
    cur.execute(sql, (book.book_id, book.title, book.author))
    conn.commit()
    return cur.lastrowid

def insert_rental(conn, rental):
    """
    Inserts a new rental into the rentals table
    :param conn: The connection to the database
    :param book: The client to be inserted
    :return: The id of the row it was inserted into
    """
    sql = ''' INSERT INTO rentals(rental_id,book_id,client_id,rented_date,returned_date)
              VALUES(?,?,?) '''
    cur = conn.cursor()
    cur.execute(sql, (book.book_id, book.title, book.author))
    conn.commit()
    return cur.lastrowid


def create_database_and_tables():
    database = "sqlite3db.db"

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
    conn = create_connection(database)

    # creating the tables in the database
    if conn is not None:
        create_table(conn, sql_create_clients_table)
        create_table(conn, sql_create_books_table)
        create_table(conn, sql_create_rentals_table)
    else:
        print("Error! cannot create the database connection.")


def select_task_by_priority(conn):
    """
    Query tasks by priority
    :param conn: the Connection object
    :param priority:
    :return:
    """
    cur = conn.cursor()
    cur.execute("SELECT * FROM clients")

    rows = cur.fetchall()

    for row in rows:
        print(row)


def main1():
    database = "sqlite3db.db"

    # create a database connection
    conn = create_connection(database)
    with conn:

        select_task_by_priority(conn)


if __name__ == '__main__':
    #this function creates only if theres not database or tables with those names
    create_database_and_tables()
    main1()

    s = input("a")
