#include "pch.h"
#include "CppUnitTest.h"
#include "../Local Movie Database/Movie.h"
#include "../Local Movie Database/Movie.cpp"
#include "../Local Movie Database/DynamicVector.h"
#include "../Local Movie Database/MoviesRepository.cpp"
#include "../Local Movie Database/AdministratorService.cpp"
#include "../Local Movie Database/Validators.h"
#include "../Local Movie Database/Validators.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(MovieClassTest)
	{
	public:
		
		TEST_METHOD(getters)
		{
			string title = "Something";
			string genre = "Dark";
			int yearOfRelease = 2002;
			int nrOfLikes = 300;
			string trailer = "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers";
			Movie movie{title, genre, yearOfRelease, nrOfLikes, trailer };

			Assert::AreEqual(title, movie.getTitle());
			Assert::AreEqual(genre, movie.getGenre());
			Assert::AreEqual(yearOfRelease, movie.getYearOfRelease());
			Assert::AreEqual(nrOfLikes, movie.getNumberOfLikes());
			Assert::AreEqual(trailer, movie.getTrailer());
		}

		TEST_METHOD(setters)
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

			Assert::AreEqual(title1, movie.getTitle());
			Assert::AreEqual(genre1, movie.getGenre());
			Assert::AreEqual(yearOfRelease1, movie.getYearOfRelease());
			Assert::AreEqual(nrOfLikes1, movie.getNumberOfLikes());
			Assert::AreEqual(trailer1, movie.getTrailer());

			// testing equality


			Movie mv1{ "asd", "wer", 100, 200, "tre" };
			Movie mv12{ "asd", "wer", 100, 200, "tre" };

			Assert::AreEqual((mv1 == mv12), true);
		}

		TEST_METHOD(toString) {
			string title = "Something";
			string genre = "Dark";
			int yearOfRelease = 2002;
			int nrOfLikes = 300;
			string trailer = "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers";
			Movie movie{ title, genre, yearOfRelease, nrOfLikes, trailer };
			std::stringstream txt;
			txt << "Title: " << title << " Genre: " << genre << " Year of release: " << yearOfRelease << " Number of likes: " << nrOfLikes << " Trailer: " << trailer;

			Assert::AreEqual(movie.toString(), txt.str());

			Movie movie2;
			movie2 = movie;
			Assert::AreEqual((movie == movie2), true);

		}

		TEST_METHOD(equalityAndAssing) {
			string title = "Something";
			string genre = "Dark";
			int yearOfRelease = 2002;
			int nrOfLikes = 300;
			string trailer = "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers";
			Movie movie{ title, genre, yearOfRelease, nrOfLikes, trailer };
			
			Movie movie2;
			movie2 = movie;
			Assert::AreEqual((movie == movie2), true);
		}

	};

	TEST_CLASS(DynamicVectorClass)
	{
	public:
		TEST_METHOD(dynamicVectorCreation) {

			DynamicVector<string> dv1;
			string str1 = "Hello ";
			string str2 = "to ";
			string str3 = "you ";
			string str4 = "world!\n";
			dv1.add("Hello ");
			Assert::AreEqual(dv1.getSize(), 1);
			dv1.add("to ");
			Assert::AreEqual(dv1.getSize(), 2);
			dv1.add("you ");
			Assert::AreEqual(dv1.getSize(), 3);
			dv1.add("world!\n");
			Assert::AreEqual(dv1.getSize(), 4);

			Assert::AreEqual(dv1[0], str1);
			Assert::AreEqual(dv1[1], str2);
			Assert::AreEqual(dv1[2], str3);
			Assert::AreEqual(dv1[3], str4);


			DynamicVector<int> dv2{ 3 };
			dv2.add(6);
			Assert::AreEqual(dv2.getSize(), 1);
			dv2.add(67);
			Assert::AreEqual(dv2.getSize(), 2);
			dv2.add(63);
			Assert::AreEqual(dv2.getSize(), 3);
			dv2.add(61);
			Assert::AreEqual(dv2.getSize(), 4);
			dv2.add(62);
			Assert::AreEqual(dv2.getSize(), 5);

			Assert::AreEqual(dv2[0], 6);
			Assert::AreEqual(dv2[1], 67);
			Assert::AreEqual(dv2[2], 63);
			Assert::AreEqual(dv2[3], 61);
		}

		TEST_METHOD(operatorSquareBrackets) {
			Movie mv1{ "asd", "wer", 100, 200, "tre" };
			Movie mv2{ "asg", "weer", 1500, 2200, "trse" };
			Movie mv3{ "afsd", "wrer", 4100, 2500, "t7re" };
			Movie mv4{ "ahsd", "wder", 1030, 2600, "trge" };

			// operator [] testing and getSize()

			DynamicVector<Movie> dv3{ 2 };
			dv3.add(mv1);
			Assert::AreEqual(dv3.getSize(), 1);
			dv3.add(mv2);
			Assert::AreEqual(dv3.getSize(), 2);
			dv3.add(mv3);
			Assert::AreEqual(dv3.getSize(), 3);
			dv3.add(mv4);
			Assert::AreEqual(dv3.getSize(), 4);

			Assert::AreEqual((dv3[0] == mv1), true);
			Assert::AreEqual((dv3[1] == mv2), true);
			Assert::AreEqual((dv3[2] == mv3), true);
			Assert::AreEqual((dv3[2] == mv2), false);
			Assert::AreEqual((dv3[3] == mv4), true);
		}

		TEST_METHOD(DeleteFunction) {

			Movie mv1{ "asd", "wer", 100, 200, "tre" };
			Movie mv2{ "asg", "weer", 1500, 2200, "trse" };
			Movie mv3{ "afsd", "wrer", 4100, 2500, "t7re" };
			Movie mv4{ "ahsd", "wder", 1030, 2600, "trge" };

			// operator [] testing and getSize()

			DynamicVector<Movie> dv3{ 2 };
			dv3.add(mv1);
			dv3.add(mv2);
			dv3.add(mv3);
			dv3.add(mv4);

			// deleteing elements
			dv3.deleteElementByIndex(0);
			Assert::AreEqual((dv3[0] == mv2), true);
			Assert::AreEqual(dv3.getSize(), 3);

			dv3.deleteElementByIndex(1);
			Assert::AreEqual((dv3[1] == mv4), true);
			Assert::AreEqual(dv3.getSize(), 2);
		}

		TEST_METHOD(updatingElements) {
			Movie mv1{ "asd", "wer", 100, 200, "tre" };
			Movie mv2{ "asg", "weer", 1500, 2200, "trse" };
			Movie mv3{ "afsd", "wrer", 4100, 2500, "t7re" };
			Movie mv4{ "ahsd", "wder", 1030, 2600, "trge" };

			DynamicVector<Movie> dv3{ 2 };
			dv3.add(mv1);
			dv3.add(mv2);
			dv3.add(mv3);
			dv3.add(mv4);

			// testing updating
			Assert::AreEqual((dv3[0] == mv1), true);
			dv3.updateElement(mv2, 0);
			Assert::AreEqual((dv3[0] == mv2), true);
		}

		TEST_METHOD(getIndexOfElement) {

			Movie mv1{ "asd", "wer", 100, 200, "tre" };
			Movie mv2{ "asg", "weer", 1500, 2200, "trse" };
			Movie mv3{ "afsd", "wrer", 4100, 2500, "t7re" };
			Movie mv4{ "ahsd", "wder", 1030, 2600, "trge" };

			DynamicVector<Movie> dv3{ 2 };
			dv3.add(mv1);
			dv3.add(mv3);
			dv3.add(mv4);

			// getting index
			int index = dv3.getIndexOfElement(mv1);
			Assert::AreEqual(index, 0);
			index = dv3.getIndexOfElement(mv4);
			Assert::AreEqual(index, 2);
			index = dv3.getIndexOfElement(mv2);
			Assert::AreEqual(index, -1);
		}

		TEST_METHOD(getAllElements){
			Movie mv1{ "asd", "wer", 100, 200, "tre" };
			Movie mv2{ "asg", "weer", 1500, 2200, "trse" };
			Movie mv3{ "afsd", "wrer", 4100, 2500, "t7re" };
			Movie mv4{ "ahsd", "wder", 1030, 2600, "trge" };

			DynamicVector<Movie> dv3{ 2 };
			dv3.add(mv1);
			dv3.add(mv3);
			dv3.add(mv4);

			// get all elements testing
			Assert::AreEqual((dv3.getAllElements()[0] == dv3[0]), true);

		}
		TEST_METHOD(operatorAssing) {
			Movie mv1{ "asd", "wer", 100, 200, "tre" };
			Movie mv2{ "asg", "weer", 1500, 2200, "trse" };
			Movie mv3{ "afsd", "wrer", 4100, 2500, "t7re" };
			Movie mv4{ "ahsd", "wder", 1030, 2600, "trge" };

			DynamicVector<Movie> dv3{ 2 };
			dv3.add(mv1);
			dv3.add(mv3);
			dv3.add(mv4);


			DynamicVector<Movie> dv1{ 2 };

			dv1 = dv3;

			// get all elements testing
			Assert::AreEqual((dv1[0] == dv3[0]), true);
			Assert::AreEqual((dv1[2] == dv3[2]), true);

		}

		TEST_METHOD(getSize) {
			Movie mv1{ "asd", "wer", 100, 200, "tre" };
			Movie mv2{ "asg", "weer", 1500, 2200, "trse" };
			Movie mv3{ "afsd", "wrer", 4100, 2500, "t7re" };
			Movie mv4{ "ahsd", "wder", 1030, 2600, "trge" };

			DynamicVector<Movie> dv3{ 2 };
			dv3.add(mv1);
			dv3.add(mv3);
			dv3.add(mv4);

			Assert::AreEqual(dv3.getSize(), 3);
		}

	};

	TEST_CLASS(MoviesRepositoryTest)
	{
	public:
		TEST_METHOD(constructors) {
			MoviesRepository mr{};
			mr.addMovie(Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers"));
			mr.addMovie(Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ"));
			mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
			mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
			mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));


			MoviesRepository mr1 = mr;

			Assert::AreEqual((mr.getAllMovies()[0] == mr1.getAllMovies()[0]), true);

		}

		TEST_METHOD(addMovieTest) {
			MoviesRepository mr{};
			Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
			mr.addMovie(m1);
			mr.addMovie(Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ"));
			mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
			mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
			mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));


			Assert::AreEqual((mr.getAllMovies()[0] == m1), true);

		}

		TEST_METHOD(deleteMovieTest) {
			MoviesRepository mr{};
			Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
			Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
			mr.addMovie(m1);
			mr.addMovie(m2);
			mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
			mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
			mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

			mr.deleteMovieByIndex(0);
			Assert::AreEqual((mr.getAllMovies()[0] == m2), true);
		}

		TEST_METHOD(updateMovieTest) {
			MoviesRepository mr{};
			Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
			Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
			mr.addMovie(m1);
			mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
			mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
			mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

			mr.updateMovie(m2, 0);
			Assert::AreEqual((mr.getAllMovies()[0] == m2), true);
		}

		TEST_METHOD(getNumberOfMoviesTest) {
			MoviesRepository mr{};
			Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
			Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
			mr.addMovie(m1);
			mr.addMovie(m2);
			mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
			mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
			mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

			Assert::AreEqual(mr.getNumberOfMovies(), 5);
		}

		TEST_METHOD(getIndexOfMovieTest) {
			MoviesRepository mr{};
			Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
			Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
			mr.addMovie(m1);
			mr.addMovie(m2);
			mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
			mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
			mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

			Assert::AreEqual(mr.getIndexOfMovie(m1), 0);
			Assert::AreEqual(mr.getIndexOfMovie(m2), 1);
		}

		TEST_METHOD(getIndexOfMovieWithTitleTest) {
			MoviesRepository mr{};
			Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
			Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
			mr.addMovie(m1);
			mr.addMovie(m2);
			mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
			mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
			mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

			Assert::AreEqual(mr.getIndexOfMovieWithTitle("Joker"), 1);
			Assert::AreEqual(mr.getIndexOfMovieWithTitle("Joker", 1), -1);
		}

		TEST_METHOD(toStringTest) {
			MoviesRepository mr{};
			Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
			Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
			mr.addMovie(m1);
			mr.addMovie(m2);
			stringstream txt;
			txt << 0 << " " << m1.toString() << '\n';
			txt << 1 << " " << m2.toString() << '\n';


			Assert::AreEqual(txt.str(), mr.toString());

		}
	};

	TEST_CLASS(AdministratorServiceTest) {

	public:
		TEST_METHOD(constructors) {
			MoviesRepository mr{};
			Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
			Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
			mr.addMovie(m1);
			mr.addMovie(m2);
			mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
			mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
			mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

			AdministratorService as(mr);
			AdministratorService as1;

			as1 = mr;

			Assert::AreEqual(as1.getStringRepresentationOfMovies(), as.getStringRepresentationOfMovies());

		}

		TEST_METHOD(addMovieTest) {
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
				Assert::AreEqual(false, true);
			}
			catch(char const* str){
				Assert::AreEqual(true, true);
			}

			as.addMovie(m2);


			try {
				as.addMovie(m2);
				Assert::AreEqual(false, true);
			}
			catch (char const* str) {
				Assert::AreEqual(true, true);
			}

			Movie invalid_movie = Movie("", "", 10, 123, "");

			try {
				as.addMovie(invalid_movie);
				Assert::AreEqual(false, true);
			}
			catch (char const* str) {
				Assert::AreEqual(true, true);
			}

		}

		TEST_METHOD(deleteMovieTesting) {
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
				Assert::AreEqual(false, true);
			}
			catch (char const* str) {
				Assert::AreEqual(true, true);
			}

			try {
				as.deleteMovieFromPosition(9);
				Assert::AreEqual(false, true);
			}
			catch (char const* str) {
				Assert::AreEqual(true, true);
			}

			as.deleteMovieFromPosition(0);


			try {
				as.deleteMovieWithTitle(m1.getTitle());
				Assert::AreEqual(false, true);
			}
			catch (char const* str) {
				Assert::AreEqual(true, true);
			}

			as.addMovie(m1);

			as.deleteMovieWithTitle(m1.getTitle());


			try {
				as.deleteMovieWithTitle(m1.getTitle());
				Assert::AreEqual(false, true);
			}
			catch (char const* str) {
				Assert::AreEqual(true, true);
			}

			Movie invalid_movie = Movie("", "", 10, 123, "");

			try {
				as.deleteMovieWithTitle(invalid_movie.getTitle());
				Assert::AreEqual(false, true);
			}
			catch (char const* str) {
				Assert::AreEqual(true, true);
			}

		}

		TEST_METHOD(updateMovieTests) {
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
				Assert::AreEqual(false, true);
			}
			catch (char const* str) {
				Assert::AreEqual(true, true);
			}

			try {
				as.updateMovieFromPositionn(m1, 3);
				Assert::AreEqual(false, true);
			}
			catch (char const* str) {
				Assert::AreEqual(true, true);
			}


			as.updateMovieFromPositionn(m2, 0);

			try {
				as.updateMovieWithTitle(m2, m1.getTitle());
				Assert::AreEqual(false, true);
			}
			catch (char const* str) {
				Assert::AreEqual(true, true);
			}

			as.updateMovieWithTitle(m1, m2.getTitle());

			try {
				as.updateMovieWithTitle(m1, m2.getTitle());
				Assert::AreEqual(false, true);
			}
			catch (char const* str) {
				Assert::AreEqual(true, true);
			}

			Movie invalid_movie = Movie("", "", 10, 123, "");

			try {
				as.updateMovieWithTitle(invalid_movie, m1.getTitle());
				Assert::AreEqual(false, true);
			}
			catch (char const* str) {
				Assert::AreEqual(true, true);
			}


			try {
				as.updateMovieWithTitle(m1, invalid_movie.getTitle());
				Assert::AreEqual(false, true);
			}
			catch (char const* str) {
				Assert::AreEqual(true, true);
			}


		}
		TEST_METHOD(getStringRepresentationTest) {
			MoviesRepository mr{};
			Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
			Movie m2 = Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ");
			mr.addMovie(m1);
			mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
			mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
			mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));

			AdministratorService as(mr);

			Assert::AreEqual(mr.toString(), as.getStringRepresentationOfMovies());
		}
	};


	TEST_CLASS(ValidatorsTest) {

	public:
		TEST_METHOD(checkTitleTest) {
			Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
			Movie invalid_movie = Movie("", "", 10, -10, "");


			Assert::AreEqual(Validators::checkTitle(m1.getTitle()), true);
			Assert::AreEqual(Validators::checkTitle(invalid_movie.getTitle()), false);
		}

		TEST_METHOD(checkGenreTest) {
			Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
			Movie invalid_movie = Movie("", "", 10, -10, "");


			Assert::AreEqual(Validators::checkGenre(m1.getGenre()), true);
			Assert::AreEqual(Validators::checkGenre(invalid_movie.getGenre()), false);
		}

		TEST_METHOD(checkYearOfReleaseTest) {
			Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
			Movie invalid_movie = Movie("", "", 10, -10, "");


			Assert::AreEqual(Validators::checkYearOfRelease(m1.getYearOfRelease()), true);
			Assert::AreEqual(Validators::checkYearOfRelease(invalid_movie.getYearOfRelease()), false);
		}

		TEST_METHOD(checkNumberOfLikesTest) {
			Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
			Movie invalid_movie = Movie("", "", 10, -10, "");


			Assert::AreEqual(Validators::checkNumberOfLikes(m1.getNumberOfLikes()), true);
			Assert::AreEqual(Validators::checkNumberOfLikes(invalid_movie.getNumberOfLikes()), false);
		}

		TEST_METHOD(checkTrailerTest) {
			Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
			Movie invalid_movie = Movie("", "", 10, -10, "");


			Assert::AreEqual(Validators::checkTrailer(m1.getTrailer()), true);
			Assert::AreEqual(Validators::checkTrailer(invalid_movie.getTrailer()), false);
		}

		TEST_METHOD(checkMovieTest) {
			Movie m1 = Movie("The Dark Knight", "Dark", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers");
			Movie invalid_movie = Movie("", "", 10, -10, "");


			Assert::AreEqual(Validators::checkMovie(m1), true);
			Assert::AreEqual(Validators::checkMovie(invalid_movie), false);
		}

	};

}
