module.exports = function() {
    var express = require('express');
    var router = express.Router();

    function getActors(res, mysql, context, complete) {
        mysql.pool.query("SELECT actor_id as id, first_name, last_name FROM actor", function(error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.actors = results;
            complete();
        });
    }

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

    function getGenres(res, mysql, context, complete) {
        mysql.pool.query("SELECT genre_id as id, genre_name as name FROM genre", function(error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.genres = results;
            complete();
        });
    }

    function getProducers(res, mysql, context, complete) {
        mysql.pool.query("SELECT producer_id as id, first_name, last_name FROM producer", function(error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.producers = results;
            complete();
        });
    }

    function getMovies(res, mysql, context, complete) {
        mysql.pool.query("SELECT movie_id as id, title, year, director.first_name as director, genre.genre_name as genre, producer.first_name as producer FROM movie INNER JOIN director ON movie.dir_id = director.director_id INNER JOIN genre ON movie.genre_id = genre.genre_id INNER JOIN producer ON movie.prod_id = producer.producer_id", function(error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.movies = results;
            complete();
        });
    }

    function getMovie(res, mysql, context, id, complete) {
        var sql = "SELECT movie_id as id, title, year, director.first_name as director, genre.genre_name as genre, producer.first_name as producer FROM movie INNER JOIN director ON movie.dir_id = director.director_id INNER JOIN genre ON movie.genre_id = genre.genre_id INNER JOIN producer ON movie.prod_id = producer.producer_id WHERE movie_id = ?";
        var inserts = [id];
        mysql.pool.query(sql, inserts, function(error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end();
            }
            context.movies = results[0];
            complete();
        });
    }

    /*Display all movies. Requires web based javascript to delete users with AJAX*/

    router.get('/', function(req, res) {
        var callbackCount = 0;
        var context = {};
        context.jsscripts = ["delete.js"];
        var mysql = req.app.get('mysql');
        getMovies(res, mysql, context, complete);
        getActors(res, mysql, context, complete);
        getDirectors(res, mysql, context, complete);
        getGenres(res, mysql, context, complete);
        getProducers(res, mysql, context, complete);
        function complete() {
            callbackCount++;
            if (callbackCount >= 5) {
                res.render('movie', context);
            }
        }
        //Extra Line
        // res.render('movie', context);
    });

    /* Display one movie for the specific purpose of updating movie */
    router.get('/:id', function(req, res) {
        callbackCount = 0;
        var context = {};
        context.jsscripts = ["select.js", "update.js"];
        var mysql = req.app.get('mysql');
        getActors(res, mysql, context, complete);
        getDirectors(res, mysql, context, complete);
        getGenres(res, mysql, context, complete);
        getProducers(res, mysql, context, complete);
        getMovie(res, mysql, context, req.params.id, complete);
        function complete() {
            callbackCount++;
            if (callbackCount >= 5) {
                res.render('update-movie', context);
            }
        }
        // res.render('update-movie', context);
    });

    /* Adds a movie, redirects to the people page after adding */

    router.post('/', function(req, res) {
        console.log(req.body, "Post")
        var mysql = req.app.get('mysql');
        var sql = "INSERT INTO movie (title, year, dir_id, prod_id, genre_id) VALUES (?,?,?,?,?)";
        var inserts = [req.body.title, req.body.year, req.body.director, req.body.producer, req.body.genre];
        sql = mysql.pool.query(sql, inserts, function(error, results, fields) {
            if (error) {
                console.log(JSON.stringify(error))
                res.write(JSON.stringify(error));
                res.end();
            } else {
                res.redirect('/movie');
            }
        });
    });

    /* The URI that update data is sent to in order to update a person */
    router.put('/:id', function(req, res) {
        var mysql = req.app.get('mysql');
        console.log(req.body)
        // console.log(req.params.id)
        var sql = "UPDATE movie SET title=?, year=?, genre_id=?, dir_id=?, prod_id=? WHERE movie_id=?";
        var inserts = [req.body.title, req.body.year, req.body.genre, req.body.director, req.body.producer, req.params.id];
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
        var sql = "DELETE FROM movie WHERE movie_id = ?";
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
