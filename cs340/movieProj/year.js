module.exports = function() {
    var express = require('express');
    var router = express.Router();

    /*Display all movies. Requires web based javascript to delete users with AJAX*/

    function getYear(res, mysql, context, complete) {
        mysql.pool.query("SELECT title, year FROM movie", function(error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.years = results;
            complete();
        });
    }

    router.get('/', function(req, res) {
        var callbackCount = 0;
        var context = {};
        var mysql = req.app.get('mysql');
        getYear(res, mysql, context, complete);
        function complete() {
            callbackCount++;
            if (callbackCount >= 1) {
                res.render('year', context);
            }
        }
        //Extra Line
        // res.render('year', context);
    });

    /* Display result of year search */
    router.post('/', function(req, res) {
        console.log(req.body)
        var mysql = req.app.get('mysql');
        var sql = "SELECT title, year FROM movie WHERE year=?";
        var inserts = [req.body.year];
        sql = mysql.pool.query(sql, inserts, function(error, results, fields) {
            if (error) {
                console.log(JSON.stringify(error))
                res.write(JSON.stringify(error));
                res.end();
            } else {
                var context = {};
                context.years = results;
                // res.redirect('/title', context);
                res.render('year', context);
            }
        });
    });

    return router;
}();
