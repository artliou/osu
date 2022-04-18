function updateActor(id) {
    $.ajax({
        url: '/actor/' + id,
        type: 'PUT',
        data: $('#update-actor').serialize(),
        success: function(result) {
            window.location.replace("./");
        }
    })
};

function updateGenre(id) {
    $.ajax({
        url: '/genre/' + id,
        type: 'PUT',
        data: $('#update-genre').serialize(),
        success: function(result) {
            window.location.replace("./");
        }
    })
};

function updateDirector(id) {
    $.ajax({
        url: '/director/' + id,
        type: 'PUT',
        data: $('#update-director').serialize(),
        success: function(result) {
            window.location.replace("./");
        }
    })
};

function updateProducer(id) {
    $.ajax({
        url: '/producer/' + id,
        type: 'PUT',
        data: $('#update-producer').serialize(),
        success: function(result) {
            window.location.replace("./");
        }
    })
};

function updateMovie(id) {
    $.ajax({
        url: '/movie/' + id,
        type: 'PUT',
        data: $('#update-movie').serialize(),
        success: function(result) {
            window.location.replace("./");
        }
    })
};