#include "Movie.h"
#include "Validators.h"
#include "Tests.h"
#include "MoviesRepository.h"
#include "AdministratorService.h"
#include "UserService.h"
#include <cassert>
#include <sstream>

using namespace std;


void Tests::testMovieClassGetters()
{
	string title = "Something";
	string genre = "Dark";
	int yearOfRelease = 2002;
	int nrOfLikes = 300;
	string trailer = "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers";
	Movie movie{ title, genre, yearOfRelease, nrOfLikes, trailer };

	assert(title == movie.getTitle());
	assert(genre == movie.getGenre());
	assert(yearOfRelease == movie.getYearOfRelease());
	assert(nrOfLikes == movie.getNumberOfLikes());
	assert(trailer == movie.getTrailer());
}

void Tests::testMovieClassSetters()
{
	string title = "Something";
	string genre = "Dark";
	int yearOfRelease = 2002;
	int nrOfLikes = 300;
	string trailer = "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers";
	Movie movie{ title, genre, yearOfRelease, nrOfLikes, trailer };

	string title1 = "Something1";
	string genre1 = "Dark1";
	int yearOfRelease1 = 20012;
	int nrOfLikes1 = 3001;
	string trailer1 = "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers1";

	movie.setTitle(title1);
	movie.setGenre(genre1);
	movie.setYearOfRelease(yearOfRelease1);
	movie.setNumberOfLikes(nrOfLikes1);
	movie.setTrailer(trailer1);

	assert(title1== movie.getTitle());
	assert(genre1== movie.getGenre());
	assert(yearOfRelease1== movie.getYearOfRelease());
	assert(nrOfLikes1== movie.getNumberOfLikes());
	assert(trailer1== movie.getTrailer());

	// testing equality


	Movie mv1{ "asd", "wer", 100, 200, "tre" };
	Movie mv12{ "asd", "wer", 100, 200, "tre" };

	assert(mv1 == mv12);
}

void Tests::testMovieClassToString() {
	string title = "Something";
	string genre = "Dark";
	int yearOfRelease = 2002;
	int nrOfLikes = 300;
	string trailer = "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers";
	Movie movie{ title, genre, yearOfRelease, nrOfLikes, trailer };
	std::stringstream txt;
	txt << "Title: " << title << " Genre: " << genre << " Year of release: " << yearOfRelease << " Number of likes: " << nrOfLikes << " Trailer: " << trailer;

	assert(movie.toString()== txt.str());

	Movie movie2;
	movie2 = movie;
	assert(movie == movie2);

}

void Tests::testMovieClassEqualityAssign() {
	string title = "Something";
	string genre = "Dark";
	int yearOfRelease = 2002;
	int nrOfLikes = 300;
	string trailer = "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers";
	Movie movie{ title, genre, yearOfRelease, nrOfLikes, trailer };

	Movie movie2;
	movie2 = movie;
	assert(movie == movie2);
}


void Tests::testMoviesRepoConstructor() {
	MoviesRepository mr{};
	mr.addMovie(Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ"));
	mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
	mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));


	MoviesRepository mr1 = mr;

	assert(mr.getAllMovies()[0] == mr1.getAllMovies()[0]);

}

void Tests::testMoviesRepoAddMovie() {
	MoviesRepository mr{};
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	mr.addMovie(m1);
	mr.addMovie(Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ"));
	mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
	mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));


	assert(mr.getAllMovies()[0] == m1);

}

void Tests::testMoviesRepoDeleteMovie() {
	MoviesRepository mr{};
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
	mr.addMovie(m1);
	mr.addMovie(m2);
	mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
	mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

	mr.deleteMovieByIndex(0);
	assert(mr.getAllMovies()[0] == m2);
}

void Tests::testMoviesRepoUpdate() {
	MoviesRepository mr{};
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
	mr.addMovie(m1);
	mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
	mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

	mr.updateMovie(m2, 0);
	assert(mr.getAllMovies()[0] == m2);
}

void Tests::testMoviesRepoGetNumberOfMovies() {
	MoviesRepository mr{};
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
	mr.addMovie(m1);
	mr.addMovie(m2);
	mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
	mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

	assert(mr.getNumberOfMovies()== 5);
}

