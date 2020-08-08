function deleteActor(id) {
    $.ajax({
        url: '/actor/' + id,
        type: 'DELETE',
        success: function(result) {
            window.location.reload(true);
        }
    })
};

function deleteMovieActor(pid, cid) {
    $.ajax({
        url: '/movie_actors/pid/' + pid + '/cert/' + cid,
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
