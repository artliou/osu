module.exports = function() {
    var express = require('express');
    var router = express.Router();

    /*Display Search Bar for Titles. Requires web based javascript to delete users with AJAX*/

    function getTitle(res, mysql, context, complete) {
        mysql.pool.query("SELECT title, year FROM movie", function(error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.titles = results;
            complete();
        });
    }

    router.get('/', function(req, res) {
        var callbackCount = 0;
        var context = {};
        var mysql = req.app.get('mysql');
        getTitle(res, mysql, context, complete);
        function complete() {
            callbackCount++;
            if (callbackCount >= 1) {
                res.render('title', context);
            }
        }
        //Extra Line
        // res.render('title', context);
    });

    /* Display result of title search*/
    router.post('/', function(req, res) {
        console.log(req.body)
        var mysql = req.app.get('mysql');
        var sql = "SELECT title, year FROM movie WHERE title=?";
        var inserts = [req.body.title];
        sql = mysql.pool.query(sql, inserts, function(error, results, fields) {
            if (error) {
                console.log(JSON.stringify(error))
                res.write(JSON.stringify(error));
                res.end();
            } else {
                var context = {};
                context.titles = results;
                // res.redirect('/title', context);
                res.render('title', context);
            }
        });
    });

    return router;
}();
