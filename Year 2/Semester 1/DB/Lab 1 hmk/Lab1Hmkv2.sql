DROP DATABASE MovieShowsDBv2
GO
CREATE DATABASE MovieShowsDBv2
GO
USE MovieShowsDBv2
GO

DROP TABLE Actors
DROP TABLE Movies
DROP TABLE MovieRoles
DROP TABLE EpisodeRoles
DROP TABLE Episodes
DROP TABLE Series
DROP TABLE Users
DROP TABLE UserReviewLikes
DROP TABLE Reviews
DROP TABLE MSEReviews
DROP TABLE Awards
DROP TABLE Roles

CREATE TABLE Actors (
	actor_id INT PRIMARY KEY IDENTITY(1,1),
	name NVARCHAR(70) NOT NULL,
	bio NVARCHAR(MAX),
	born_date DATE NOT NULL,
	died_date DATE
)


CREATE TABLE Movies (
	movie_id INT PRIMARY KEY IDENTITY(1,1),
	title NVARCHAR(100) NOT NULL,
	genre NVARCHAR (50),
	summary NVARCHAR(MAX),
	release_date DATE NOT NULL,
	duration INT,
	budget INT,
	rating FLOAT,
	CONSTRAINT CHK_Movies_Rating CHECK (rating >=0 AND rating <=10),
	CONSTRAINT CHK_Movies_Budget CHECK(budget > 0),
	CONSTRAINT CHK_Movies_Duration CHECK (duration > 0)
)


CREATE TABLE Series(
	series_id INT PRIMARY KEY IDENTITY(1,1),
	title NVARCHAR(100) NOT NULL,
	summary NVARCHAR(MAX),
	rating FLOAT,
	start_year SMALLINT NOT NULL,
	end_year SMALLINT DEFAULT NULL,
	CONSTRAINT CHK_Series_Rating CHECK (rating >=0 AND rating <=10)
)


CREATE TABLE Awards(
	award_id INT PRIMARY KEY IDENTITY(1,1),
	title NVARCHAR(150) NOT NULL,
	type NVARCHAR(50) NOT NULL,
	year INT NOT NULL,
	actor_id INT DEFAULT NULL,
	movie_id INT DEFAULT NULL,
	series_id INT DEFAULT NULL,
	CONSTRAINT FK_Awards_Actors FOREIGN KEY (actor_id) REFERENCES Actors(actor_id),
	CONSTRAINT FK_Awards_Movies FOREIGN KEY (movie_id) REFERENCES Movies(movie_id),
	CONSTRAINT FK_Awards_Series FOREIGN KEY (series_id) REFERENCES Series(series_id),
	CONSTRAINT CHK_Awards_year CHECK (year > 1900),
	CONSTRAINT CHK_Awards_Only_One_Value CHECK ( 
		(movie_id IS NOT NULL AND series_id IS NULL AND actor_id IS NULL) 
		OR (movie_id IS NULL AND series_id IS NOT NULL AND actor_id IS NULL) 
		OR (movie_id IS NULL AND series_id IS NULL AND actor_id IS NOT NULL) 
	)
)

CREATE TABLE Episodes (
	episode_id INT PRIMARY KEY IDENTITY(1,1),
	series_id INT NOT NULL,
	title NVARCHAR(100) NOT NULL,
	summary NVARCHAR(MAX),
	aired_date DATE NOT NULL,
	season_number SMALLINT NOT NULL,
	episode_number SMALLINT NOT NULL,
	rating FLOAT,
	CONSTRAINT FK_Episodes_Series FOREIGN KEY (series_id) REFERENCES Series(series_id),
	CONSTRAINT CHK_Episodes_Rating CHECK (rating >=0 AND rating <=10),
	CONSTRAINT CHK_Episode_Number CHECK (episode_number >= 0),
	CONSTRAINT CHK_Season_Number CHECK (season_number > 0),
	CONSTRAINT CHK_Aired_Date CHECK (aired_date > CONVERT(date, '1905-1-1'))
)

CREATE TABLE Roles(
	actor_id INT,
	movie_id INT DEFAULT NULL,
	episode_id INT DEFAULT NULL,
	role NVARCHAR(100),
	CONSTRAINT FK_Roles_Actors FOREIGN KEY (actor_id) REFERENCES Actors(actor_id),
	CONSTRAINT FK_Roles_Movies FOREIGN KEY (movie_id) REFERENCES Movies(movie_id),
	CONSTRAINT FK_Roles_Episodes FOREIGN KEY (episode_id) REFERENCES Episodes(episode_id),
	CONSTRAINT CHK_Roles_One_Column_Value CHECK (
		(movie_id IS NOT NULL AND episode_id IS NULL)
		OR (movie_id IS NULL AND episode_id IS NOT NULL)
	)
)

CREATE TABLE Users (
	user_id INT PRIMARY KEY IDENTITY(1,1),
	name NVARCHAR(70) NOT NULL,
	email NVARCHAR(100) NOT NULL,
	joined_date DATE NOT NULL,
	description NVARCHAR(256)
)

CREATE TABLE Reviews (
	review_id INT PRIMARY KEY IDENTITY(1,1),
	user_id INT NOT NULL,
	title NVARCHAR(100) NOT NULL,
	commentary NVARCHAR(MAX),
	posted_date DATE NOT NULL,
	number_of_likes INT DEFAULT 0,
	number_of_dislikes INT DEFAULT 0,
	mark TINYINT NOT NULL,
	CONSTRAINT CHK_Reviews_Mark CHECK (mark >=0 AND mark <= 10),
	CONSTRAINT FK_Reviews_Users FOREIGN KEY (user_id) REFERENCES Users(user_id),
	CONSTRAINT CHK_Reviews_Likes CHECK (number_of_likes >= 0 AND number_of_dislikes >= 0)
)

CREATE TABLE UserReviewLikes (
	user_id INT NOT NULL,
	review_id INT NOT NULL,
	liked BIT NOT NULL, 
	PRIMARY KEY (user_id, review_id),
	CONSTRAINT FK_UserReviewLikes_Users FOREIGN KEY (user_id) REFERENCES Users(user_id),
	CONSTRAINT FK_UserReviewLikes_Reviews FOREIGN KEY (review_id) REFERENCES Reviews(review_id),
)

CREATE TABLE MSEReviews(
	review_id INT NOT NULL,
	movie_id INT DEFAULT NULL,
	episode_id INT DEFAULT NULL,
	series_id INT DEFAULT NULL,
	CONSTRAINT FK_MSEReviews_Reviews FOREIGN KEY (review_id) REFERENCES Reviews(review_id),
	CONSTRAINT FK_MSEReviews_Movies FOREIGN KEY (movie_id) REFERENCES Movies(movie_id),
	CONSTRAINT FK_MSEReviews_Series FOREIGN KEY (series_id) REFERENCES Series(series_id),
	CONSTRAINT FK_MSEReviews_Episodes FOREIGN KEY (episode_id) REFERENCES Episodes(episode_id),
	CONSTRAINT CHK_MSEReviews_Only_One_Value CHECK ( 
		(movie_id IS NOT NULL AND series_id IS NULL AND episode_id IS NULL) 
		OR (movie_id IS NULL AND series_id IS NOT NULL AND episode_id IS NULL) 
		OR (movie_id IS NULL AND series_id IS NULL AND episode_id IS NOT NULL) 
	)
)
