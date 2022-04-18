var express = require('express');
var bodyParser = require("body-parser");

module.exports = function() {
    var app = express();

    app.use(bodyParser.urlencoded({ extended: false }));
    app.use(bodyParser.json());

    require('../app/routes/boats.server.routes.js')(app);
    require('../app/routes/slips.server.routes.js')(app);
    return app;
};
