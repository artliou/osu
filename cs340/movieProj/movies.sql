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
INSERT INTO genres (genre_name) VALUES ('Action'); -- 1
INSERT INTO genres (genre_name) VALUES ('Animation');
INSERT INTO genres (genre_name) VALUES ('Adventure');
INSERT INTO genres (genre_name) VALUES ('Comedy');
INSERT INTO genres (genre_name) VALUES ('Drama'); -- 5
INSERT INTO genres (genre_name) VALUES ('Fantasy');
INSERT INTO genres (genre_name) VALUES ('Horror');
INSERT INTO genres (genre_name) VALUES ('Romance');
INSERT INTO genres (genre_name) VALUES ('Thriller');

-- Insert Producer Data
INSERT INTO producer (first_name, last_name) VALUES ('Avi', 'Arad');
INSERT INTO producer (first_name, last_name) VALUES ('Kevin', 'Feige');
INSERT INTO producer (first_name, last_name) VALUES ('Amy', 'Pascal');

-- Insert Director Data
INSERT INTO director (first_name, last_name) VALUES ('Jon', 'Favreau'); -- 1 
INSERT INTO director (first_name, last_name) VALUES ('Kenneth', 'Branagh');
INSERT INTO director (first_name, last_name) VALUES ('Joe', 'Johnston');
INSERT INTO director (first_name, last_name) VALUES ('Joss', 'Whedon');
INSERT INTO director (first_name, last_name) VALUES ('Shane', 'Black'); -- 5
INSERT INTO director (first_name, last_name) VALUES ('Alan', 'Taylor');
INSERT INTO director (first_name, last_name) VALUES ('Anthony', 'Russo');
INSERT INTO director (first_name, last_name) VALUES ('James', 'Gunn');
INSERT INTO director (first_name, last_name) VALUES ('Peyton', 'Reed');
INSERT INTO director (first_name, last_name) VALUES ('Scott', 'Derrickson'); -- 10
INSERT INTO director (first_name, last_name) VALUES ('Jon', 'Watts');
INSERT INTO director (first_name, last_name) VALUES ('Taika', 'Waititi');
INSERT INTO director (first_name, last_name) VALUES ('Ryan', 'Coogler'); -- 13

-- Insert Actor Data
INSERT INTO actor (first_name, last_name) VALUES ('Sebastian', 'Stan');
INSERT INTO actor (first_name, last_name) VALUES ('Jeremy', 'Renner');
INSERT INTO actor (first_name, last_name) VALUES ('Hayler', 'Atwell');
INSERT INTO actor (first_name, last_name) VALUES ('Clark', 'Gregg'); -- 5
INSERT INTO actor (first_name, last_name) VALUES ('Dave', 'Bautista'); 
INSERT INTO actor (first_name, last_name) VALUES ('Samuel', 'Jackson');
INSERT INTO actor (first_name, last_name) VALUES ('Zoe', 'Saldana');
INSERT INTO actor (first_name, last_name) VALUES ('Vin', 'Diesel');
INSERT INTO actor (first_name, last_name) VALUES ('Idris', 'Elba'); -- 10
INSERT INTO actor (first_name, last_name) VALUES ('Paul', 'Rudd'); 
INSERT INTO actor (first_name, last_name) VALUES ('Tom', 'Hiddleston');
INSERT INTO actor (first_name, last_name) VALUES ('Elizabeth', 'Olsen');
INSERT INTO actor (first_name, last_name) VALUES ('Tom', 'Holland');
INSERT INTO actor (first_name, last_name) VALUES ('Chris', 'Pratt'); -- 15
INSERT INTO actor (first_name, last_name) VALUES ('Don', 'Cheadle'); 
INSERT INTO actor (first_name, last_name) VALUES ('Bradley', 'Cooper');
INSERT INTO actor (first_name, last_name) VALUES ('Chris', 'Evans');
INSERT INTO actor (first_name, last_name) VALUES ('Scarlett', 'Johansson');
INSERT INTO actor (first_name, last_name) VALUES ('Robert', 'Downey'); -- 20
INSERT INTO actor (first_name, last_name) VALUES ('Benedict', 'Cumberbatch');
INSERT INTO actor (first_name, last_name) VALUES ('Chadwick', 'Boseman');
INSERT INTO actor (first_name, last_name) VALUES ('Chris', 'Hemsworth');

-- Insert Movie Data
INSERT INTO movie (title, year) VALUES ('Iron Man', 2008);

-- Insert Movie-Actor Data