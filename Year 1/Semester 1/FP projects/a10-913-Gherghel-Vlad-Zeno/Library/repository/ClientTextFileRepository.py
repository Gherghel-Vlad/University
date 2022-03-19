from Library.domain.client import Client
from Library.repository.ClientRepository import ClientRepository


class ClientTextFileRepositoryException(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class ClientTextFileRepository(ClientRepository):
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
        client_list = super().client_list

        f = open(self.file_name, "w")
        try:
            for client in client_list:
                client_str = str(client.client_id) + "*" + str(client.name) + "\n"
                f.write(client_str)

            f.close()
        except Exception:
            raise ClientTextFileRepositoryException(
                "Something went wrong with the writing in the file. Please check that the file is okay.")

    def _load_data(self):
        client_list = []

        try:
            f = open(self.file_name, "r")

            line = f.readline().strip()

            while len(line) > 0:
                line = line.split("*")
                client_list.append(Client(line[0], line[1]))
                line = f.readline().strip()

            for client in client_list:
                self.add_client(client)

            f.close()
        except FileNotFoundError as e:
            raise FileNotFoundError()
        except IOError as e:
            raise ClientTextFileRepositoryException(
                "File " + str(self.file_name) + " could not be opened. Check if everything is alright.")

    def add_client(self, client):
        super().add_client(client)
        self._save_data()

    def remove_client(self, id_):
        super().remove_client(id_)
        self._save_data()

    def update_client(self, id_, new_name):
        super().update_client(id_, new_name)
        self._save_data()
