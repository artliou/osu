const pug = require('pug');

exports.render = function(req, res) {
    res.render('index', {
        title: 'CS 340 Final Project',
        httpMethod: this.httpMethod,
        stuff: this.stuff
    });
};
