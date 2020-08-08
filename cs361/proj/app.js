var express = require('express');
var mysql = require('./dbcon.js');
const delay = require('delay');

var app = express();
var handlebars = require('express-handlebars').create({defaultLayout:'main'});
var bodyParser = require('body-parser');

app.use(bodyParser.urlencoded({extended: true}));
app.use(bodyParser.json());
app.use(express.static('public'));

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 3486);

// User Story 1
app.get("/admin_homepage", function (req, res, next) {
  res.render('admin_homepage');
});

//Admin: Register Tutor Page
app.get("/registerTutor", function (req, res, next) {
  var context = {};
  var subjects = {};
  //Grab Subjects, then render
  mysql.pool.query('SELECT subjects_id, subject_name FROM subjects;', function (err, rows, fields) {
    if (err) {
      next(err);
      return;
    } else {
        subjects.row_info = [];
        for (row in rows) {
          info = {};
          info.id = rows[row].subjects_id;
          info.name = rows[row].subject_name;

          //push into subjects
          subjects.row_info.push(info);
        }
        context.data3 = subjects;
        //Finally Render
        res.render('regTutor', context);
      }
    });
});

app.get("/registerTeacher", function(req, res, next){
  var context = {};
  var schools = {};

  mysql.pool.query('SELECT school_id, school_name FROM school;', function(err, rows, fields){
    if(err){
      next(err);
      return;
    }
    schools.row_info = [];
    for(row in rows){
      info = {};
      info.id = rows[row].school_id;
      info.name = rows[row].school_name;
      schools.row_info.push(info);
    }
    context.data1 = schools;
  });


    delay(200)
      .then(() => {
        res.render('regTeacher', context);
    });

});

app.post("/registerTeacher", function(req, res, next){

  mysql.pool.query("INSERT INTO teacher (first_name, last_name, email, teacher_code, school) VALUES (?,?,?,?, (SELECT s.school_id FROM school s WHERE s.school_name = ?))", [req.body.first_name, req.body.last_name, req.body.email, 101, req.body.school], function (err, result) { 
    console.log(req.body);
    if (err) {
      console.log(err);
      res.render('failed')
      return;
    }
  });

});



//Add Tutor Helper Function
app.post("/addTutor", function (req, res, next) {
  //Insert into db using query params
  mysql.pool.query("INSERT INTO tutor (first_name, last_name, email, tutor_city, tutor_state, college_name, background_pass) VALUES (?, ?, ?, ?, ?, ?, ?)", [req.body.first_name, req.body.last_name, req.body.email, req.body.city, req.body.state, req.body.college, req.body.check], function (err, result) {
    console.log(req.body);
    if (err) {
      console.log(err);
      res.render('failed')
      return;
    }
  });

  delay(400)
    .then(() => {
      mysql.pool.query("INSERT INTO tutor_subjects VALUES ((SELECT tut.id FROM tutor tut WHERE tut.first_name = ? AND tut.last_name = ?), (SELECT sub.subjects_id FROM subjects sub WHERE sub.subject_name = ?))", [req.body.first_name, req.body.last_name, req.body.subject], function (err, result) {
        if (err) {
          console.log("Add Tutor-Subject Not Working");
          console.log(err);
          res.render('failed')
          return;
        }
        res.render('success');
      });
    });
});

// User Story 2
app.get("/teacher_homepage", function(req, res, next){
    var context = {}
    var students = {};
    //Used to fill school dropdown menu
    mysql.pool.query('SELECT student_id, first_name, last_name FROM student;', function(err, rows, fields){
      if(err){
        console.log(err);
        next(err);
        return;
      }
      //Store the info from db in schools object
      students.row_info = [];
      for(row in rows){
        info = {};
        info.id = rows[row].student_id;
        info.first_name = rows[row].first_name;
        info.last_name = rows[row].last_name;
        students.row_info.push(info);
      }
      context.data1 = students;
    });
    delay(200)
      .then(() => {
        res.render('teacher_home', context);
    });
  });

// User Story 2
app.get("/teacher_homepage", function(req, res, next){
    res.render('teacher_home');
  });

