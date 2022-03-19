USE MovieShowsDBv2
GO
DELETE FROM MSEReviews
DELETE FROM Roles
DELETE FROM UserReviewLikes
DELETE FROM Awards
DBCC CHECKIDENT (Awards, RESEED, 0)
DELETE FROM Episodes
DBCC CHECKIDENT (Episodes, RESEED, 0)
DELETE FROM Users
DBCC CHECKIDENT (Users, RESEED, 0)
DELETE FROM Reviews
DBCC CHECKIDENT (Reviews, RESEED, 0)
DELETE FROM Movies
DBCC CHECKIDENT (Movies, RESEED, 0)
DELETE FROM Series
DBCC CHECKIDENT (Series, RESEED, 0)
DELETE FROM Actors
DBCC CHECKIDENT (Actors, RESEED, 0)

SELECT * FROM Actors
SELECT * FROM Episodes
SELECT * FROM Reviews
SELECT * FROM Movies

SELECT * FROM Movies
SELECT * FROM Series
SELECT * FROM Awards
SELECT * FROM Roles
SELECT * FROM Users
SELECT * FROM Reviews
SELECT * FROM UserReviewLikes
SELECT * FROM MSEReviews

-- insert into actors values
INSERT INTO Actors(name, bio, born_date) VALUES ('Tom Hanks', 'One of the best actors.', '19560709')
INSERT INTO Actors(name, bio, born_date) VALUES ('Peter Dinklage', 'He kinda short, but he''s really good.', '19690611')
INSERT INTO Actors(name, bio, born_date) VALUES ('Patrick Stewart', 'He bald.', '19400713')
INSERT INTO Actors(name, bio, born_date) VALUES ('Kit Harington', 'He''s really good for a young actor.', '19861226')
INSERT INTO Actors(name, bio, born_date) VALUES ('Joaquin Phoenix', 'He really deliveres in his acting.', '19741029')
INSERT INTO Actors(name, bio, born_date, died_date) VALUES ('Paul Walker', 'He died too young for what he had to offer...', '19730912', '20131030')
INSERT INTO Actors(name, bio, born_date, died_date) VALUES ('Heath Ledger', 'He played his role too good...', '19790404', '20080122')
INSERT INTO Actors(name, bio, born_date) VALUES ('Emilia Clarke', 'Beautiful and talented.', '19861023')
INSERT INTO Actors(name, bio, born_date) VALUES ('Sophie Turner', 'What can you ask for more?', '19960221')

-- inserting movies

INSERT INTO Movies(title, genre, summary, release_date, duration, budget, rating) 
VALUES ('Forrest Gump', 'Drama;Romance', 'The presidencies of Kennedy and Johnson, the Vietnam War, the Watergate scandal and other historical events unfold from the perspective of an Alabama man with an IQ of 75, whose only desire is to be reunited with his childhood sweetheart.',
 '19940706', 144, 55000000, 8.8)
INSERT INTO Movies(title, genre, summary, release_date, duration, budget, rating) 
VALUES ('X-Men: Days of Future Past', 'Action;Adventure;Sci-Fi', 'The X-Men send Wolverine to the past in a desperate effort to change history and prevent an event that results in doom for both humans and mutants.',
 '20140523', 132, 200000000, 7.9)
INSERT INTO Movies(title, genre, summary, release_date, duration, budget, rating) 
VALUES ('The Fast and the Furious', 'Action;Crime;Thriller', 'Los Angeles police officer Brian O''Conner must decide where his loyalty really lies when he becomes enamored with the street racing world he has been sent undercover to destroy.',
 '20010622', 106, 38000000, 6.8)
 INSERT INTO Movies(title, genre, summary, release_date, duration, budget, rating) 
