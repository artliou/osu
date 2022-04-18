const pug = require('pug');

exports.render = function(req, res) {
    res.render('index', {
        title: 'CS_290: Assignment - HTTP GET/POST checker',
        httpMethod: this.httpMethod,
        stuff: this.stuff
    });
};