void Tests::testMoviesRepoGetIndexOfMovie() {
	MoviesRepository mr{};
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
	mr.addMovie(m1);
	mr.addMovie(m2);
	mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
	mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

	assert(mr.getIndexOfMovie(m1)== 0);
	assert(mr.getIndexOfMovie(m2)== 1);
}

void Tests::testMoviesRepoGetIndexOfMovieWithTitle() {
	MoviesRepository mr{};
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
	mr.addMovie(m1);
	mr.addMovie(m2);
	mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
	mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

	assert(mr.getIndexOfMovieWithTitle("Joker")== 1);
	assert(mr.getIndexOfMovieWithTitle("Joker", 1)== -1);
}

void Tests::testMoviesRepoToString() {
	MoviesRepository mr{};
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
	mr.addMovie(m1);
	mr.addMovie(m2);
	stringstream txt;
	txt << 0 << " " << m1.toString() << '\n';
	txt << 1 << " " << m2.toString() << '\n';


	assert(txt.str()== mr.toString());
}

void Tests::testAdministratorServiceConstructor() {
	MoviesRepository mr{};
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
	mr.addMovie(m1);
	mr.addMovie(m2);
	mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
	mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

	AdministratorService as(mr);


}

void Tests::testAdministratorServiceAddMovie() {
	MoviesRepository mr{};
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
	mr.addMovie(m1);
	mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
	mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

	AdministratorService as(mr);

	try {
		as.addMovie(m1);
		assert(false== true);
	}
	catch (char const* str) {
		assert(true== true);
	}

	as.addMovie(m2);


	try {
		as.addMovie(m2);
		assert(false== true);
	}
	catch (char const* str) {
		assert(true== true);
	}

	Movie invalid_movie = Movie("", "", 10, 123, "");

	try {
		as.addMovie(invalid_movie);
		assert(false== true);
	}
	catch (char const* str) {
		assert(true== true);
	}

}

void Tests::testAdministratorServiceDeleteMovie() {
	MoviesRepository mr{};
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
	mr.addMovie(m1);
	mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
	mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

	AdministratorService as(mr);

	try {
		as.deleteMovieWithTitle(m2.getTitle());
		assert(false== true);
	}
	catch (char const* str) {
		assert(true== true);
	}

	try {
		as.deleteMovieFromPosition(9);
		assert(false== true);
	}
	catch (char const* str) {
		assert(true== true);
	}

	as.deleteMovieFromPosition(0);


	try {
		as.deleteMovieWithTitle(m1.getTitle());
		assert(false== true);
	}
	catch (char const* str) {
		assert(true== true);
	}

	as.addMovie(m1);

	as.deleteMovieWithTitle(m1.getTitle());


	try {
		as.deleteMovieWithTitle(m1.getTitle());
		assert(false== true);
	}
	catch (char const* str) {
		assert(true== true);
	}

	Movie invalid_movie = Movie("", "", 10, 123, "");

	try {
		as.deleteMovieWithTitle(invalid_movie.getTitle());
		assert(false== true);
	}
	catch (char const* str) {
		assert(true== true);
	}

}

void Tests::testAdministratorServiceUpdateMovie() {
	MoviesRepository mr{};
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
	mr.addMovie(m1);
	mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
	mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

	AdministratorService as(mr);

	try {
		as.updateMovieWithTitle(m1, m2.getTitle());
		assert(false== true);
	}
	catch (char const* str) {
		assert(true== true);
	}

	try {
		as.updateMovieFromPositionn(m1, 3);
		assert(false== true);
	}
	catch (char const* str) {
		assert(true== true);
	}


	as.updateMovieFromPositionn(m2, 0);

	try {
		as.updateMovieWithTitle(m2, m1.getTitle());
		assert(false== true);
	}
	catch (char const* str) {
		assert(true== true);
	}

	as.updateMovieWithTitle(m1, m2.getTitle());

	try {
		as.updateMovieWithTitle(m1, m2.getTitle());
		assert(false== true);
	}
	catch (char const* str) {
		assert(true== true);
	}

	Movie invalid_movie = Movie("", "", 10, 123, "");

	try {
		as.updateMovieWithTitle(invalid_movie, m1.getTitle());
		assert(false== true);
	}
	catch (char const* str) {
		assert(true== true);
	}


	try {
		as.updateMovieWithTitle(m1, invalid_movie.getTitle());
		assert(false== true);
	}
	catch (char const* str) {
		assert(true== true);
	}

	try {
		as.updateMovieFromPositionn(invalid_movie, 1);
		assert(false == true);
	}
	catch (char const* str) {
		assert(true == true);
	}

	try {
		as.updateMovieWithTitle(m1, "Forrest Gump");
		assert(false == true);
	}
	catch (char const* str) {
		assert(true == true);
	}


}
void Tests::testAdministratorServiceGetStringRepresentation() {
	MoviesRepository mr{};
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
	mr.addMovie(m1);
	mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
	mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

	AdministratorService as(mr);

	assert(mr.toString()== as.getStringRepresentationOfMovies());
}




