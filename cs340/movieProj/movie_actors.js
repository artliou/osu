module.exports = function() {
    var express = require('express');
    var router = express.Router();

    /* get movies to populate in dropdown */
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

    /* get actor to populate in multi select */
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

    /* Get M-M relationships from Movie and Actors*/
    function getMovieActors(res, mysql, context, complete) {
        sql = "SELECT movie_id, actor_id, title, year, CONCAT(first_name,' ',last_name) AS name FROM movie INNER JOIN movie_actors on movie.movie_id = movie_actors.mov_id INNER JOIN actor on actor.actor_id = movie_actors.act_id"
        mysql.pool.query(sql, function(error, results, fields) {
            if (error) {
                res.write(JSON.stringify(error));
                res.end()
            }
            context.movie_actors = results;
            complete();
        });
    }

    /* List movies with actors along with
     * displaying a form to associate a person with multiple certificates
     */
    router.get('/', function(req, res) {
        var callbackCount = 0;
        var context = {};
        context.jsscripts = ["delete.js"];
        var mysql = req.app.get('mysql');
        getMovies(res, mysql, context, complete);
        getActors(res, mysql, context, complete);
        getMovieActors(res, mysql, context, complete);
        function complete() {
            callbackCount++;
            if (callbackCount >= 3) {
                res.render("movie_actors", context);
            }
        }
        // Extra Line to Render
        // res.render(handlebars_file, context);
    });

    /* Associate actor(s) with a movie and
     * then redirect to the movie_actors page after adding
     */
    router.post('/', function(req, res) {
        console.log("We get the multi-select actor(s) as ", req.body.actors)
        console.log("Body", req.body)
        var mysql = req.app.get('mysql');
        var actors = req.body.actors;
        var movie = req.body.movie_id;
        for (let actor of actors) {
            console.log("Processing actor id " + actor)
            // console.log("Processing movie id " + movie)
            var sql = "INSERT INTO movie_actors (mov_id, act_id) VALUES (?,?)";
            var inserts = [movie, actor];
            sql = mysql.pool.query(sql, inserts, function(error, results, fields) {
                if (error) {
                    res.write(JSON.stringify(error));
                    res.end();
                    console.log(error)
                }
            });
        }
        res.redirect('/movie_actors');
    });

    /* Delete a movie_actor record */
    /* This route will accept a HTTP DELETE request in the form
     * /movie/{{mov_id}}/actor/{{actor_id}} -- which is sent by the AJAX form
     */
    router.delete('/mov_id/:mov_id/act_id/:act_id', function(req, res) {
        console.log(req.params.mov_id)
        console.log(req.params.act_id)
        var mysql = req.app.get('mysql');
        var sql = "DELETE FROM movie_actors WHERE mov_id = ? AND act_id = ?";
        var inserts = [req.params.mov_id, req.params.act_id];
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
