from console.console import Console
from domains.Snake import Snake
from domains.Table import Table
from services.Game import Game

snake = Snake()

table = Table(snake)

game = Game(table)

console = Console(game)

console.start()

