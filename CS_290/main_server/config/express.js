var express = require('express');
var bodyParser     =        require("body-parser");

module.exports = function() {
    var app = express();
    app.use(express.static('./public'));
    app.set('views', './app/views');
    app.set('view engine', 'pug');
    
    app.use(bodyParser.urlencoded({ extended: false }));
    app.use(bodyParser.json());

    require('../app/routes/index.server.routes.js')(app);
    require('../app/routes/error.server.routes.js')(app);
    return app;
};