VALUES ('Joker', 'Drama;Crime;Thriller', 'In Gotham City, mentally troubled comedian Arthur Fleck is disregarded and mistreated by society. He then embarks on a downward spiral of revolution and bloody crime. This path brings him face-to-face with his alter-ego: the Joker.',
 '20191004', 122, 55000000, 8.4)
 INSERT INTO Movies(title, genre, summary, release_date, duration, budget, rating)
  VALUES ('The Dark Knight', 'Action;Crime;Drama', 'When the menace known as the Joker wreaks havoc and chaos on the people of Gotham, Batman must accept one of the greatest psychological and physical tests of his ability to fight injustice.',
 '20080718', 152, 185000000,9.0)
 INSERT INTO Movies(title, genre, summary, release_date, duration, budget, rating)
 VALUES ('The Green Mile', 'Crime;Drama;Fantasy', 'The lives of guards on Death Row are affected by one of their charges: a black man accused of child murder and rape, yet who has a mysterious gift.',
 '19991210', 189, 60000000,8.6)
 

 --- inserting series

 INSERT INTO Series(title, summary, rating, start_year, end_year)
 VALUES ('Game of Thrones', 'Nine noble families fight for control over the lands of Westeros, while an ancient enemy returns after being dormant for millennia.', 
 9.2, 2011, 2019)
 INSERT INTO Series(title, summary, rating, start_year, end_year)
 VALUES ('Star Trek: The Next Generation', 'Set almost 100 years after Captain Kirk''s five-year mission, a new generation of Starfleet officers set off in the U.S.S. Enterprise-D on their own mission to go where no one has gone before.', 
 8.6, 1987, 1994)
 INSERT INTO Series(title, summary, rating, start_year, end_year)
 VALUES ('Star Trek: Deep Space Nine', 'In the vicinity of the liberated planet of Bajor, the Federation space station Deep Space Nine guards the opening of a stable wormhole to the far side of the galaxy.', 
 8.0, 1993, 1999)
 INSERT INTO Series(title, summary, rating, start_year, end_year)
 VALUES ('Star Trek: Picard', 'Follow-up series to Star Trek: The Next Generation (1987) and Star Trek: Nemesis (2002) that centers on Jean-Luc Picard (Sir Patrick Stewart) in the next chapter of his life.', 
 7.5, 2020, NULL)

 --- inserting episodes

 INSERT INTO Episodes(series_id, title, summary, aired_date, season_number, episode_number, rating)
 VALUES (1, 'The Winds of Winter', 'Cersei and Loras Tyrell stand trial by the gods. Daenerys prepares to set sail for Westeros. Davos confronts Melisandre. Sam and Gilly arrive in the Citadel. Bran discovers a long-kept secret. Lord Frey has an uninvited guest.',
 '20160626', 6, 10, 9.9)
 INSERT INTO Episodes(series_id, title, summary, aired_date, season_number, episode_number, rating)
 VALUES (1, 'Battle of the Bastards', 'Jon and Sansa face Ramsay Bolton on the fields of Winterfell. Daenerys strikes back at her enemies. Theon and Yara arrive in Meereen.',
 '20160619', 6, 9, 9.9)
  INSERT INTO Episodes(series_id, title, summary, aired_date, season_number, episode_number, rating)
 VALUES (1, 'Winter Is Coming', 'Eddard Stark is torn between his family and an old friend when asked to serve at the side of King Robert Baratheon; Viserys plans to wed his sister to a nomadic warlord in exchange for an army.',
 '20110417', 1, 1, 9.1)
 INSERT INTO Episodes(series_id, title, summary, aired_date, season_number, episode_number, rating)
 VALUES (2, 'The Inner Light', 'Picard awakes to find himself living in a small village where he is a well-known member of the community who is suffering from a delusion of being a starship captain.',
 '19920530', 5, 25, 9.5)
 INSERT INTO Episodes(series_id, title, summary, aired_date, season_number, episode_number, rating)
 VALUES (3, 'In The Pale Moonlight', 'To save the Federation in a critical scheme, Sisko comes to realize that he must violate its fundamental principles to do so.',
 '19980415', 6, 19, 9.5)
  INSERT INTO Episodes(series_id, title, summary, aired_date, season_number, episode_number, rating)
 VALUES (3, 'Remembrance', 'Fourteen years after retiring from Starfleet, Jean-Luc Picard, still haunted by the death of Data, is living a quiet life on his family vineyard when a woman comes to him for help.',
 '20200123', 1, 1, 8.3)
 --- inserting awards
 -- actor awards
 INSERT INTO Awards(title, type, year, actor_id)
 VALUES ('Outstanding Supporting Actor in a Drama Series', 'Winner', 2018, 2)
 INSERT INTO Awards(title, type, year, actor_id)
 VALUES ('Outstanding Television Movie', 'Nominee', 2019, 2)
  INSERT INTO Awards(title, type, year, actor_id)
 VALUES ('Outstanding Supporting Actor in a Drama Series', 'Winner', 2015, 2)
 -- movie awards
 INSERT INTO Awards(title, type, year, movie_id)
 VALUES ('Best Achievement in Cinematography', 'Nominee', 2009, 5)
 INSERT INTO Awards(title, type, year, movie_id)
 VALUES ('Best Achievement in Film Editing', 'Nominee', 2009, 5)
 INSERT INTO Awards(title, type, year, movie_id)
 VALUES ('Best Performance by an Actor in a Supporting Role', 'Winner', 2009, 5)
 -- serie awards
 INSERT INTO Awards(title, type, year, series_id)
 VALUES ('Outstanding Drama Series', 'Winner', 2019, 1)
 INSERT INTO Awards(title, type, year, series_id)
 VALUES ('Outstanding Casting for a Drama Series', 'Winner', 2019, 1)
 INSERT INTO Awards(title, type, year, series_id)
 VALUES ('Outstanding Drama Series', 'Winner', 2018, 1)


 --- inserting roles
 -- movie roles
 INSERT INTO Roles(actor_id, movie_id, role)
 VALUES (1, 1, 'Forest Gump')
  INSERT INTO Roles(actor_id, movie_id, role)
 VALUES (1, 6, 'Paul Edgecomb')
 INSERT INTO Roles(actor_id, movie_id, role)
 VALUES (2, 2, 'Dr. Bolivar Trask')
 INSERT INTO Roles(actor_id, movie_id, role)
 VALUES (3, 2, 'Professor X')
 INSERT INTO Roles(actor_id, movie_id, role)
 VALUES (6, 3, 'Brian O''Conner')
 INSERT INTO Roles(actor_id, movie_id, role)
 VALUES (7, 5, 'Joker')
 INSERT INTO Roles(actor_id, movie_id, role)
 VALUES (5, 4, 'Joker')
 -- serie roles
 INSERT INTO Roles(actor_id, episode_id, role)
 VALUES (2, 1, 'Tyrion Lannister')
 INSERT INTO Roles(actor_id, episode_id, role)
 VALUES (2, 2, 'Tyrion Lannister')
 INSERT INTO Roles(actor_id, episode_id, role)
 VALUES (4, 1, 'Jon Snow')
 INSERT INTO Roles(actor_id, episode_id, role)
 VALUES (4, 3, 'Jon Snow')
 INSERT INTO Roles(actor_id, episode_id, role)
 VALUES (8, 1, 'Daenerys Targaryen')
 INSERT INTO Roles(actor_id, episode_id, role)
 VALUES (9, 3, 'Sansa Stark')
 INSERT INTO Roles(actor_id, episode_id, role)
 VALUES (9, 2, 'Sansa Stark')
 INSERT INTO Roles(actor_id, episode_id, role)
 VALUES (3, 4, 'Jean-Luc Picard')
 INSERT INTO Roles(actor_id, episode_id, role)
 VALUES (3, 5, 'Jean-Luc Picard')
 INSERT INTO Roles(actor_id, episode_id, role)
 VALUES (3, 6, 'Jean-Luc Picard')


 -- inserting users
 INSERT INTO Users(name, email, joined_date, description)
 VALUES ('AnonymousWatcher', 'justasomebody@gmail.com', '20160505', 'I like everything.')
 INSERT INTO Users(name, email, joined_date, description)
 VALUES ('NotAPro42', 'profac@gmail.com', '20180316', 'Hello! How are you?')
 INSERT INTO Users(name, email, joined_date, description)
 VALUES ('ItsAMeMario', 'falsemario@gmail.com', '20200623', 'Sometimes I question who I am...')
 -- this is what i ll delete
 INSERT INTO Users(name, email, joined_date, description)
 VALUES ('qwerty', 'qwerty123@gmail.com', '20210623', 'Haha...')
 INSERT INTO Users(name, email, joined_date, description)
 VALUES ('Gigi', 'alah31@gmail.com', '20190524', 'One and only one!')

 -- inserting reviews
 -- game of thrones serie review
 INSERT INTO Reviews(user_id, title, commentary, posted_date, number_of_likes, number_of_dislikes, mark)
 VALUES (1, 'I loved everything about it!', 'Everything was perfect from the start to finish!', '20191212', 102, 102030, 10)
 -- game of thrones episode review
 INSERT INTO Reviews(user_id, title, commentary, posted_date, number_of_likes, number_of_dislikes, mark)
 VALUES (1, 'Best episode by far!', 'The acting, the music, the scenary, everything was a work of art. Congrats to the director for being able to pull something so good!',
 '20181212', 4002, 32, 10)
 INSERT INTO Reviews(user_id, title, commentary, posted_date, number_of_likes, number_of_dislikes, mark)
 VALUES (2, 'Really loved this ep!', 'This episode doesnt need any comment. Just watch it! :)',
 '20181220', 1032, 12, 10)
 INSERT INTO Reviews(user_id, title, commentary, posted_date, number_of_likes, number_of_dislikes, mark)
 VALUES (1, 'Another beautiful episode!', 'What can i say, i fell in love with this series...',
 '20190820', 4532, 102, 10)
 -- star trek the next generation epsiode reviews
  INSERT INTO Reviews(user_id, title, commentary, posted_date, number_of_likes, number_of_dislikes, mark)
 VALUES (1, 'Haunting episode!', 'I cant say anything, that has not been said before. This episode and that beautifully sad melody, has been in my mind for many, many years.',
 '20200112', 11, 0, 10)
 -- star trek deep space nine epsiode
  INSERT INTO Reviews(user_id, title, commentary, posted_date, number_of_likes, number_of_dislikes, mark)
 VALUES (1, 'Best Episode of DS9... Maybe Best of Any Star Trek!', 'This is my all-time favorite episode, not only of Deep Space Nine, but of Star Trek as a whole. Avery Brooks is an incredible actor, and this episode is proof. And, he plays alongside Andrew Robinson, another stellar actor.',
 '20210608', 3, 0, 10)
 -- star trek picard reviews epsiode
 INSERT INTO Reviews(user_id, title, commentary, posted_date, number_of_likes, number_of_dislikes, mark)
 VALUES (1, 'Better than expected!', 'I only wish they had released all episodes in one day, so I could binge watch it....',
 '20200922', 4832, 132, 9)
 -- inserting movies reviews
 -- forrest gump
