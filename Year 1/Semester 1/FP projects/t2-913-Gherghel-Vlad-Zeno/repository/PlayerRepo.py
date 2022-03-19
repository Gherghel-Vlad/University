import copy
import math
import random

from domains.player import Player


class PlayerRepositoryException(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class PlayerRepository:
    def __init__(self, filename):
        self._players_list = []
        self._filename = filename
        self.read_text()
        self.sort_descending_by_strength()
        self._current_position = -1
        self._done_qual = False

    @property
    def players_list(self):
        return self._players_list

    def add_player(self, player):
        self._players_list.append(player)

    def read_text(self):
        player_list = []

        try:
            f = open(self._filename, "r")

            line = f.readline().strip()

            while len(line) > 0:
                line = line.split(",")
                player_list.append(Player(line[0], line[1], line[2]))
                line = f.readline().strip()

            for player in player_list:
                self.add_player(player)

            f.close()
        except FileNotFoundError as e:
            raise FileNotFoundError()
        except IOError as e:
            raise PlayerRepositoryException(
                "File " + str(self._filename) + " could not be opened. Check if everything is alright.")

    def sort_descending_by_strength(self):
        self._players_list.sort(key=lambda x: x.player_strength, reverse=True)

    def find_eliminated_number(self):
        """
        Finds the number of players that need to be eliminated
        :return: A integer representing the number of players that need to be eliminated
        """
        nr = 1

        while nr <= len(self._players_list):
            nr = nr * 2

        return nr / 2

    def delete_player_by_id(self, id_):
        """
        Deletes the player with the given id
        :param id_: the id of the player to be eliminated
        :return: -
        """
        for index in range(0, len(self._players_list)):
            if self._players_list[index].id == id_:
                del self._players_list[index]
                break

    def increase_strength(self, id_):
        """
        Increases the strength of the player by 1
        :param id_: The id of the player that will have its strength increased
        :return: -
        """
        for index in range(0, len(self._players_list)):
            if self._players_list[index].id == id_:
                self._players_list[index].player_strength = str(int(self._players_list[index].player_strength) + 1)
                break

    def start_qualification(self):
        """
        Creates the qualification case of the tournament
        :return: A list of the 2 players that are in a fight
        """
        nr_of_players_to_eliminate = self.find_eliminated_number()

        len_list = len(self._players_list)

        self._current_position += 1

        return [self._players_list[len_list - self._current_position - 1], self._players_list[len_list - self._current_position - 2]]
        #
        # if nr_of_players_to_eliminate != 0:
        #
        # nr_of_players_pairing_needed = nr_of_players_to_eliminate * 2
        #
        # len_list = len(self._players_list)
        #
        # players_list_at_current_stage = copy.deepcopy(self._players_list)
        #
        # for index_players in range(0, nr_of_players_pairing_needed, 2):
        #     yield [players_list_at_current_stage[len_list - index_players],
        #            players_list_at_current_stage[len_list - index_players - 1]]

    def start_tournament(self):
        """
        Starts the tournament (including the qualification if necessary)
        :return: A list of the current 2 players in a fight, or the winner
        """
        done = False
        while len(self._players_list) != 1:
            nr_of_players_to_eliminate = self.find_eliminated_number()

            if nr_of_players_to_eliminate != 0 and self._done_qual == False:
                self.start_qualification()

            self._done_qual = True

            if self._current_position == len(self._players_list) - 1:
                # shuffling the list
                random.shuffle(self._players_list)
                self._current_position = -1

            len_list = len(self._players_list)

            self._current_position += 1
            if len(self._players_list) == 2:
                return [self._players_list[len_list - 1],
                        self._players_list[len_list - 2]]
            else:
                return [self._players_list[len_list - self._current_position - 1],
                        self._players_list[len_list - self._current_position - 2]]

        return [self._players_list[0]]

        # nr_of_players_to_eliminate = self.find_eliminated_number()
        #
        # if nr_of_players_to_eliminate != len(self._players_list):
        #     self.start_qualification()
        #
        # while len(self._players_list) != 1:
        #     # shuffling the list
        #     random.shuffle(self._players_list)
        #
        #     players_list_at_current_stage = copy.deepcopy(self._players_list)
        #
        #     for index_players in range(0, len(players_list_at_current_stage), 2):
        #         yield [[players_list_at_current_stage[index_players], players_list_at_current_stage[index_players + 1]]]

    def __str__(self):
        representation = "Players: \n"
        for player in self._players_list:
            representation += str(player) + "\n"
        if len(self._players_list) == 0:
            representation += "There are no players yet"
        return representation
