function deleteActor(id) {
    $.ajax({
        url: '/actor/' + id,
        type: 'DELETE',
        success: function(result) {
            window.location.reload(true);
        }
    })
};

function deleteGenre(id) {
    $.ajax({
        url: '/genre/' + id,
        type: 'DELETE',
        success: function(result) {
            window.location.reload(true);
        }
    })
};

function deleteDirector(id) {
    $.ajax({
        url: '/director/' + id,
        type: 'DELETE',
        success: function(result) {
            window.location.reload(true);
        }
    })
};

function deleteProducer(id) {
    $.ajax({
        url: '/producer/' + id,
        type: 'DELETE',
        success: function(result) {
            window.location.reload(true);
        }
    })
};

function deleteMovie(id) {
    $.ajax({
        url: '/movie/' + id,
        type: 'DELETE',
        success: function(result) {
            window.location.reload(true);
        }
    })
};

function deleteMovieActor(mov_id, act_id) {
    $.ajax({
        url: '/movie_actors/mov_id/' + mov_id + '/act_id/' + act_id,
        type: 'DELETE',
        success: function(result) {
            if (result.responseText != undefined) {
                alert(result.responseText)
            }
            else {
                window.location.reload(true)
            }
        }
    })
};
