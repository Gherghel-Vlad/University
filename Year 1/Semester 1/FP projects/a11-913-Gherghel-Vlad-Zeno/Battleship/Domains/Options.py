class OptionsException(Exception):
    def __init__(self, ms):
        super().__init__(ms)


class Options:
    def __init__(self):
        self._max_computer_moves_before_sure_hit = 10
        self._difficulty = "easy"

        # setting the normal values used in the decision making
        self._easy_value_of_moves = 10
        self._normal_value_of_moves = 7
        self._hard_value_of_moves = 3

    @property
    def easy_value_of_moves(self):
        return self._easy_value_of_moves

    @property
    def normal_value_of_moves(self):
        return self._normal_value_of_moves

    @property
    def hard_value_of_moves(self):
        return self._hard_value_of_moves

    @property
    def max_computer_moves_before_sure_hit(self):
        return self._max_computer_moves_before_sure_hit

    @max_computer_moves_before_sure_hit.setter
    def max_computer_moves_before_sure_hit(self, value):
        self._max_computer_moves_before_sure_hit = int(value)

    @property
    def difficulty(self):
        return self._difficulty

    @difficulty.setter
    def difficulty(self, value):
        self._difficulty = value

    def set_difficulty(self, difficulty):
        """
        Sets the maximum number of moves before the computer will surely hit one bsaed on the difficulty name
        easy - 10
        normal - 7
        hard - 5
        :param difficulty: A string from ["easy", "normal", "hard"]
        :return: -
        raises OptionsException if the name of the difficulty is wrong
        """
        difficulty = str(difficulty).lower().strip()

        if difficulty not in ["easy", "normal", "hard"]:
            raise OptionsException("Wrong difficulty parameter! It can be easy, normal or hard only.")

        if difficulty == "hard":
            self.max_computer_moves_before_sure_hit = self.hard_value_of_moves
            self.difficulty = "hard"
        elif difficulty == "normal":
            self.max_computer_moves_before_sure_hit = self.normal_value_of_moves
            self.difficulty = "normal"
        else:
            self.max_computer_moves_before_sure_hit = self.easy_value_of_moves
            self.difficulty = "easy"
