/* 
DB Setup for Group 17
Data Definition Queries for Tutoring Database
Author: 
*/

-- Drop, Create, Use Commands
DROP DATABASE if exists tutoring;
CREATE DATABASE tutoring;
USE tutoring;

-- Schema  for Table "tutor"
CREATE TABLE tutor (
  tutor_id int NOT NULL PRIMARY KEY AUTO_INCREMENT,
  first_name varchar (32) NOT NULL,
  last_name varchar (32) NOT NULL,
  email varchar(255) NOT NULL,
  tutor_city varchar (32) NOT NULL,
  tutor_state varchar (32) NOT NULL, 
  college_name varchar (255) NOT NULL,
  background_pass boolean NOT NULL
) ENGINE=InnoDB;

INSERT INTO tutor (first_name, last_name, email, tutor_city, tutor_state, college_name, background_pass) 
VALUES ("Dwight", "Schrute", "shruted@oregonstate.edu", "Corvallis", "Oregon", "Oregon State University", 1);

-- Schema  for Table "subjects"
CREATE TABLE subjects (
  subjects_id int NOT NULL PRIMARY KEY AUTO_INCREMENT,
  subject_name varchar (32) NOT NULL
) ENGINE=InnoDB;

INSERT INTO subjects (subject_name) 
VALUES ("Math"), ("Science"), ("History"), ("Spanish"), ("Computer Science");

-- Schema  for Table (Many-to-Many)
CREATE TABLE tutor_subjects (
  tutor_id int,
  subject_id int,
  PRIMARY KEY (tutor_id, subject_id), 
  FOREIGN KEY (tutor_id) REFERENCES tutor(tutor_id) ON DELETE CASCADE,
  FOREIGN KEY (subject_id) REFERENCES subjects(subjects_id) ON DELETE CASCADE
) ENGINE=InnoDB;

INSERT INTO tutor_subjects
VALUES ((SELECT t.tutor_id FROM tutor t WHERE t.first_name = "Dwight" AND t.last_name = "Schrute"), 
        (SELECT sub.subjects_id FROM subjects sub WHERE sub.subject_name = "History"));

-- Schema for Table "School"
CREATE TABLE school (
  school_id int NOT NULL PRIMARY KEY AUTO_INCREMENT,
  school_name varchar(32) NOT NULL,
  city varchar (32) NOT NULL,
  state_name varchar (32) NOT NULL
) ENGINE=InnoDB;

INSERT INTO school (school_name, city, state_name) 
VALUES ("Scranton High School", "Scranton", "Pennsylvania");

INSERT INTO school (school_name, city, state_name) 
VALUES ("Corvallis High School", "Corvallis", "Ohio");

-- Schema for Table "Teacher"
CREATE TABLE teacher (
  teacher_id int NOT NULL PRIMARY KEY AUTO_INCREMENT,
  teacher_code bigint NOT NULL,
  first_name varchar (32) NOT NULL,
  last_name varchar (32) NOT NULL,
  email varchar(255) NOT NULL,
  school int NOT NULL,
  FOREIGN KEY (school)
  REFERENCES school(school_id) ON DELETE RESTRICT
) ENGINE=InnoDB;

INSERT INTO teacher (teacher_code, first_name, last_name, email, school) 
VALUES (123456, "Pam", "Beasley", "beasley@dist55.org", (SELECT s.school_id FROM school s WHERE s.school_name = "Scranton High School"));

INSERT INTO teacher (teacher_code, first_name, last_name, email, school) 
VALUES (123458, "Jim", "Halpert", "halpert@dist55.org", (SELECT s.school_id FROM school s WHERE s.school_name = "Corvallis High School"));

/* Tables Definition */
-- Schema for Table "Student"
CREATE TABLE student (
  id int NOT NULL PRIMARY KEY AUTO_INCREMENT,
  student_id bigint NOT NULL,
  first_name varchar (32) NOT NULL,
  last_name varchar (32) NOT NULL,
  email varchar(255) NOT NULL,
  school int NOT NULL,
  teacher int NOT NULL,
  grade int NOT NULL,
  FOREIGN KEY (school) REFERENCES school(school_id) ON DELETE RESTRICT,
  FOREIGN KEY (teacher) REFERENCES teacher(teacher_id) ON DELETE RESTRICT,
  FOREIGN KEY (teacher) REFERENCES teacher(teacher_id) ON DELETE RESTRICT
)ENGINE=InnoDB;

INSERT INTO student (student_id, first_name, last_name, email, school, teacher, grade) 
VALUES (654321, "Michael", "Scott", "student@gmail.com", (SELECT s.school_id FROM school s WHERE s.school_name = "Scranton High School"), 
(SELECT t.teacher_id FROM teacher t WHERE t.first_name = "Pam" AND t.last_name="Beasley"), 11);

-- Schema  for Table (Many-to-Many)
CREATE TABLE student_subjects (
  student_id int,
  subject_id int,
  PRIMARY KEY (student_id, subject_id), 
  FOREIGN KEY (student_id) REFERENCES student(id) ON DELETE CASCADE,
  FOREIGN KEY (subject_id) REFERENCES subjects(subjects_id) ON DELETE CASCADE
) ENGINE=InnoDB;

INSERT INTO student_subjects
VALUES ((SELECT stu.id FROM student stu WHERE stu.first_name = "Michael" AND stu.last_name = "Scott"), 
        (SELECT sub.subjects_id FROM subjects sub WHERE sub.subject_name = "History"));

-- Schema for Table "Session"
CREATE TABLE tutorSession (
  session_id int NOT NULL PRIMARY KEY AUTO_INCREMENT,
  student int NOT NULL,
  tutor int NOT NULL,
  subject integer NOT NULL,
  session_date date NOT NULL,
  session_time TIME NOT NULL,
  session_location varchar(32) NOT NULL,
  session_occured boolean NOT NULL,
  FOREIGN KEY (tutor) REFERENCES tutor(tutor_id) ON DELETE RESTRICT,
  FOREIGN KEY (subject) REFERENCES subjects(subjects_id) ON DELETE RESTRICT,
  FOREIGN KEY (student) REFERENCES student(id) ON DELETE RESTRICT
)ENGINE=InnoDB;
