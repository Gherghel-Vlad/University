class MenuUI:
    def __init__(self, players_service):
        self._player_service = players_service

    def print_players_ui(self):
        print(str(self._player_service.player_list_str))

    def start_tournament_ui(self):
        players = self._player_service.start_tournament()
        while len(players) != 1:
            print("Last " + str(self._player_service.player_list_len()))

            print(str(players[0]) + " vs " + str(players[1]) + "\n")
            print("Who loses? 1 or 2 \n")
            number = input("Number: ")
            if number.strip() == '1':
                self._player_service.eliminate_player_by_id(players[1].id)
                self._player_service.increase_strength(players[0].id)
            else:
                self._player_service.eliminate_player_by_id(players[0].id)
                self._player_service.increase_strength(players[1].id)
            players = self._player_service.start_tournament()

        print("Winner is: " + str(players[0]))

    def start(self):

        self.print_players_ui()

        try:
            self.start_tournament_ui()
        except ValueError as msg:
            print(msg)
