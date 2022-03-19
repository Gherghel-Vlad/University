from repository.PlayerRepo import PlayerRepository
from services.PlayersService import PlayerService
from ui.ui import MenuUI

player_repo = PlayerRepository("players.txt")

player_service = PlayerService(player_repo)

ui = MenuUI(player_service)
ui.start()

