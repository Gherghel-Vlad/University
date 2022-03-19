class Repository:
    def __init__(self):
        """
        Initializes a new repo
        :param repo: Repo list
        """
        self._repository = []

    def add(self, item):
        self._repository.append(item)

    def remove(self, _id):
        for item in self._repository[:]:
            if item.id == _id:
                self._repository.remove(item)
                return
        raise ValueError("Doesnt exist")

    def get_all(self):
        return self._repository
