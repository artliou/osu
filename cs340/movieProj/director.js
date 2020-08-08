module.exports = function() {
    var express = require('express');
    var router = express.Router();

    /*Display all people. Requires web based javascript to delete users with AJAX*/
    function getDirectors(res, mysql, context, complete) {
        mysql.pool.query("SELECT director_id as id, first_name, last_name FROM director", function(error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.directors = results;
            complete();
        });
    }

    function getDirector(res, mysql, context, id, complete) {
        var sql = "SELECT director_id as id, first_name, last_name FROM director WHERE director_id = ?";
        var inserts = [id];
        mysql.pool.query(sql, inserts, function(error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.directors = results[0];
            complete();
        });
    }

    router.get('/', function(req, res) {
        var callbackCount = 0;
        var context = {};
        context.jsscripts = ["delete.js"];
        var mysql = req.app.get('mysql');
        getDirectors(res, mysql, context, complete);
        function complete() {
            callbackCount++;
            if (callbackCount >= 1) {
                res.render('director', context);
            }
        }
        //Extra Line
        // res.render('director', context);
    });

    /* Display one person for the specific purpose of updating people */

    router.get('/:id', function(req, res) {
        callbackCount = 0;
        var context = {};
        context.jsscripts = ["select.js", "update.js"];
        var mysql = req.app.get('mysql');
        getDirector(res, mysql, context, req.params.id, complete);
        function complete() {
            callbackCount++;
            if (callbackCount >= 1) {
                res.render('update-director', context);
            }
        }
    });

    /* Adds a person, redirects to the people page after adding */

    router.post('/', function(req, res) {
        console.log(req.body)
        var mysql = req.app.get('mysql');
        var sql = "INSERT INTO director (first_name, last_name) VALUES (?,?)";
        var inserts = [req.body.fname, req.body.lname];
        sql = mysql.pool.query(sql, inserts, function(error, results, fields) {
            if (error) {
                console.log(JSON.stringify(error))
                res.write(JSON.stringify(error));
                res.end();
            } else {
                res.redirect('/director');
            }
        });
    });

    /* The URI that update data is sent to in order to update a person */

    router.put('/:id', function(req, res) {
        var mysql = req.app.get('mysql');
        console.log(req.body)
        console.log(req.params.id)
        var sql = "UPDATE director SET first_name = ?, last_name = ? WHERE director_id = ?";
        var inserts = [req.body.first_name, req.body.last_name, req.params.id];
        sql = mysql.pool.query(sql, inserts, function(error, results, fields) {
            if (error) {
                console.log(error)
                res.write(JSON.stringify(error));
                res.end();
            } else {
                res.status(200);
                res.end();
            }
        });
    });

    /* Route to delete a person, simply returns a 202 upon success. Ajax will handle this. */

    router.delete('/:id', function(req, res) {
        var mysql = req.app.get('mysql');
        var sql = "DELETE FROM director WHERE director_id = ?";
        var inserts = [req.params.id];
        sql = mysql.pool.query(sql, inserts, function(error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.status(400);
                res.end();
            } else {
                res.status(202).end();
            }
        })
    })

    return router;
}();
