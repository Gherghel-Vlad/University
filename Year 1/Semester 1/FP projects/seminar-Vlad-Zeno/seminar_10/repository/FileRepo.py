from seminar_10.repository.Repository import Repository


class FileRepo(Repository):
    def __init__(self, file_name):
        super(FileRepo, self).__init__()
        self._file_name = file_name

    @property
    def file_name(self):
        return self._file_name

    @file_name.setter
    def file_name(self, value):
        self._file_name = value
