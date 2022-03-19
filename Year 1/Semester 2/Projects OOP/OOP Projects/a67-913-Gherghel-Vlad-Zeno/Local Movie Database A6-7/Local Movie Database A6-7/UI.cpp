
#include "UI.h"
#include <iostream>
#include <cmath>
#include "Validators.h"
#include "CSVFile.h"
#include "HTMLFile.h"
using namespace std;

void UI::printChoiceMenuAtStart() {
	cout << "Log in as: " << endl << "1 Administrator" << endl << "2 User" << endl << "0 Exit" << endl;
}


void UI::printAdministratorMenu() {
	cout << "\nCommands: " << endl;
	cout << "1 Show all movies" << endl;
	cout << "2 Add movie " << endl;
	cout << "3 Delete movie " << endl;
	cout << "4 Update movie " << endl;
	cout << "0 Exit " << endl;
}

void UI::showAllMovies() {
	cout << this->as.getStringRepresentationOfMovies();
}

void UI::addMovie()
{
	string title, genre, trailer;
	int nrOfLikes, yearOfRelease;
	cout << "Title: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, title);
	cout << "Genre: ";
	getline(cin, genre);
	cout << "Year of release: ";
	cin >> yearOfRelease;
	cout << "Number of likes: ";
	cin >> nrOfLikes;
	cout << "Trailer link: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, trailer);

	this->as.addMovie(Movie(title, genre, yearOfRelease, nrOfLikes, trailer));

}

void UI::deleteMovie() {

	int index = -1;
	bool done = false;
	string title;

	char command[10];

	while (!done) {
		cout << "1 Delete by index." << endl << "2 Delete by movie title." << endl << "0 Exit." << endl;
		cout << "Give command: ";
		cin >> command;

		switch (atoi(command))
		{
		case 1:
			cout << "Give index of movie to delete: ";
			cin >> index;
			this->as.deleteMovieFromPosition(index);
			return;
		case 2:
			cout << "Give title of movie to delete: "; 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, title);
			this->as.deleteMovieWithTitle(title);
			return;
		case 0:
			return;
		default:
			cout << "Wrong command" << endl;
			break;
		}
	}



	
}

void UI::updateMovie() {

	int index = -1;
	bool done = false;
	string search_title;
	string title, genre, trailer;
	int nrOfLikes, yearOfRelease;

	char command[10];

	while (!done) {
		cout << "1 Update by index." << endl << "2 Update by movie title." << endl << "0 Exit." << endl;
		cout << "Give command: ";
		cin >> command;

		switch (atoi(command))
		{
		case 1:
			cout << "Give index of movie to update: ";
			cin >> index;

			cout << "Title: ";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, title);
			cout << "Genre: ";
			getline(cin, genre);
			cout << "Year of release: ";
			cin >> yearOfRelease;
			cout << "Number of likes: ";
			cin >> nrOfLikes;
			cout << "Trailer link: ";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, trailer);

			this->as.updateMovieFromPositionn(Movie(title, genre, yearOfRelease, nrOfLikes, trailer), index);
			return;
		case 2:
			cout << "Give title of movie to update: ";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, search_title);

			cout << "Title: ";
			getline(cin, title);
			cout << "Genre: ";
			getline(cin, genre);
			cout << "Year of release: ";
			cin >> yearOfRelease;
			cout << "Number of likes: ";
			cin >> nrOfLikes;
			cout << "Trailer link: ";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, trailer);

			this->as.updateMovieWithTitle(Movie(title, genre, yearOfRelease, nrOfLikes, trailer), search_title);
			return;
		case 0:
			return;
		default:
			cout << "Wrong command" << endl;
			break;
		}
	}


}

void UI::startAdministratorUi() {
	bool done = false;

	char command[10];

	while (!done) {
		this->printAdministratorMenu();
		cout << "Give command: ";
		cin >> command;
		try {
			switch (atoi(command))
			{
			case 1:
				this->showAllMovies();
				break;
			case 2:
				this->addMovie();
				break;
			case 3:
				this->deleteMovie();
				break;
			case 4:
				this->updateMovie();
				break;
			case 0:
				return;
			default:
				cout << "Wrong command" << endl;
				break;
			}
			cout << "Command succesfully executed!\n";
		}
		catch (MoviesRepositoryException& e) {
			cout << "Movies repo error: " << e.what() << endl;
		}
		catch (ValidatorsException& e) {
			cout << "Validator error: " << e.what() << endl;
		}
		catch (AdministratorServiceException& e) {
			cout << "Administrator error: " << e.what() << endl;
		}
		catch (char const* str) {
			cout << str << endl;
		}
		catch (...) {
			cout << "Careful, you are writing some bad input!";

		}

	}



}

