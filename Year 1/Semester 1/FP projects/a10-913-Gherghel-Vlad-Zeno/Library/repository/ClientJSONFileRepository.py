import json
import jsonpickle
from pathlib import Path

from Library.domain.client import Client
from Library.repository.ClientRepository import ClientRepository


class ClientJSONFileRepositoryException(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class ClientJSONFileRepository(ClientRepository):
    def __init__(self, file_name):
        super().__init__()
        self._file_name = file_name
        # loads the data if it can or creates a new file with that name
        try:
            self._load_data()
        except FileNotFoundError as e:
            f = open(file_name, "w")
            f.close()

    @property
    def file_name(self):
        return self._file_name

    def _save_data(self):
        client_list = super().client_list

        f = open(self.file_name, "w")
        try:
            # json.dump(client_list, f)
            f.write(jsonpickle.encode(client_list))

            f.close()
        except Exception:
            raise ClientJSONFileRepositoryException(
                "Something went wrong with the writing in the file. Please check that the file is okay.")

    def _load_data(self):
        client_list = []

        try:
            f = open(self.file_name, "r")

            client_list = jsonpickle.decode(f.read())

            for client in client_list:
                self.add_client(client)

            f.close()
        except json.decoder.JSONDecodeError as e:
            pass
        except FileNotFoundError as e:
            raise FileNotFoundError()
        except Exception as e:
            raise ClientJSONFileRepositoryException(
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
