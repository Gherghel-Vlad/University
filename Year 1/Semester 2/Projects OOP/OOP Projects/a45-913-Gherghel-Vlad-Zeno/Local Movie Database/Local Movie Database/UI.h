#pragma once
#include "AdministratorService.h"
#include "Movie.h"
#include "UserService.h"

class UI {
private:
	AdministratorService& as;
	UserService& us;

public:

	UI(AdministratorService& as, UserService& us): us(us), as(as){
	}
	
	void printChoiceMenuAtStart();

	// prints the administrator's menu
	void printAdministratorMenu();

	void showAllMovies();

	void addMovie();

	void deleteMovie();

	void updateMovie();

	void startAdministratorUi();

	void startUserUi();

	void printUserMenu();

	void showWatchList();

	void startLookingForMovies();

	void showMovieWatchlistMenu();

	void deleteMovieFromWatchlist();

	// starts the console ui
	void startUi();




};