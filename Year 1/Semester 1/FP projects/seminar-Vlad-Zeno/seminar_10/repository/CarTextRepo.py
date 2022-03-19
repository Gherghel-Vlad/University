from Tools.scripts.ndiff import fopen

from seminar_10.domain.Car import Car
from seminar_10.repository.FileRepo import FileRepo


class CarTextRepo(FileRepo):
    def __init__(self, file_name):
        super().__init__(file_name)

    def _load_file(self):
        file = open(self.file_name, "r")
        for line in file:
            list_strings = line.strip().split(",")
            self.store(Car(list_strings[0], list_strings[1], list_strings[2], list_strings[3]))
        file.close()

    def _save_file(self):
        file = open(self.file_name, "w")
        cars = self.getAll()
        for car in cars:
            file.write(str(car.id) + "," + str(car.license) + "," + str(car.make) + "," + str(car.model))
        file.close()