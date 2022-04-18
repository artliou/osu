const pug = require('pug');

exports.render = function(req, res) {
    res.render('error', {
        title: 'CS_290: Assignment 2 - HTML/CSS',
        error: req
    })
};
