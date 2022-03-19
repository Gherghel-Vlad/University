import pickle

from seminar_10.repository.FileRepo import FileRepo


class ClientTextRepo(FileRepo):
    def __init__(self, file_name):
        super().__init__(file_name)

    def _load_file(self):
        #  def __init__(self, rentalId, start, end, client, car):
        file = open(self.file_name, "rb")

        object_list = []
        object_list = pickle.load(file)
        for obj in object_list:
            self.store(obj)

        file.close()

    def _save_file(self):
        file = open(self.file_name, "wb")

        pickle.dump(self.getAll(), file)

        file.close()