INSERT INTO Reviews(user_id, title, commentary, posted_date, number_of_likes, number_of_dislikes, mark)
 VALUES (1, 'Life''s Lessons in one Movie...!', 'When I first saw this movie I didn''t appreciate it like I do now. I think it may have been because I was so young when I first saw it. Just recently I saw the movie again....',
 '20050525', 1000, 124, 10)
 -- Joker (2019)
INSERT INTO Reviews(user_id, title, commentary, posted_date, number_of_likes, number_of_dislikes, mark)
 VALUES (1, 'Yikes. THIS is people''s "best movie ever"?', 'The recurring themes of so many of the 10 star reviews here should tell you a lot about this movie and its audience. If you can''t get through a movie review without tossing in one or more claims...',
 '20200114', 421, 265, 3)
 -- The Green Mile
 INSERT INTO Reviews(user_id, title, commentary, posted_date, number_of_likes, number_of_dislikes, mark)
 VALUES (2, 'Do not live your entire life without seeing this film!!!', 'GREATEST FILM I HAVE EVER SEEN. i remember seeing it when it first came out when i was 12 years old. now i just finished watching it and have gone through practically a whole box of tissues...',
 '20120112', 6500, 8, 10)

 -- inserting user review likes
 INSERT INTO UserReviewLikes(user_id, review_id, liked)
 VALUES (1, 3, 1)
 INSERT INTO UserReviewLikes(user_id, review_id, liked)
 VALUES (1, 1, 1)
 INSERT INTO UserReviewLikes(user_id, review_id, liked)
 VALUES (3, 10, 0)
 INSERT INTO UserReviewLikes(user_id, review_id, liked)
 VALUES (2, 1, 1)
 INSERT INTO UserReviewLikes(user_id, review_id, liked)
 VALUES (3, 1, 0)

 -- inserting MSEReviews
 -- series
 INSERT INTO MSEReviews(review_id, series_id)
 VALUES (1, 1)
 -- episodes
 INSERT INTO MSEReviews(review_id, episode_id)
 VALUES (2, 1)
 INSERT INTO MSEReviews(review_id, episode_id)
 VALUES (3, 1)
 INSERT INTO MSEReviews(review_id, episode_id)
 VALUES (4, 3)
 INSERT INTO MSEReviews(review_id, episode_id)
 VALUES (5, 4)
 INSERT INTO MSEReviews(review_id, episode_id)
 VALUES (6, 5)
 INSERT INTO MSEReviews(review_id, episode_id)
 VALUES (7, 6)
 -- movies
 INSERT INTO MSEReviews(review_id, movie_id)
 VALUES (8, 1)
 INSERT INTO MSEReviews(review_id, movie_id)
 VALUES (9, 4)
 INSERT INTO MSEReviews(review_id, movie_id)
 VALUES (10, 6)

 -- UPDATE data in reviews
 SELECT * FROM Reviews
 UPDATE Reviews
 SET number_of_likes = number_of_likes + 1
 WHERE title LIKE '%Best%'

  UPDATE Reviews
 SET number_of_likes = 6500
 WHERE review_id = 10

 -- update data in movies
 SELECT * FROM Movies

 UPDATE Movies
 SET rating = rating + 0.1
 WHERE rating BETWEEN 5 AND 9


 UPDATE Movies
 SET rating = rating - 0.1
 WHERE rating BETWEEN 5 AND 9.1

 -- update data in actors
 UPDATE Actors
 SET died_date = '20240508'
 WHERE actor_id = 3 AND died_date IS NULL

 UPDATE Actors
 SET died_date = NULL
 WHERE actor_id = 3 

 -- delete data in users
 SELECT * from Users
 DELETE FROM Users
 WHERE user_id IN (4, 5)

 -- delete user review likes
 DELETE FROM UserReviewLikes
 WHERE user_id = 3 AND review_id =10

 --  a. 2 queries with the union operation; use UNION [ALL] and OR;
 SELECT * FROM Reviews

 -- all the reviews that are really disliked or really loved 
 -- UNION
 SELECT R.user_id, R.number_of_likes, R.number_of_dislikes
 FROM Reviews as R
 WHERE R.number_of_dislikes > 10000
 UNION
 SELECT Re.user_id, Re.number_of_likes, Re.number_of_dislikes
 FROM Reviews as Re
 WHERE Re.number_of_likes > 4000

 -- movies that are old or have a really big budget
 -- OR
 SELECT * FROM Movies

 SELECT M.title
 FROM Movies M
 WHERE M.release_date < '20000101' OR M.budget > 100000000

 -- b. 2 queries with the intersection operation; use INTERSECT and IN;
 -- intersect
 -- find the actor ids that played in game of thrones and x men
 SELECT * FROM Movies

 SELECT R.actor_id
 FROM Roles R
 WHERE R.episode_id IN (SELECT E.episode_id FROM Episodes E WHERE E.series_id = 1) -- getting all the episodes from game of thronws
 INTERSECT
 SELECT R.actor_id
 FROM Roles R
 WHERE R.movie_id = 2

 -- in
 -- get all the roles that appeared in more than 2 epsiodes from game of thrones
 SELECT * FROM Roles
  SELECT * FROM Episodes

 SELECT DISTINCT R.role 
 FROM Roles R
 WHERE R.episode_id IN (SELECT E.episode_id FROM Episodes E WHERE E.series_id = 1) AND
		R.actor_id IN (
		 SELECT Ro.actor_id
		 FROM Roles Ro 
		 WHERE Ro.episode_id IN (SELECT E.episode_id FROM Episodes E WHERE E.series_id = 1)
		 GROUP BY Ro.actor_id
		 HAVING COUNT(*) >= 2)

