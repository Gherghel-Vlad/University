DROP DATABASE MovieShowsDB
GO
CREATE DATABASE MovieShowsDB
GO
USE MovieShowsDB
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
DROP TABLE MovieReviews
DROP TABLE SeriesReviews
DROP TABLE EpisodeReviews

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
	duration TIME,
	budget INT,
	rating INT,
	CONSTRAINT CHK_Movies_Rating CHECK (rating >=0 AND rating <=10),
	CONSTRAINT CHK_Movies_Budget CHECK(budget > 0),
	CONSTRAINT CHK_Movies_Duration CHECK (duration > CONVERT(time, '0'))
)

CREATE TABLE MovieRoles(
	actor_id INT NOT NULL,
	movie_id INT NOT NULL,
	role NVARCHAR(100),
	CONSTRAINT FK_MovieRoles_Actors FOREIGN KEY (actor_id) REFERENCES Actors(actor_id),
	CONSTRAINT FK_MovieRoles_Movies FOREIGN KEY (movie_id) REFERENCES Movies(movie_id),
)

CREATE TABLE Series(
	series_id INT PRIMARY KEY IDENTITY(1,1),
	title NVARCHAR(100) NOT NULL,
	summary NVARCHAR(MAX),
	rating INT,
	start_year SMALLINT NOT NULL,
	end_year SMALLINT DEFAULT NULL,
	CONSTRAINT CHK_Series_Rating CHECK (rating >=0 AND rating <=10)
)

CREATE TABLE Episodes (
	episode_id INT PRIMARY KEY IDENTITY(1,1),
	series_id INT NOT NULL,
	title NVARCHAR(100) NOT NULL,
	summary NVARCHAR(MAX),
	aired_date DATE NOT NULL,
	season_number SMALLINT NOT NULL,
	episode_number SMALLINT NOT NULL,
	rating TINYINT,
	CONSTRAINT FK_Episodes_Series FOREIGN KEY (series_id) REFERENCES Series(series_id),
	CONSTRAINT CHK_Episodes_Rating CHECK (rating >=0 AND rating <=10),
	CONSTRAINT CHK_Episode_Number CHECK (episode_number >= 0),
	CONSTRAINT CHK_Season_Number CHECK (season_number > 0),
	CONSTRAINT CHK_Aired_Date CHECK (aired_date > CONVERT(date, '1905-1-1'))
)

CREATE TABLE EpisodeRoles (
	actor_id INT,
	episode_id INT,
	role NVARCHAR(100),
	CONSTRAINT FK_EpisodeRoles_Actors FOREIGN KEY (actor_id) REFERENCES Actors(actor_id),
	CONSTRAINT FK_EpisodeRoles_Episodes FOREIGN KEY (episode_id) REFERENCES Episodes(episode_id)
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

CREATE TABLE MovieReviews (
	movie_id INT NOT NULL,
	review_id INT NOT NULL,
	PRIMARY KEY (movie_id, review_id),
	CONSTRAINT FK_MovieReviews_Movies FOREIGN KEY (movie_id) REFERENCES Movies(movie_id),
	CONSTRAINT FK_MovieReviews_Reviews FOREIGN KEY (review_id) REFERENCES Reviews(review_id)
)

CREATE TABLE SeriesReviews (
	series_id INT NOT NULL,
	review_id INT NOT NULL,
	PRIMARY KEY (series_id, review_id),
	CONSTRAINT FK_SerieReviews_Series FOREIGN KEY (series_id) REFERENCES Series(series_id),
	CONSTRAINT FK_SerieReviews_Reviews FOREIGN KEY (review_id) REFERENCES Reviews(review_id)
)

CREATE TABLE EpisodeReviews (
	episode_id INT NOT NULL,
	review_id INT NOT NULL,
	PRIMARY KEY (episode_id, review_id),
	CONSTRAINT FK_EpisodeReviews_Episodes FOREIGN KEY (episode_id) REFERENCES Episodes(episode_id),
	CONSTRAINT FK_EpisodeReviews_Reviews FOREIGN KEY (review_id) REFERENCES Reviews(review_id)
)