void UI::printUserMenu() {
	cout << "\nCommands:";
	cout << "\n1 Show watchlist";
	cout << "\n2 See movies by genre (leave empty for all movies)";
	cout << "\n3 Delete a movie";
	cout << "\n4 Open watch list file";
	cout << "\n0 Exit";
}

void UI::showWatchList() {
	cout << this->us.getWatchListString();
}

void UI::showMovieWatchlistMenu() {
	cout << "\nCommands";
	cout << "\n1 Add movie to watchlist";
	cout << "\n2 Next movie";
	cout << "\n0 Exit";
}


void UI::startLookingForMovies() {

	string genre;
	cout << "Genre to look for (leave empty for all movies): ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, genre);

	bool doneLooking = false;

	Movie movie;
	char command[20];
	std::wstring link;
	while (!doneLooking) {
		movie = this->us.getCurrentMovieToShowToUser(genre);
		system(std::string("start " + movie.getTrailer()).c_str());
		cout << movie.toString();
		this->showMovieWatchlistMenu();
		cout << "\nCommand: ";
		cin >> command;

		try {
			switch (atoi(command)) {
			case 1:
				this->us.addMovieToWatchList(movie);
				break;
			case 2:
				continue;
			case 0:
				return;
			default:
				cout << "Bad command";
				break;
			}
		}
		catch (char const* str) {
			cout << str << endl;
		}
		catch (...) {
			cout << "Sth went wrong!\n";
		}
	}

}

void UI::deleteMovieFromWatchlist() {
	int index;
	bool done = false;
	char command[20];

	while (!done) {
		try {
			cout << "Give index of movie to delete: ";
			cin >> index;
			cout << "Do you want to give the movie a like?\n";
			cout << "1 Yes\n";
			cout << "2 No\n";
			cout << "Give command: ";
			cin >> command;
			
			switch (atoi(command)) {
			case 1:
				this->us.deleteMovieFromWatchList(index, true);
				done = true;
				break;
			case 2:
				this->us.deleteMovieFromWatchList(index, false);
				done = true;
				break;
			default:
				cout << "Wrong command!\n";
				break;
			}

		}
		catch (UserServiceException& e) {
			throw e;
		}
		catch (...) {
			throw exception("Sth went really wrong!");
		}
	}
}


void UI::startUserUi() {
	bool done = false;

	char command[10];

	while (!done) {
		this->printUserMenu();
		cout << "\nGive command: ";
		cin >> command;
		try {
			switch (atoi(command))
			{
			case 1:
				this->showWatchList();
				break;
			case 2:
				this->startLookingForMovies();
				this->us.restartFromStart();
				break;
			case 3:
				this->deleteMovieFromWatchlist();
				break;
			case 4:
				this->us.openFile();
				break;
			case 0:
				this->us.writeToFile();
				return;
			default:
				throw exception("Wrong command!");
			}
			if (atoi(command) != 3) {
				cout << "Command succesfully executed!\n";
			}
		}
		catch (MoviesRepositoryException& e) {
			cout << "Movies repo error: " << e.what() << endl;
		}
		catch (ValidatorsException& e) {
			cout << "Validator error: " << e.what() << endl;
		}
		catch (UserServiceException& e) {
			cout << "User error: " << e.what() << endl;
		}
		catch (char const* str) {
			cout << str << endl;
		}
		catch (...) {
			cout << "Careful, you are writing some bad input!";

		}

	}


}

void UI::startUi() {
	bool done = false;

	char command[10];

	while (!done) {
		this->printChoiceMenuAtStart();

		cout << "\nGive command: ";
		cin >> command;

		switch (atoi(command))
		{
		case 1:
			this->startAdministratorUi();
			break;
		case 2:
			this->startUserUi();
			break;
		case 0:
			return;
		default:
			cout << "Wrong command" << endl;
			break;
		}


	}
}


void UI::printStartUIFileMenu() {

	cout << "Choose to which type of file to save the watch list:" << endl;
	cout << "1 CSV type" << endl;
	cout << "2 HTML type" << endl;
	cout << "0 Exit" << endl;

}


void UI::startUiFile() {
	bool done = false;

	char command[10];

	while (!done) {
		
		this->printStartUIFileMenu();

		cout << "\nGive command: ";
		cin >> command;

		switch (atoi(command))
		{
		case 1:
			this->us.setFile(new CSVFile());
			this->startUi();
			break;
		case 2:
			this->us.setFile(new HTMLFile());
			this->startUi();
			break;
		case 0:
			return;
		default:
			cout << "Wrong command" << endl;
			break;
		}


	}
}