-- c. 2 queries with the difference operation; use EXCEPT and NOT IN;

-- EXCEPT
-- select all the awards for actor id 2 except the ones that are Nominee
SELECT * FROM Awards

SELECT * FROM Awards A
Where A.actor_id = 2
EXCEPT
SELECT * FROM Awards A2
Where A2.actor_id = 2 AND A2.type = 'Nominee'

-- NOT IN
-- select all the movies that didnt get a reward 

SELECT * FROM Movies M
WHERE M.movie_id NOT IN (SELECT DISTINCT A.movie_id FROM Awards A WHERE A.movie_id IS NOT NULL)

-- d. 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN (one query per operator); one query will join at least 3 tables, while another one will join at least two many-to-many relationships;

-- INNER JOIN
-- actors name with movies that played in
SELECT A.name, M.title
FROM Actors A
INNER JOIN Roles R ON R.actor_id = A.actor_id
INNER JOIN Movies M ON M.movie_id = R.movie_id

-- left join (this one unites 2 many to many relations)
-- actors and reviews ids for movies that they participated in
SELECT * FROM MSEReviews
SELECT * FROM Movies

SELECT DISTINCT A.name, R.review_id
FROM Actors A
LEFT JOIN Roles Ro ON Ro.actor_id = A.actor_id
LEFT JOIN Movies M ON M.movie_id = RO.movie_id
LEFT JOIN MSEReviews R ON R.movie_id = M.movie_id


