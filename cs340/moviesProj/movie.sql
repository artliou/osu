/* Data Definition Queries for Movie Database
Author: Arthur Liou
*/

-- Drop, Create, Use Commands
DROP DATABASE if exists movies;
CREATE DATABASE movies;
USE movies;

/* Tables Definition */
-- Table Structure for Table "Genre"
CREATE TABLE genre (
  genre_id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,
  genre_name varchar(32) NOT NULL
);

-- Table Structure for Table "Producer"
CREATE TABLE producer (
  producer_id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,
  first_name varchar(32) NOT NULL,
  last_name varchar(32) NOT NULL
);

-- Table Structure for Table "Director"
CREATE TABLE director (
  director_id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,
  first_name varchar(32) NOT NULL,
  last_name varchar(32) NOT NULL
);


-- Table Structure for Table "Actor"
CREATE TABLE actor (
  actor_id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,
  first_name varchar(32) NOT NULL,
  last_name varchar(32) NOT NULL
);

-- Table Structure for Table "Movies"
CREATE TABLE movie (
  movie_id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,
  dir_id int,
  prod_id int,
  genre_id int,
  title varchar(255),
  year integer,
  FOREIGN KEY (dir_id) REFERENCES director(director_id),
  FOREIGN KEY (prod_id) REFERENCES producer(producer_id),
  FOREIGN KEY (genre_id) REFERENCES genre(genre_id)
);

-- Table Structure for Table "Movies-Actors"
CREATE TABLE movie_actors (
  cast_credit_id integer NOT NULL PRIMARY KEY AUTO_INCREMENT,
  mov_id int,
  act_id int,
  FOREIGN KEY (mov_id) REFERENCES movie(movie_id),
  FOREIGN KEY (act_id) REFERENCES actor(actor_id)
);

/* Insert Queries for Data Population */
-- Data Source
-- https://en.wikipedia.org/wiki/List_of_Marvel_Cinematic_Universe_films

-- Insert Genres Data
INSERT INTO genre (genre_name) VALUES ('Action'); -- 1
INSERT INTO genre (genre_name) VALUES ('Adventure');
INSERT INTO genre (genre_name) VALUES ('Fantasy');
INSERT INTO genre (genre_name) VALUES ('Thriller');

-- Insert Producer Data
INSERT INTO producer (first_name, last_name) VALUES ('Avi', 'Arad');
INSERT INTO producer (first_name, last_name) VALUES ('Kevin', 'Feige');

-- Insert Director Data
INSERT INTO director (first_name, last_name) VALUES ('Jon', 'Favreau');
INSERT INTO director (first_name, last_name) VALUES ('Kenneth', 'Branagh');
INSERT INTO director (first_name, last_name) VALUES ('Joe', 'Johnston');
INSERT INTO director (first_name, last_name) VALUES ('Joss', 'Whedon');
INSERT INTO director (first_name, last_name) VALUES ('Shane', 'Black'); -- 5
INSERT INTO director (first_name, last_name) VALUES ('Alan', 'Taylor');
INSERT INTO director (first_name, last_name) VALUES ('Anthony', 'Russo');
INSERT INTO director (first_name, last_name) VALUES ('Taika', 'Waititi');
INSERT INTO director (first_name, last_name) VALUES ('Ryan', 'Coogler'); -- 9

-- Insert Actor Data
INSERT INTO actor (first_name, last_name) VALUES ('Robert', 'Downey');
INSERT INTO actor (first_name, last_name) VALUES ('Chris', 'Evans');
INSERT INTO actor (first_name, last_name) VALUES ('Jeremy', 'Renner');
INSERT INTO actor (first_name, last_name) VALUES ('Chris', 'Hemsworth'); -- 4
INSERT INTO actor (first_name, last_name) VALUES ('Samuel', 'Jackson');
INSERT INTO actor (first_name, last_name) VALUES ('Clark', 'Gregg'); -- 6
INSERT INTO actor (first_name, last_name) VALUES ('Scarlett', 'Johansson');
INSERT INTO actor (first_name, last_name) VALUES ('Tom', 'Hiddleston');
INSERT INTO actor (first_name, last_name) VALUES ('Chadwick', 'Boseman'); -- 9