// User Story 2
app.get("/addSubject", function(req, res, next){
    var context = {}
    var students = {};
    var subjects = {};
    //Used to fill school dropdown menu
    mysql.pool.query('SELECT id, first_name, last_name FROM student;', function(err, rows, fields){
      if(err){
        console.log(err);
        next(err);
        return;
      }
      //Store the info from db in schools object
      students.row_info = [];
      for(row in rows){
        info = {};
        info.id = rows[row].id;
        info.first_name = rows[row].first_name;
        info.last_name = rows[row].last_name;
        students.row_info.push(info);
      }
      context.data1 = students;
    });

    //Used to fill school dropdown menu
    mysql.pool.query('SELECT subjects_id, subject_name FROM subjects;', function(err, rows, fields){
      if(err){
        console.log(err);
        next(err);
        return;
      }
      console.log(rows);
      //Store the info from db in schools object
      subjects.row_info = [];
      for(row in rows){
        info = {};
        info.id = rows[row].subjects_id;
        info.name = rows[row].subject_name;
        subjects.row_info.push(info);
      }
      context.data2 = subjects;
    });

    delay(400)
      .then(() => {
        res.render('addSub', context);
    });
  });

app.post('/addSubject',function(req,res,next){
    var context = {};

    //Insert into has table using query params
   mysql.pool.query("INSERT INTO student_subjects VALUES (?, ?);", 
    [req.body.student, req.body.subject], function(err, result){
        if(err){
          res.render('failedSub');
          return;
        }
        res.render('success');
  });
});

app.get("/registerstudent", function(req, res, next){
  var context = {};
  var schools = {};
  var teachers = {};
  var subjects = {};

  //Used to fill school dropdown menu
  mysql.pool.query('SELECT school_id, school_name FROM school;', function(err, rows, fields){
    if(err){
      next(err);
      return;
    }

    //Store the info from db in schools object
    schools.row_info = [];
    for(row in rows){
      info = {};
      info.id = rows[row].school_id;
      info.name = rows[row].school_name;

      //push into schools
      schools.row_info.push(info);
    }
    context.data1 = schools;
  });

  mysql.pool.query('SELECT teacher_id, first_name, last_name FROM teacher;', function(err, rows, fields){
    if(err){
      next(err);
      return;
    }

    //Store the info from db in schools object
    teachers.row_info = [];
    for(row in rows){
      info = {};
      info.id = rows[row].teacher_id;
      info.first_name = rows[row].first_name;
      info.last_name = rows[row].last_name;

      //push into teachers
      teachers.row_info.push(info);
    }
    context.data2 = teachers;
  });

  mysql.pool.query('SELECT subjects_id, subject_name FROM subjects;', function(err, rows, fields){
    if(err){
      next(err);
      return;
    }

    //Store the info from db in schools object
    subjects.row_info = [];
    for(row in rows){
      info = {};
      info.id = rows[row].subjects_id;
      info.name = rows[row].subject_name;

      //push into subjects
      subjects.row_info.push(info);
    }
    context.data3 = subjects;
  });

    delay(200)
      .then(() => {
        res.render('regStudent', context);
    });
  });

app.post("/addstudent", function(req, res, next){
    //Insert into db using query params
  mysql.pool.query("INSERT INTO student (student_id, first_name, last_name, email, school, teacher, grade) VALUES (?, ?, ?, ?, (SELECT s.school_id FROM school s WHERE s.school_name = ?), ?, ?)", 
    [req.body.id, req.body.first_name, req.body.last_name, req.body.email, req.body.school, req.body.teacher, req.body.grade], function(err, result){
        console.log(req.body);
        if(err){
          console.log(err);
          res.render('failed')
          return;
        }
    });

  delay(400)
      .then(() => {
          mysql.pool.query("INSERT INTO student_subjects VALUES ((SELECT stu.id FROM student stu WHERE stu.first_name = ? AND stu.last_name = ?), (SELECT sub.subjects_id FROM subjects sub WHERE sub.subject_name = ?))",
          [req.body.first_name, req.body.last_name, req.body.subject], function(err, result){
            if(err){
              console.log("not working 1");
              console.log(err);
              res.render('failed')
              return;
            }
            res.render('success');
          });
    }); 
});

/**
 * TUtor HomePage and Adding Subjects
 */
app.get("/tutor_home", function (req, res, next) {
  res.render('tutor_home');
});