-- right join
-- episodes and the series they are from
SELECT E.title, S.title
FROM Episodes E
RIGHT JOIN Series S ON S.series_id = E.series_id

-- full join
-- reviews to movies
SELECT M.title, R.review_id
FROM Movies M
FULL JOIN MSEReviews R ON R.movie_id = M.movie_id

-- e. 2 queries with the IN operator and a subquery in the WHERE clause; in at least one case, the subquery should include a subquery in its own WHERE clause;

-- all the reviews user 3 liked/disliked
SELECT * FROM UserReviewLikes
SELECT * 
FROM Reviews R
WHERE R.review_id IN (SELECT UR.review_id FROM UserReviewLikes UR WHERE UR.user_id = 3)

-- with 2 subqueries
-- all the awards given to actors that played in game of thrones
SELECT * FROM Awards A
WHERE A.actor_id IN (SELECT R.actor_id FROM Roles R 
						WHERE R.episode_id IN (SELECT E.episode_id FROM Episodes E 
												WHERE E.series_id = 1))


-- f. 2 queries with the EXISTS operator and a subquery in the WHERE clause;

-- select all the series that have won something in 2018
SELECT * FROM Awards

SELECT S.title
FROM Series S
WHERE EXISTS (SELECT * FROM Awards A WHERE A.series_id = S.series_id AND A.year = 2018)

