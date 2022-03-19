

#include <iostream>
#include "Movie.h"
#include "AdministratorService.h"
#include "MoviesRepository.h"
#include "UI.h"
#include "Tests.h"



void addDummyData(MoviesRepository& mr) {
	mr.addMovie(Movie("The Dark Knight", "Dark Action", 2009, 100000, "https://www.youtube.com/watch?v=EXeTwQWrcwY&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Joker", "Dark", 2019, 90000, "https://www.youtube.com/watch?v=-_DJEzZk2pc&ab_channel=FTZ"));
	mr.addMovie(Movie("Forrest Gump", "Heart warming", 1994, 1000000, "https://www.youtube.com/watch?v=bLvqoHBptjg&ab_channel=ParamountMovies"));
	mr.addMovie(Movie("The Green Mile", "Beautiful", 1999, 1010000, "https://www.youtube.com/watch?v=Ki4haFrqSrw&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Zack Snyder's Justice League", "Superhero", 2021, 500000, "https://www.youtube.com/watch?v=vM-Bja2Gy04&ab_channel=HBOMax"));
	mr.addMovie(Movie("Léon: The Professional", "Action", 1994, 1000000, "https://www.youtube.com/watch?v=jawVxq1Iyl0&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("The Shawshank Redemption", "Drama", 1994, 43251, "https://www.youtube.com/watch?v=6hB3S9bIaco&ab_channel=ryy79"));
	mr.addMovie(Movie("Fight Club", "Drama", 1999, 432553, "https://www.youtube.com/watch?v=qtRKdVHc-cE&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("Inception", "Action", 2010, 548483, "https://www.youtube.com/watch?v=YoHD9XEInc0&ab_channel=MovieclipsClassicTrailers"));
	mr.addMovie(Movie("The Matrix", "Sci-Fi, Action", 1999, 800000, "https://www.youtube.com/watch?v=vKQi3bBA1y8&ab_channel=MovieclipsClassicTrailers"));
}

int main() {

	MoviesRepository mr{};
	
	//addDummyData(mr);

	AdministratorService as(mr);

	UserService us(mr);


	UI ui{ as, us };

	ui.startUiFile();


	//cout << mr;
	//mr.writeToFile("movies_list.txt");


	/*Movie mv1 = Movie("The Matrix", "Sci-Fi, Action", 1999, 800000, "https://www.youtube.com/watch?v=vKQi3bBA1y8&ab_channel=MovieclipsClassicTrailers");
	Movie mv2 = Movie("The Matrix", "Sci-Fi, Action", 1999, 800000, "https://www.youtube.com/watch?v=vKQi3bBA1y8&ab_channel=MovieclipsClassicTrailers");

	cout << mv1 << mv2;

	Movie mv3 = Movie{};

	cin >> mv3;

	cout << mv3;*/

	//Tests t;

	//t.testAll();

	return 0;
}

