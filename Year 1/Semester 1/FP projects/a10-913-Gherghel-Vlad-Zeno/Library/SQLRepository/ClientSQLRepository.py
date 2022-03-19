from Library.SQLRepository.SQLHelpers import SQLHelpers
from Library.domain.client import Client
from Library.repository.ClientRepository import ClientRepository


class ClientSQLRepository(ClientRepository):
    def __init__(self, database_path):
        super().__init__()
        self._db_path = database_path
        self.select_all_clients_sql()

    def select_all_clients_sql(self):
        """
        Creates and returns a list with all the clients in the table clients
        :return: A list containing all the clients
        """
        conn = SQLHelpers.create_connection(self._db_path)

        cur = conn.cursor()
        cur.execute("SELECT * FROM clients")

        rows = cur.fetchall()

        # i update/copy the list from the table clients into the repo list
        for row in rows:
            if super().find(row[0]) == -1:
                super().add_client(Client(row[0], row[1]))

        conn.close()

    def insert_client_sql(self, client):
        """
        Inserts a new client into the clients table
        :param conn: The connection to the database
        :param client: The client to be inserted
        :return: The id of the row it was inserted into
        """
        conn = SQLHelpers.create_connection(self._db_path)

        sql = ''' INSERT INTO clients(client_id,name)
                  VALUES(?,?) '''

        cur = conn.cursor()
        cur.execute(sql, (client.client_id, client.name))
        conn.commit()

        conn.close()

        return cur.lastrowid

    def delete_client_sql(self, id):
        """
        Deletes a client by client id
        :param id: id of the client
        :return: -
        """
        conn = SQLHelpers.create_connection(self._db_path)

        sql = 'DELETE FROM clients WHERE client_id=?'

        cur = conn.cursor()
        cur.execute(sql, (id,))
        conn.commit()

        conn.close()

    def update_client_sql(self, id_, new_name):
        """
        Updates the client that has that id
        :param id_: The id of the client that s going to be updated
        :param new_name: The new name of the client
        :return: -
        """
        conn = SQLHelpers.create_connection(self._db_path)

        sql = ''' UPDATE clients
                  SET name = ? 
                  WHERE client_id = ?'''
        cur = conn.cursor()
        cur.execute(sql, (new_name, id_))
        conn.commit()

        conn.close()

    def add_client(self, client):
        super().add_client(client)
        self.insert_client_sql(client)

    def remove_client(self, id_):
        super().remove_client(id_)
        self.delete_client_sql(id_)

    def update_client(self, id_, new_name):
        super().update_client(id_, new_name)
        self.update_client_sql(id_, new_name)
