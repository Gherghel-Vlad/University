from Battleship.Domains.Board import BoardException
from Battleship.Service.Game import GameException


class ConsoleUI:
    def __init__(self, game, options):
        self._game = game
        self._options = options

    def ship_value_type_to_name(self, ship_value_type):
        """
        Transforms the ship type value into it's ship's name
        :param ship_value_type: The ship type value (-1, -2, -3, -4, -5)
        :return: A string that represents the name of that ship
        """
        if ship_value_type == -1:
            return "Destroyer (length of 2 cells)"
        elif ship_value_type == -2:
            return "Submarine (length of 3 cells)"
        elif ship_value_type == -3:
            return "Cruiser (length of 3 cells)"
        elif ship_value_type == -4:
            return "Battleship (length of 4 cells)"
        elif ship_value_type == -5:
            return "Cruiser (length of 5 cells)"
        else:
            raise ValueError("Wrong number")

    def put_player_ship(self, ship_value_type):
        start_coord = input("Please specify where you want " +
                            self.ship_value_type_to_name(ship_value_type) + " to be put.\nStart coordinates: ")
        end_coord = input("End coordinates: ")
        self._game.set_player_ship(start_coord, end_coord, ship_value_type)

    def player_turn(self):
        coordinates = input("Where do you wanna shoot?\n Coordinates (ex: A7, B10): ")
        self._game.player_shoot(coordinates)

    def computer_shoot(self):
        self._game.computer_shoot()

    def print_player_board(self):
        print(self._game.get_player_board_string())

    def print_computer_board(self):
        print(str(self._game.get_computer_board_string()))

    def start(self):
        news = "" # will show what and who hit what

        # first thing: setting the player's ships
        i = 1
        while i < 6:  # there are 5 ships
            self.print_player_board()
            try:
                self.put_player_ship(-i)
                i += 1
            except Exception as val:
                print(val)
        # self._game.set_player_ship("a1", "a2", -1)
        # self._game.set_player_ship("c4", "e4", -2)
        # self._game.set_player_ship("d7", "d9", -3)
        # self._game.set_player_ship("h4", "h7", -4)
        # self._game.set_player_ship("j4", "j8", -5)

        done = False
        news = ""

        while not done:  # starting the actual game
            print("Player board: \n")
            self.print_player_board()
            print("\nComputer board: \n")
            self.print_computer_board()
            print(news)
            news = ""
            try:
                self.player_turn()
            except GameException as val:
                if val == GameException("Invalid coordinates!"):
                    # case in which the user puts invalid coordinates, the computer shouldn't make a move
                    news += "Player: " + val.ms + "\n"
                    continue

                print("Player board: \n")
                self.print_player_board()
                print("\nComputer board: \n")
                self.print_computer_board()
                print(val)
                break
            except BoardException as e:
                try:
                    news += "Player: " + e.ms + "\n"
                    if e == BoardException("Position already hit before! Try again."):
                        continue
                except Exception as e:
                    print(e)
            except Exception as e:
                print(e)

            try:
                self.computer_shoot()
            except GameException as val:
                print("Player board: \n")
                self.print_player_board()
                print("\nComputer board: \n")
                self.print_computer_board()
                print(val)
                break
            except BoardException as e:
                try:
                    news += "Computer: " + e.ms + "\n"
                except Exception as e:
                    print(e)
            except Exception as e:
                print(e)

