var pug = require('pug');

exports.main = function(req, res) {
    var options = {};
    var locals = {};

    if (req.method === 'GET') {
        var html = pug.renderFile('./app/views/main.pug', options);
        res.send(html);
    }
}