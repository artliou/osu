var express = require('express');
var bodyParser = require("body-parser");

module.exports = function() {
    var app = express();

    app.use(bodyParser.urlencoded({ extended: false }));
    app.use(bodyParser.json());
    
    app.use('/css',       express.static('css'));
    app.use('/bootstrap', express.static('bootstrap'));
    app.use('/assets',    express.static('assets'));
    app.use('/client',    express.static('client'));

    require('../app/routes/main.server.routes.js')(app);
    require('../app/routes/oauth2.server.routes.js')(app);
    return app;
};
