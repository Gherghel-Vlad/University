#pragma once



class Tests {
private:
	void testMovieClassGetters();

	void testMovieClassSetters();

	void testMovieClassToString();

	void testMovieClassEqualityAssign();

	void testMoviesRepoConstructor();

	void testMoviesRepoAddMovie();

	void testMoviesRepoDeleteMovie();

	void testMoviesRepoUpdate();

	void testMoviesRepoGetIndexOfMovie();
	
	void testMoviesRepoGetIndexOfMovieWithTitle();

	void testMoviesRepoToString();

	void testMoviesRepoGetNumberOfMovies();

	void testAdministratorServiceConstructor();

	void testAdministratorServiceAddMovie();

	void testAdministratorServiceDeleteMovie();

	void testAdministratorServiceUpdateMovie();

	void testAdministratorServiceGetStringRepresentation();

	void testValidatorsCheckTitle();

	void testValidatorsCheckGenre();

	void testValidatorsCheckYearOfRelease();

	void testValidatorsCheckNumberOfLikes();

	void testValidatorsCheckTrailer();

	void testValidatorsCheckMovie();

	void testUserServiceConstructor();

	void testUserServiceAddMovieToWatchList();

	void testUserServiceGetCurrentMovieToShowToUser();

	void testUserServiceDeleteFromWatchlist();

	void testUserServicegetWatchListString();

	void testMovieClass();

	void testMoviesRepoClass();

	void testAdministratorServiceClass();

	void testValidatorsClass();

	void testUserServiceClass();
public:
	void testAll();

};