void Tests::testValidatorsCheckTitle() {
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie invalid_movie = Movie("", "", 10, -10, "");


	try {
		Validators::checkTitle(m1.getTitle());
		assert(true);
	}
	catch (ValidatorsException& e) {
		assert(false);
	}

	try {
		Validators::checkTitle(invalid_movie.getTitle());
		assert(false);
	}
	catch (ValidatorsException& e) {
		assert(true);
	}
}

void Tests::testValidatorsCheckGenre() {
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie invalid_movie = Movie("", "", 10, -10, "");

	try {
		Validators::checkGenre(m1.getGenre());
		assert(true);
	}
	catch (ValidatorsException& e) {
		assert(false);
	}

	try {
		Validators::checkGenre(invalid_movie.getGenre());
		assert(false);
	}
	catch (ValidatorsException& e) {
		assert(true);
	}
}

void Tests::testValidatorsCheckYearOfRelease() {
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie invalid_movie = Movie("", "", 10, -10, "");

	try {
		Validators::checkYearOfRelease(m1.getYearOfRelease());
		assert(true);
	}
	catch (ValidatorsException& e) {
		assert(false);
	}

	try {
		Validators::checkYearOfRelease(invalid_movie.getYearOfRelease());
		assert(false);
	}
	catch (ValidatorsException& e) {
		assert(true);
	}
}

void Tests::testValidatorsCheckNumberOfLikes() {
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie invalid_movie = Movie("", "", 10, -10, "");

	try {
		Validators::checkNumberOfLikes(m1.getNumberOfLikes());
		assert(true);
	}
	catch (ValidatorsException& e) {
		assert(false);
	}

	try {
		Validators::checkNumberOfLikes(invalid_movie.getNumberOfLikes());
		assert(false);
	}
	catch (ValidatorsException& e) {
		assert(true);
	}
}

void Tests::testValidatorsCheckTrailer() {
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie invalid_movie = Movie("", "", 10, -10, "");

	try {
		Validators::checkTrailer(m1.getTrailer());
		assert(true);
	}
	catch (ValidatorsException& e) {
		assert(false);
	}

	try {
		Validators::checkTrailer(invalid_movie.getTrailer());
		assert(false);
	}
	catch (ValidatorsException& e) {
		assert(true);
	}
}

void Tests::testValidatorsCheckMovie() {
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie invalid_movie = Movie("", "", 10, -10, "");


	try {
		Validators::checkMovie(m1);
		assert(true);
	}
	catch (ValidatorsException& e) {
		assert(false);
	}

	try {
		Validators::checkMovie(invalid_movie);
		assert(false);
	}
	catch (ValidatorsException& e) {
		assert(true);
	}
}



void Tests::testUserServiceConstructor() {
	MoviesRepository mr{};
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
	mr.addMovie(m1);
	mr.addMovie(m2);
	mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
	mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));
	
	UserService us{ mr };
	UserService us1 = us;
}

