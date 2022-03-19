class PlayerService:
    def __init__(self, players_repo):
        self._players_repo = players_repo

    def player_list_len(self):
        return len(self._players_repo.players_list)

    @property
    def player_list_str(self):
        return str(self._players_repo)

    def eliminate_player_by_id(self, id_):
        """
        Eliminates the player with the given id
        :param id_: The given id
        :return: -
        """
        self._players_repo.delete_player_by_id(id_)

    def increase_strength(self, id_):
        """
        Increases the strength of the player by 1
        :param id_: The id of the player that will have its strength increased
        :return: -
        """
        self._players_repo.increase_strength(id_)

    def start_tournament(self):
        """
        Starts the tournament
        :return: The generator for the tournament
        """
        return self._players_repo.start_tournament()

