module.exports = function(app) {
    var index = require('../controllers/main.server.controller');

    // Get main page
    app.get('/', index.main);

};