// Tutor: Add Subjects
app.get("/addTutorSubject", function (req, res, next) {
  var context = {}
  var tutor = {};
  var subjects = {};
  //Used to fill tutor dropdown menu
  mysql.pool.query('SELECT tutor_id, first_name, last_name FROM tutor;', function (err, rows, fields) {
    if (err) {
      console.log(err);
      next(err);
      return;
    }
    //Store the info from db in tutor object
    tutor.row_info = [];
    for (row in rows) {
      info = {};
      info.id = rows[row].id;
      info.first_name = rows[row].first_name;
      info.last_name = rows[row].last_name;
      tutor.row_info.push(info);
    }
    context.data1 = tutor;
  });

  //Used to fill subjectsdropdown menu
  mysql.pool.query('SELECT subjects_id, subject_name FROM subjects;', function (err, rows, fields) {
    if (err) {
      console.log(err);
      next(err);
      return;
    }
    console.log(rows);

    subjects.row_info = [];
    for (row in rows) {
      info = {};
      info.id = rows[row].subjects_id;
      info.name = rows[row].subject_name;
      subjects.row_info.push(info);
    }
    context.data2 = subjects;
  });

  delay(400)
    .then(() => {
      res.render('addTutorSub', context);
    });
});

// Add Subject to Tutor
app.post('/addTutorSubject', function (req, res, next) {
  var context = {};

  //Insert into tutor_subject table using query params
  mysql.pool.query("INSERT INTO tutor_subjects VALUES (?, ?);", [req.body.tutor, req.body.subject], function (err, result) {
    if (err) {
      res.render('tutorAddFail');
      return;
    }
    res.render('tutorAddSuccess');
  });
});

app.get("/addSession", function(req, res, next){
    var context = {}
    var students = {};
    var subjects = {};
    var schools = {};
    var tutors = {};
    // query to get list of students
    mysql.pool.query('SELECT id, first_name, last_name FROM student;', function(err, rows, fields){
      if(err){
        console.log(err);
        next(err);
        return;
      }
 
      students.row_info = [];
      for(row in rows){
        info = {};
        info.id = rows[row].id;
        info.first_name = rows[row].first_name;
        info.last_name = rows[row].last_name;
        students.row_info.push(info);
      }
      context.data1 = students;
    });

    // query to get list of subjects
    mysql.pool.query('SELECT subjects_id, subject_name FROM subjects;', function(err, rows, fields){
      if(err){
        console.log(err);
        next(err);
        return;
      }
      console.log(rows);

      subjects.row_info = [];
      for(row in rows){
        info = {};
        info.id = rows[row].subjects_id;
        info.subject_name = rows[row].subject_name;
        subjects.row_info.push(info);
      }
      context.data2 = subjects;
    });

    // query for tutors
    mysql.pool.query('SELECT tutor_id, first_name, last_name FROM tutor;', function(err, rows, fields){
    if(err){
      console.log(err);
      next(err);
      return;
    }
    console.log(rows);

    tutors.row_info = [];
    for(row in rows){
      info = {};
      info.id = rows[row].tutor_id;
      info.first_name = rows[row].first_name;
      info.last_name = rows[row].last_name;
      tutors.row_info.push(info);
    }
    context.data3 = tutors;
    });

    // query for schools
    mysql.pool.query('SELECT school_id, school_name FROM school;', function(err, rows, fields){
    if(err){
      console.log(err);
      next(err);
      return;
    }
    console.log(rows);

    schools.row_info = [];
    for(row in rows){
      info = {};
      info.id = rows[row].school_id;
      info.school_name = rows[row].school_name;
      schools.row_info.push(info);
    }
    context.data4 = schools;
    });

    delay(400)
      .then(() => {
        res.render('addSession', context);
    });
  });

app.post('/addSession', function (req, res, next) {
  var context = {};

  //Insert into tutor_subject table using query params
  mysql.pool.query("INSERT INTO tutorSession (student, tutor, subject, session_date, session_time, session_location, session_occured) VALUES (?, ?, ?, ?, ?, (SELECT school.school_name FROM school WHERE school.school_id = ?), FALSE);", [req.body.student, req.body.tutor, req.body.subject, req.body.date, req.body.time, req.body.school], function (err, result) {
    if (err) {
      console.log(err);
      res.render('sessionAddFail');
      return;
    }
    res.render('sessionAddSuccess', context);
  });
});

/*** 
 * Server Error Handling & Listening
 ***/

//Page not found error 
app.use(function(req,res){
  res.status(404);
  res.render('404');
});

//Server error
app.use(function(err, req, res, next){
  res.status(500);
  res.render('500');
  console.log(err);
});

app.listen(app.get('port'), function(){
  console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});