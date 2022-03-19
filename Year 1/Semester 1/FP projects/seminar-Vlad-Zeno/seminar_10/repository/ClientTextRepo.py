from Tools.scripts.ndiff import fopen

from seminar_10.domain.Client import Client
from seminar_10.repository.FileRepo import FileRepo


class ClientTextRepo(FileRepo):
    def __init__(self, file_name):
        super().__init__(file_name)

    def _load_file(self):
        file = open(self.file_name, "r")
        for line in file:
            list_strings = line.strip().split(",")
            self.store(Client(list_strings[0], list_strings[1], list_strings[2]))
        file.close()

    def _save_file(self):
        file = open(self.file_name, "w")
        clients = self.getAll()
        for client in clients:
            file.write(str(client.id) + "," + str(client.cnp) + "," + str(client.name))
        file.close()