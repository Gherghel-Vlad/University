USE MovieShowsDBv2
GO
DELETE FROM Actors
DBCC CHECKIDENT (Actors, RESEED, 0)
DELETE FROM Awards
DBCC CHECKIDENT (Awards, RESEED, 0)

SELECT * FROM Actors
SELECT * FROM Episodes

SELECT * FROM Movies
SELECT * FROM Series
SELECT * FROM Awards
SELECT * FROM Roles
SELECT * FROM Users

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

 -- inserting reviews
 -- game of thrones serie review
 INSERT INTO Reviews(user_id, title, commentary, posted_date, number_of_likes, number_of_dislikes, mark)
 VALUES (1, 'I loved everything about it!', 'Everything was perfect from the start to finish!', '20191212', 102, 102030, 10)
 -- game of thrones episode review
 INSERT INTO Reviews(user_id, title, commentary, posted_date, number_of_likes, number_of_dislikes, mark)
 VALUES (1, 'Best episode by far!', 'The acting, the music, the scenary, everything was a work of art. Congrats to the director for being able to pull something so good!',
 '20181212', 4002, 32, 10)








