class Player:
    def __init__(self, id, name, player_strength):
        self._id = id
        self._name = name
        self._player_strength = player_strength

    @property
    def id(self):
        return self._id

    @property
    def name(self):
        return self._name

    @property
    def player_strength(self):
        return self._player_strength

    @player_strength.setter
    def player_strength(self, value):
        self._player_strength = value

    def __str__(self):
        return "Id: " + str(self.id) + " Name: " + str(self.name) + " Player strength: " + str(self.player_strength)
