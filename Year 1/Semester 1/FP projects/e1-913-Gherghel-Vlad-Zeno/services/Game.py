from domains.Table import TableException


class GameException(Exception):
    def __init__(self, ms):
        super().__init__(ms)
        self._ms = ms

    @property
    def ms(self):
        return self._ms


class Game:
    def __init__(self, table):
        self._table = table

    def move_snake(self, n):
        """
        Moves the snake on the table n positions
        :param n: A integer representing how many positions to move
        :return: -
        raises GameException for invalid move, game over or won
        """
        try:
            self._table.move_snake(int(n))
        except TableException as te:
            raise GameException(te.ms)

    def change_direction(self, direction):
        """
        Changes the direction and moves 1 position in that direction the snake
        :param direction: A string representing the direction (right, left, up, down)
        :return: -
        """
        try:
            self._table.move_direction(str(direction).strip().lower())
        except TableException as te:
            raise GameException(te.ms)

    def get_str_table(self):
        """
        Returns the string representation of the table
        :return: A string representation of the table
        """
        return str(self._table)