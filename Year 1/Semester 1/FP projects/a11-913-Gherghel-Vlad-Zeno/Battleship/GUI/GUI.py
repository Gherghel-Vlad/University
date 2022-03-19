from tkinter import *

from Battleship.Domains.Board import Board
from Battleship.Domains.BoardComputer import BoardComputer
from Battleship.Domains.Options import Options
from Battleship.Domains.Point import Point
from Battleship.Domains.Strategy import Strategy
from Battleship.Service.Game import Game, GameException


class GUI:
    def __init__(self):
        self.ship_value_type = -1
        self.first_coordinate = 0
        self.second_coordinate = 0

    def update_buttons(self):
        # updating the player's board
        for i in range(0, 10):
            for j in range(0, 10):
                if self.board.get(Point(i, j)) in [-1, -2, -3, -4, -5]:
                    self.player_buttons[i * 10 + j].config(bg='blue')
                elif self.board.get(Point(i, j)) == 1:
                    self.player_buttons[i * 10 + j].config(bg='light gray')
                elif self.board.get(Point(i, j)) == 2:
                    self.player_buttons[i * 10 + j].config(bg='red')

        # updating the computer's board
        for i in range(0, 10):
            for j in range(0, 10):
                if self.computer_board.get(Point(i, j)) == 1:
                    self.computer_buttons[i * 10 + j].config(bg='light gray')
                    self.computer_buttons[i * 10 + j].config(state='disabled')
                elif self.computer_board.get(Point(i, j)) == 2:
                    self.computer_buttons[i * 10 + j].config(bg='red')
                    self.computer_buttons[i * 10 + j].config(state='disabled')

    def convert_from_point_to_coordinate(self, point):
        letter_list = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j"]
        number_list = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10"]
        return str(letter_list[point.x]) + str(number_list[point.y])

    def player_shoot(self, x, y):
        string = ""
        try:
            self.game.player_shoot(self.convert_from_point_to_coordinate(Point(x, y)))
        except Exception as e:
            if e == GameException("Lucky bastard... you won..."):
                self.disable_computer_buttons()
                string = "Player: " + str(e) + "\n"
            else:
                string += "Player: " + str(e) + "\n"
        try:
            self.game.computer_shoot()
        except Exception as e:
            if e == GameException("Computer won! Loser :)"):
                self.disable_computer_buttons()
                string = "Computer: " + str(e) + "\n"
            else:
                string += "Computer: " + str(e) + "\n"

        self.update_buttons()
        self.newsLbl["text"] = string

    def place_ship(self, x, y):
        if self.first_coordinate == 0:
            self.first_coordinate = self.convert_from_point_to_coordinate(Point(x, y))
        else:
            self.second_coordinate = self.convert_from_point_to_coordinate(Point(x, y))
            try:
                self.game.set_player_ship(self.first_coordinate, self.second_coordinate, self.ship_value_type)
                self.ship_value_type -= 1
                self.newsLbl['text'] = str(self.placing_ship_message())
                self.update_buttons()
            except Exception as e:
                self.newsLbl['text'] = str(self.placing_ship_message() + "\n" + str(e))
            self.first_coordinate = 0
        if self.ship_value_type == -6:
            self.disable_player_buttons()
            self.enable_computer_buttons()

    def placing_ship_message(self):
        string = "Pick 2 positions from your board so that you place your "
        if self.ship_value_type == -1:
            return string + "destroyer (length of 2 cells)"
        elif self.ship_value_type == -2:
            return string + "destroyer (length of 3 cells)"
        elif self.ship_value_type == -3:
            return string + "destroyer (length of 3 cells)"
        elif self.ship_value_type == -4:
            return string + "destroyer (length of 4 cells)"
        elif self.ship_value_type == -5:
            return string + "destroyer (length of 5 cells)"
        return "Game start! Start shooting at his cells! BEAT HIM!"

    def place_buttons(self):
        lbl = Label(self.game_window, text="Your board", font=("Times New Roman", 16))
        lbl.place(x=150, y=30)

        letter_list = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j"]
        for i in range(0, 10):
            lbl = Label(self.game_window, text=str(letter_list[i]).upper(), font=("Times New Roman", 12), width=3, height=3)
            lbl.place(x=50 + 25 * (i + 1) + 10, y=70, width=30, height=30)

            lbl = Label(self.game_window, text=str(i+1), font=("Times New Roman", 12), width=3, height=3)
            lbl.place(x=55, y=60 + 25 * (i + 1) + 10, width=30, height=30)

        for i in range(0, 10):
            for j in range(0, 10):
                btn = Button(self.game_window, width=2, height=2, command=lambda i1=i, j1=j: self.place_ship(i1, j1))
                self.player_buttons.append(btn)
                btn.place(x=50 + 25 * (i + 1) + 10, y=60 + 25 * (j + 1) + 10, width=30, height=30)

        lbl = Label(self.game_window, text="Computer's board", font=("Times New Roman", 16))
        lbl.place(x=500, y=30)

        for i in range(0, 10):
            lbl = Label(self.game_window, text=str(letter_list[i]).upper(), font=("Times New Roman", 12), width=3, height=3)
            lbl.place(x=425 + 25 * (i + 1) + 10, y=70, width=30, height=30)

            lbl = Label(self.game_window, text=str(i+1), font=("Times New Roman", 12), width=3, height=3)
            lbl.place(x=715, y=60 + 25 * (i + 1) + 10, width=30, height=30)

        for i in range(0, 10):
            for j in range(0, 10):
                btn = Button(self.game_window, width=2, height=2,
                             command=lambda i1=i, j1=j: self.player_shoot(i1, j1))
                self.computer_buttons.append(btn)
                btn.place(x=425 + 25 * (i + 1) + 10, y=60 + 25 * (j + 1) + 10, width=30, height=30)

    def set_ships_phase(self):
        self.newsLbl['text'] = self.placing_ship_message()

    def disable_player_buttons(self):
        for i in range(0, 10):
            for j in range(0, 10):
                self.player_buttons[i * 10 + j].config(state='disabled')

    def enable_computer_buttons(self):
        for i in range(0, 10):
            for j in range(0, 10):
                self.computer_buttons[i * 10 + j].config(state='normal')

    def disable_computer_buttons(self):
        for i in range(0, 10):
            for j in range(0, 10):
                self.computer_buttons[i * 10 + j].config(state='disabled')

    def game_window_start(self, difficulty):
        self.difficulty_window.destroy()
        self.board = Board(10, 10)
        options = Options()
        options.set_difficulty(difficulty)
        strategy = Strategy(options)
        self.computer_board = BoardComputer(10, 10, strategy)
        self.game = Game(self.board, self.computer_board)

        self.game_window = Tk()
        self.player_buttons = []
        self.computer_buttons = []
        pixel = PhotoImage(width=1, height=1)

        self.game_window.title("Battleship (" + str(difficulty) + ")")
        self.game_window.geometry('800x500')
        self.game_window.resizable(False, False)

        # placing the buttons
        self.place_buttons()
        self.newsLbl = Label(self.game_window, text="", font=("Times New Roman", 12), width=60, height=3)
        self.newsLbl.place(x=350, y=420, anchor=CENTER)

        self.disable_computer_buttons()
        # player puts his ships on the board
        self.set_ships_phase()
        self.game_window.mainloop()

    def select_difficulty(self):
        self.start_window.destroy()
        self.difficulty_window = Tk()

        self.difficulty_window.title("Battleship")
        self.difficulty_window.geometry('500x500')
        self.difficulty_window.resizable(False, False)

        btn = Button(self.difficulty_window, text="Easy difficulty", font=("Times New Roman", 20),
                     command=lambda: self.game_window_start("easy"))

        btn.place(relx=0.5, rely=0.3, anchor=CENTER)

        btn = Button(self.difficulty_window, text="Normal difficulty", font=("Times New Roman", 20),
                     command=lambda: self.game_window_start("normal"))

        btn.place(relx=0.5, rely=0.5, anchor=CENTER)

        btn = Button(self.difficulty_window, text="Hard difficulty", font=("Times New Roman", 20),
                     command=lambda: self.game_window_start("hard"))

        btn.place(relx=0.5, rely=0.7, anchor=CENTER)

        self.difficulty_window.mainloop()

    def start_window(self):
        self.start_window = Tk()

        self.start_window.title("Battleship")

        self.start_window.geometry('500x500')
        self.start_window.resizable(False, False)
        lbl = Label(self.start_window, text="Welcome to Battleship game!", font=("Times New Roman", 20))

        lbl.place(relx=0.5, rely=0.4, anchor=CENTER)

        btn = Button(self.start_window, text="Start game", font=("Times New Roman", 20), command=self.select_difficulty)

        btn.place(relx=0.5, rely=0.6, anchor=CENTER)

        self.start_window.mainloop()

# this is how you start it
# gui = GUI()
# gui.start_window()
