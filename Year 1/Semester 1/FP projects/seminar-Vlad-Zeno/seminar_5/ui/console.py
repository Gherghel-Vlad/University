from seminar_5.services.shelter import Shelter


class ShelterUI:
    def __init__(self):
        self._shelter = Shelter()

    def start(self):
        """
        Handle main ui look here
        :return:
        """
        pass


cat_shelter = ShelterUI()
cat_shelter.start()