-- Insert Movie Data
-- INSERT INTO movie (title, year) VALUES ('Iron Man', 2008);
INSERT INTO movie (title, year, dir_id, prod_id, genre_id) VALUES ('Iron Man', 2008, 1, 1, 1);
INSERT INTO movie (title, year, dir_id, prod_id, genre_id) VALUES ('Iron Man 2', 2010, 1, 2, 1);
INSERT INTO movie (title, year, dir_id, prod_id, genre_id) VALUES ('Thor', 2011, 2, 2, 4);
INSERT INTO movie (title, year, dir_id, prod_id, genre_id) VALUES ('Captain America: The First Avenger', 2011, 3, 2, 4);
INSERT INTO movie (title, year, dir_id, prod_id, genre_id) VALUES ('The Avengers', 2012, 4, 2, 2); -- 5
INSERT INTO movie (title, year, dir_id, prod_id, genre_id) VALUES ('Iron Man 3', 2013, 5, 2, 1);
INSERT INTO movie (title, year, dir_id, prod_id, genre_id) VALUES ('Thor: The Dark World', 2013, 6, 2, 3);
INSERT INTO movie (title, year, dir_id, prod_id, genre_id) VALUES ('Captain America: The Winter Soldier', 2014, 7, 2, 1);
INSERT INTO movie (title, year, dir_id, prod_id, genre_id) VALUES ('Avengers: Age of Ultron', 2016, 4, 2, 2);
INSERT INTO movie (title, year, dir_id, prod_id, genre_id) VALUES ('Captain America: Civil War', 2016, 7, 2, 4); -- 10
INSERT INTO movie (title, year, dir_id, prod_id, genre_id) VALUES ('Thor: Ragnarok', 2017, 8, 2, 3);
INSERT INTO movie (title, year, dir_id, prod_id, genre_id) VALUES ('Black Panther', 2018, 9, 2, 3);
INSERT INTO movie (title, year, dir_id, prod_id, genre_id) VALUES ('Avengers: Infinity War', 2018, 7, 2, 2);

-- Insert Movie-Actor Data
INSERT INTO movie_actors (mov_id, act_id) VALUES (1, 1);
INSERT INTO movie_actors (mov_id, act_id) VALUES (1, 5);
INSERT INTO movie_actors (mov_id, act_id) VALUES (1, 6);
INSERT INTO movie_actors (mov_id, act_id) VALUES (2, 1);
INSERT INTO movie_actors (mov_id, act_id) VALUES (2, 5);
INSERT INTO movie_actors (mov_id, act_id) VALUES (2, 6);
INSERT INTO movie_actors (mov_id, act_id) VALUES (2, 7);
INSERT INTO movie_actors (mov_id, act_id) VALUES (3, 4);
INSERT INTO movie_actors (mov_id, act_id) VALUES (3, 5);
INSERT INTO movie_actors (mov_id, act_id) VALUES (3, 6);
INSERT INTO movie_actors (mov_id, act_id) VALUES (3, 8);
INSERT INTO movie_actors (mov_id, act_id) VALUES (4, 2);
INSERT INTO movie_actors (mov_id, act_id) VALUES (4, 5);
INSERT INTO movie_actors (mov_id, act_id) VALUES (5, 1);
INSERT INTO movie_actors (mov_id, act_id) VALUES (5, 2);
INSERT INTO movie_actors (mov_id, act_id) VALUES (5, 3);
INSERT INTO movie_actors (mov_id, act_id) VALUES (5, 4);
INSERT INTO movie_actors (mov_id, act_id) VALUES (5, 5);
INSERT INTO movie_actors (mov_id, act_id) VALUES (5, 6);
INSERT INTO movie_actors (mov_id, act_id) VALUES (5, 7);
INSERT INTO movie_actors (mov_id, act_id) VALUES (5, 8);
INSERT INTO movie_actors (mov_id, act_id) VALUES (6, 1);
INSERT INTO movie_actors (mov_id, act_id) VALUES (6, 1);
INSERT INTO movie_actors (mov_id, act_id) VALUES (7, 2); -- Cameo Appearance
INSERT INTO movie_actors (mov_id, act_id) VALUES (7, 4);
INSERT INTO movie_actors (mov_id, act_id) VALUES (7, 8);
INSERT INTO movie_actors (mov_id, act_id) VALUES (8, 2);
INSERT INTO movie_actors (mov_id, act_id) VALUES (8, 5);
INSERT INTO movie_actors (mov_id, act_id) VALUES (8, 7);
INSERT INTO movie_actors (mov_id, act_id) VALUES (9, 1);
INSERT INTO movie_actors (mov_id, act_id) VALUES (9, 2);
INSERT INTO movie_actors (mov_id, act_id) VALUES (9, 3);
INSERT INTO movie_actors (mov_id, act_id) VALUES (9, 4);
INSERT INTO movie_actors (mov_id, act_id) VALUES (9, 5);
INSERT INTO movie_actors (mov_id, act_id) VALUES (9, 7);
INSERT INTO movie_actors (mov_id, act_id) VALUES (10, 1);
INSERT INTO movie_actors (mov_id, act_id) VALUES (10, 2);
INSERT INTO movie_actors (mov_id, act_id) VALUES (10, 3);
INSERT INTO movie_actors (mov_id, act_id) VALUES (10, 7);
INSERT INTO movie_actors (mov_id, act_id) VALUES (10, 9);
INSERT INTO movie_actors (mov_id, act_id) VALUES (11, 4);
INSERT INTO movie_actors (mov_id, act_id) VALUES (12, 9);
INSERT INTO movie_actors (mov_id, act_id) VALUES (13, 1);
INSERT INTO movie_actors (mov_id, act_id) VALUES (13, 2);
INSERT INTO movie_actors (mov_id, act_id) VALUES (13, 4);
INSERT INTO movie_actors (mov_id, act_id) VALUES (13, 5);
INSERT INTO movie_actors (mov_id, act_id) VALUES (13, 7);
INSERT INTO movie_actors (mov_id, act_id) VALUES (13, 8);
INSERT INTO movie_actors (mov_id, act_id) VALUES (13, 9);
