module.exports = function(app) {
    var index = require('../controllers/oauth2.server.controller');

    // Get main page
    app.get('/oauth2', index.oauth2);

};