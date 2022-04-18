var express = require('express');
var bodyParser = require("body-parser");

module.exports = function() {
    var app = express();

    app.use(bodyParser.urlencoded({ extended: false }));
    app.use(bodyParser.json());

    require('../app/routes/users.js')(app);
    require('../app/routes/content.js')(app);
    return app;
};
