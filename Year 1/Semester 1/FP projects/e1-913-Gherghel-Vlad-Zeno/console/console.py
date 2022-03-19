from services.Game import GameException


class Console:
    def __init__(self, game):
        self._game = game

    def move_snake_ui(self, number):
        self._game.move_snake(int(number))

    def change_direction_ui(self, direction):
        self._game.change_direction(direction)

    def start(self):
        done = False

        command_list = {"move": self.move_snake_ui, "right": self.change_direction_ui, "left": self.change_direction_ui,
                        "up": self.change_direction_ui, "down": self.change_direction_ui}

        while not done:

            print(self._game.get_str_table())

            user_command = input("Give command: ").strip().lower()

            user_command_list = user_command.split(" ")
            try:
                if user_command_list[0] == "move" and len(user_command_list) <= 2 and len(user_command_list) >= 1:
                    number = 1

                    if len(user_command_list) == 2:
                        try:
                            number = int(user_command_list[1])
                        except Exception:
                            raise ValueError("Second argument of move needs to be a number")

                    self.move_snake_ui(number)
                elif user_command_list[0] in ["left", "right", "up", "down"] and len(user_command_list) == 1:
                    self.change_direction_ui(user_command_list[0])
                else:
                    print("Bad command!")
            except GameException as ge:
                if ge.ms == "Game over!" or ge.ms == "Game won!":
                    done = True
                print(ge.ms)