void Tests::testUserServiceAddMovieToWatchList() {
	MoviesRepository mr{};
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
	mr.addMovie(m1);
	mr.addMovie(m2);
	mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
	mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

	UserService us{ mr };

	us.addMovieToWatchList(mr.getAllMovies()[0]);

	assert(us.getCurrentMovieToShowToUser("") == m1);

	try {
		us.addMovieToWatchList(mr.getAllMovies()[0]);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

}

void Tests::testUserServiceGetCurrentMovieToShowToUser() {
	MoviesRepository mr{};
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie m2 = Movie("Joker", "Dark, Action", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
	mr.addMovie(m1);
	mr.addMovie(m2);
	mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
	mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

	UserService us{ mr };

	Movie m3 = us.getCurrentMovieToShowToUser("");
	assert(m3 == m1);

	m3 = us.getCurrentMovieToShowToUser("");
	assert(m3 == m2);

	try {
		m3 = us.getCurrentMovieToShowToUser("asdwafdsaf");
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	MoviesRepository mr1{};
	mr1.addMovie(m1);
	mr1.addMovie(m2);
	UserService us1{ mr1 };


	m3 = us1.getCurrentMovieToShowToUser("Action");
	assert(m3 == m2);

	m3 = us1.getCurrentMovieToShowToUser("");
	assert(m3 == m1);

	us1.restartFromStart();

	m3 = us1.getCurrentMovieToShowToUser("");
	assert(m3 == m1);


}

void Tests::testUserServiceDeleteFromWatchlist() {

	MoviesRepository mr{};
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
	mr.addMovie(m1);
	mr.addMovie(m2);
	mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
	mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

	UserService us{ mr };

	us.addMovieToWatchList(m1);

	us.deleteMovieFromWatchList(0);

	try {
		us.deleteMovieFromWatchList(0);
		assert(false);
	}
	catch (...)
	{
		assert(true);
	}



	us.addMovieToWatchList(m1);

	us.deleteMovieFromWatchList(0, true);

	assert(mr.getAllMovies()[0].getNumberOfLikes() == 100001);
}

void Tests::testUserServicegetWatchListString() {
	MoviesRepository mr{};
	Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
	Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
	mr.addMovie(m1);
	mr.addMovie(m2);

	UserService us{ mr };
	us.addMovieToWatchList(m1);
	us.addMovieToWatchList(m2);

	std:stringstream txt;
	int i;
	for (i = 0; i < mr.getNumberOfMovies(); i++) {
		txt << i << " " << mr.getAllMovies()[i].toString() << "\n";
	}
	
	assert( txt.str() == us.getWatchListString());

}


void Tests::testUserServiceClass() {
	this->testUserServiceConstructor();
	this->testUserServiceAddMovieToWatchList();
	this->testUserServiceGetCurrentMovieToShowToUser();
	this->testUserServiceDeleteFromWatchlist();
	this->testUserServicegetWatchListString();

}


void Tests::testMovieClass() {
	this->testMovieClassGetters();
	this->testMovieClassSetters();
	this->testMovieClassToString();
	this->testMovieClassEqualityAssign();
}

void Tests::testMoviesRepoClass() {
	this->testMoviesRepoConstructor();
	this->testMoviesRepoAddMovie();
	this->testMoviesRepoDeleteMovie();
	this->testMoviesRepoUpdate();
	this->testMoviesRepoGetIndexOfMovie();
	this->testMoviesRepoGetIndexOfMovieWithTitle();
	this->testMoviesRepoToString();
	this->testMoviesRepoGetNumberOfMovies();
}

void Tests::testAdministratorServiceClass() {
	this->testAdministratorServiceConstructor();
	this->testAdministratorServiceAddMovie();
	this->testAdministratorServiceDeleteMovie();
	this->testAdministratorServiceUpdateMovie();
	this->testAdministratorServiceGetStringRepresentation();
}

void Tests::testValidatorsClass() {
	this->testValidatorsCheckTitle();
	this->testValidatorsCheckGenre();
	this->testValidatorsCheckYearOfRelease();
	this->testValidatorsCheckNumberOfLikes();
	this->testValidatorsCheckTrailer();
	this->testValidatorsCheckMovie();
}


void Tests::testAll() {
	this->testMovieClass();
	this->testMoviesRepoClass();
	this->testAdministratorServiceClass();
	this->testValidatorsClass();
	this->testUserServiceClass();
}