--  select all the users that wrote some reviews and where really disliked ( > 10k)
SELECT * FROM Reviews

SELECT *
FROM Users U
WHERE EXISTS (SELECT * FROM Reviews R WHERE R.user_id = U.user_id AND R.number_of_dislikes > 10000)


-- g. 2 queries with a subquery in the FROM clause;

-- select most recent people born before the 70'
SELECT TOP 2 T.name, T.born_date
FROM (SELECT * FROM Actors A WHERE A.born_date < '19700101') T
ORDER BY T.born_date DESC


-- select top 2 most close to a rating of 8.5
SELECT TOP 2 T.title, T.rating
FROM (SELECT * FROM Movies M WHERE M.rating < 8.5) T
ORDER BY T.rating DESC

-- h. 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 2 of the latter will also have a subquery in the HAVING clause; use the aggregation operators: COUNT, SUM, AVG, MIN, MAX)

-- show all the rewards won by game of thrones in each year
SELECT A.year, COUNT(*)
FROM Awards A
WHERE A.series_id = 1
GROUP BY A.year

-- show all the series with 3 episodes or more
SELECT S.title
FROM Series S
WHERE S.series_id IN (SELECT E.series_id FROM Episodes E WHERE E.series_id = S.series_id GROUP BY E.series_id HAVING COUNT(*) >= 3)

