const mysql = require('mysql');

module.exports = function () {
    var context = this;


    this.pool = mysql.createPool({
        host: 'mysql.cs.orst.edu',
        user: 'cs340_praterj',
        password: '7221',
        database: 'cs340_praterj'
    });
    console.log('[MYSQL] Created Database object.');

    this.getWorkouts = function (req, res, callback) {
        var workoutSort = parseInt(req.query.sortby);
        console.log("[MYSQL] /database.getWorkouts(" + workoutSort  + ")")
        var sqlString = 'SELECT workoutID, name, reps, weight, date, lbs FROM workouts ';
        switch (workoutSort) {
            case 0:
                {
                    sqlString += 'ORDER BY date DESC';
                }
                break;
            case 1:
                {
                    sqlString += 'ORDER BY weight DESC;';
                }
                break;
            case 2:
                {
                    sqlString += 'ORDER BY reps DESC;';
                }
                break;
        }
        context.pool.query(sqlString, function (err, rows, fields) {
            if (err) {
                console.log('[MSQL] Error: ' + err);
                callback({
                    "error": err
                });
                return;
            } else {
                callback(rows);
            }
        });
    };


    this.updateWorkout = function (req, res, callback) {
        console.log('[MYSQL] /database.insertWorkout');
        var payload = {};
        var dataSet = [
            req.body.name,
            req.body.reps,
            req.body.weight,
            new Date(req.body.date),
            req.body.lbs,
            req.body.workoutID
        ];
        context.pool.query("UPDATE workouts SET name=?, reps=?, weight=?, date=?, lbs=? WHERE workoutID=?", dataSet,
            function (err, result) {
                if (err) {
                    console.log('[MSQL] Error: ' + err);
                    payload = {
                        "updated": false,
                        "error": err
                    };
                    callback(payload);
                } else {
                    payload = {
                        "updated": true,
                        "createdID": req.body.workoutID
                    };
                    callback(payload);
                }
            });
    };

    this.insertWorkout = function (req, res, callback) {
        console.log('[MYSQL] /database.insertWorkout');
        var payload = {};
        var dataSet = [
            req.body.name,
            req.body.reps,
            req.body.weight,
            new Date(req.body.date),
            req.body.lbs
        ];
        context.pool.query("INSERT INTO workouts (name, reps, weight, date, lbs) VALUES (?, ?, ?, ?, ?)", dataSet,
            function (err, result) {
                if (err) {
                    console.log('[MSQL] Error: ' + err);
                    payload = {
                        "created": false,
                        "error": err
                    };
                    callback(payload);
                } else {
                    payload = {
                        "created": true,
                        "createdID": result.insertId
                    };
                    callback(payload);
                }
            });
    };

    this.deleteWorkout = function (req, res, callback) {
        console.log('[MYSQL] /database.deleteWorkout');
        var payload = {};
        var dataSet = [
            req.body.workoutID,
        ];
        context.pool.query("DELETE FROM workouts WHERE workoutID=?", dataSet,
            function (err, result) {
                if (err) {
                    console.log('[MSQL] Error: ' + err);
                    payload.error = err;
                    callback(payload);
                    return;
                }
                payload = {
                    "deleted": req.body.workoutID
                };
                callback(payload);
            });
    };

    this.deleteAllWorkouts = function (req, res, callback) {
        console.log('[MYSQL] /database.deleteWorkout');
        var payload = {};
        var dataSet = [];
        context.pool.query("DELETE FROM workouts", dataSet,
            function (err, result) {
                if (err) {
                    console.log('[MSQL] Error: ' + err);
                    payload.error = err;
                    callback(payload);
                    return;
                }
                payload = {
                    "deleted": "all"
                };
                callback(payload);
            });
    };

    this.createTable = function () {
        console.log('[MYSQL] Create Table');
        var createString =
            "CREATE TABLE IF NOT EXISTS workouts(" +
            "workoutID INT PRIMARY KEY AUTO_INCREMENT," +
            "name VARCHAR(255) NOT NULL," +
            "reps int NOT NULL," +
            "weight int NOT NULL," +
            "date DATETIME NOT NULL," +
            "lbs BOOLEAN NOT NULL) ENGINE=InnoDB;";
        context.pool.query(createString, function (err) {
            if (err) {
                console.log('[MSQL] Error: ' + err);
            }
        });
    };

    // Functions are defined. Do any initialization needed.

    this.createTable();
}