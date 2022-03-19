from Battleship.ConsoleUI.UI import ConsoleUI
from Battleship.Domains.Board import Board
from Battleship.Domains.BoardComputer import BoardComputer
from Battleship.Domains.Options import Options
from Battleship.Domains.Strategy import Strategy
from Battleship.GUI.GUI import GUI
from Battleship.Service.Game import Game



done = False

while not done:
    command = input("On what do you want to play?\n1 UI\n2 GUI\nNumber: ")
    command = command.strip().lower()
    if command == "1":
        done = True
        board = Board(10, 10)


        options = Options()

        # setting the options here
        done = False

        while not done:
            difficulty = input("What difficulty would you want? (easy|normal|hard): ")
            difficulty = difficulty.strip().lower()
            try:
                options.set_difficulty(difficulty)
                break
            except Exception as e:
                print(e)


        strategy = Strategy(options)

        computer_board = BoardComputer(10, 10, strategy)

        game = Game(board, computer_board)


        console_ui = ConsoleUI(game, options)
        console_ui.start()
    elif command == "2":
        done = True
        gui = GUI()
        gui.start_window()
    else:
        print("Bad number...")