-- show me the movies that had a bigger cast than Forrest Gump
SELECT * FROM Movies

SELECT M.title
FROM Movies M
WHERE M.movie_id in (SELECT R.movie_id FROM Roles R GROUP BY R.movie_id HAVING COUNT(*) > (SELECT COUNT(*) FROM Roles R1 WHERE R1.movie_id = 1))
						
-- show me the users that have more reviews than user 2 number of reviews
 SELECT U.name
 FROM Users U
 WHERE U.user_id in (SELECT R.user_id FROM Reviews R GROUP BY R.user_id HAVING COUNT(*) > (SELECT COUNT(*) FROM Reviews R1 WHERE R1.user_id = 2))


 --i. 4 queries using ANY and ALL to introduce a subquery in the WHERE clause (2 queries per operator); rewrite 2 of them with aggregation operators, and the other 2 with IN / [NOT] IN


 -- ALL
 -- show the movies that had a bigger budget than the ones before the 2000
 SELECT * FROM Movies
 SELECT * FROM Movies M
 WHERE M.budget > ALL (SELECT M2.budget FROM Movies M2  WHERE M2.release_date < '20000101')

 -- rewritten with aggregation operators
  SELECT * FROM Movies M
	WHERE M.budget > (SELECT MAX(M2.budget) FROM Movies M2  WHERE M2.release_date < '20000101')


 -- show the reviews that are way better than the reviews written by user 1
 SELECT * FROM Reviews R
 WHERE R.number_of_likes > ALL (SELECT R1.number_of_likes FROM Reviews R1 WHERE R1.user_id = 1)

 -- rewritten with in
  SELECT * FROM Reviews R
 WHERE R.number_of_likes IN (SELECT R1.number_of_likes FROM Reviews R1 WHERE R1.number_of_likes > (SELECT MAX(R2.number_of_likes) FROM Reviews R2 WHERE R2.user_id =1))

 -- ANY 
 SELECT * FROM Series
 -- show all the reviews of user's 1 that have the mark bigger than any of user's 2 reviews
 SELECT * FROM Reviews R
 WHERE R.user_id = 1 AND R.mark >= ANY (SELECT R1.mark FROM Reviews R1 WHERE R1.user_id = 2)

 -- rewritten with aggregation operators 
 SELECT * FROM Reviews R
 WHERE R.user_id = 1 AND R.mark >= (SELECT MIN(R1.mark) FROM Reviews R1 WHERE R1.user_id = 2)


 -- show the series that have a better rating than all the series from before 95'
 SELECT * FROM Series S
 WHERE S.start_year > 2000 AND S.rating > ANY (SELECT S1.rating FROM Series S1 WHERE S1.start_year < 1995)


 -- rewritten with IN
  SELECT * FROM Series S
 WHERE S.start_year > 2000 AND S.rating IN (SELECT S1.rating FROM Series S1 WHERE S1.start_year >= 1995 AND S1.rating > (SELECT MIN(S2.rating) FROM Series S2 WHERE S2.start_year < 1995))

 



